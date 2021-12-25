import * as React from "react";
import { useAppSelector, useAppDispatch } from "../../hooks/redux";
import { SCORE, TBoard } from "../../types/board";
import { Colors } from "../../types/colors-enum";
import Figure from "../figure/Figure";
import { MoveSlice } from "./../../store/reducers/moveSlice";
import clsx from "clsx";
import gameHelper from "../../helpers/GameHelper";
import { TurnSlice } from "./../../store/reducers/turnSlice";
import { BoardSlice } from "./../../store/reducers/boardSlice";
import game from "../../game/Game";
import { GameStateSlice } from "./../../store/reducers/gameStateSlice";

interface GameProps {
  board: TBoard;
}

const Game: React.FC<GameProps> = ({ board }) => {
  const { chosenFigure, possibleMoves } = useAppSelector((store) => store.move);
  const { yourTurn } = useAppSelector((store) => store.turn);
  const gameState = useAppSelector((store) => store.game.state);
  const dispatch = useAppDispatch();
  const checkPossibleMove = React.useCallback(
    (row: number, col: number) => {
      return Boolean(
        possibleMoves.find((item) => item.row === row && item.col === col)
      );
    },
    [possibleMoves]
  );
  const onFigureBlackClick = (row: number, col: number) => {
    if (yourTurn) {
      dispatch(MoveSlice.actions.chooseFigure({ row, col }));
      const calculatedPossibleMoves = gameHelper.calculatePossibleMoves(
        row,
        col,
        board
      );
      dispatch(MoveSlice.actions.setPossibleMoves(calculatedPossibleMoves));
    }
  };

  const computerTurn = (boardLocal: number[][]) => {
    if (!yourTurn) {
      const [moveToDo, moveFrom] = game.computerTurn(boardLocal);
      dispatch(
        BoardSlice.actions.moveFrom({
          row: moveFrom.row,
          col: moveFrom.col,
        })
      );
      dispatch(
        BoardSlice.actions.setWhite({ row: moveToDo.row, col: moveToDo.col })
      );
      const boardCopy: number[][] = [];
      for (let i = 0; i < 5; i++) {
        boardCopy.push([...boardLocal[i]]);
      }
      boardCopy[moveToDo.row][moveToDo.col] = 1;
      boardCopy[moveFrom.row][moveFrom.col] = 0;
      gameHelper.addAITurn(moveFrom, moveToDo);
      if (gameHelper.checkForWin(boardCopy, SCORE.AI_WIN)) {
        dispatch(GameStateSlice.actions.setResultOfGame("whiteWin"));
      } else if (gameHelper.checkForDraw()) {
        dispatch(GameStateSlice.actions.setResultOfGame("draw"));
      } else {
        dispatch(TurnSlice.actions.giveTurn(true));
      }
    }
  };
  React.useEffect(() => {
    if (!yourTurn) {
      computerTurn(board);
    }
  }, [yourTurn]);

  const playerTurn = (i: number, j: number) => {
    if (yourTurn && gameState === "going") {
      if (checkPossibleMove(i, j)) {
        if (chosenFigure) {
          dispatch(
            BoardSlice.actions.moveFrom({
              row: chosenFigure.row,
              col: chosenFigure.col,
            })
          );
          dispatch(BoardSlice.actions.setBlack({ row: i, col: j }));
          dispatch(MoveSlice.actions.chooseFigure(null));
          dispatch(MoveSlice.actions.setPossibleMoves([]));
          const boardCopy: number[][] = [];
          for (let i = 0; i < 5; i++) {
            boardCopy.push([...board[i]]);
          }
          boardCopy[i][j] = -1;
          boardCopy[chosenFigure.row][chosenFigure.col] = 0;
          gameHelper.addPlayerTurn(chosenFigure, { row: i, col: j });
          if (gameHelper.checkForWin(boardCopy, SCORE.USER_WIN)) {
            dispatch(GameStateSlice.actions.setResultOfGame("blackWin"));
          } else if (gameHelper.checkForDraw()) {
            dispatch(GameStateSlice.actions.setResultOfGame("draw"));
          } else {
            dispatch(TurnSlice.actions.giveTurn(false));
          }
        }
      } else {
        dispatch(MoveSlice.actions.chooseFigure(null));
        dispatch(MoveSlice.actions.setPossibleMoves([]));
      }
    }
  };
  return (
    <>
      {board.map((row, i) => {
        return (
          <div className="row" key={i}>
            {row.map((cell, j) => {
              return (
                <div
                  className={clsx({
                    cell: true,
                    green: checkPossibleMove(i, j),
                  })}
                  key={j}
                  onClick={(e) => {
                    playerTurn(i, j);
                  }}
                >
                  {cell === 1 ? (
                    <Figure
                      color={Colors.white}
                      chosen={i === chosenFigure?.row && j === chosenFigure.col}
                    />
                  ) : null}
                  {cell === -1 ? (
                    <Figure
                      color={Colors.black}
                      chosen={i === chosenFigure?.row && j === chosenFigure.col}
                      onFigureClick={(e) => {
                        e.stopPropagation();
                        if (gameState === "going") {
                          onFigureBlackClick(i, j);
                        }
                      }}
                    />
                  ) : null}
                </div>
              );
            })}
          </div>
        );
      })}
    </>
  );
};

export default Game;
