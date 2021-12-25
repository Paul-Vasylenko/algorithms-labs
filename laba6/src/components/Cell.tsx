import * as React from "react";
import { useAppSelector } from "../hooks/redux";
import "./cell.css";
import Token from "./Token";
import { useAppDispatch } from "./../hooks/redux";
import { BasesSlice } from "./../store/reducers/basesSlice";
import { BoardSlice } from "./../store/reducers/boardSlice";
import { TurnSlice } from "./../store/reducers/turnSlice";
import { GameSlice } from "../store/reducers/gameSlice";
import { moveToken } from "../App";
import { TokensSlice } from "../store/reducers/tokensSlice";

interface CellProps {
  row: number;
  col: number;
}

const Cell: React.FC<CellProps> = ({ row, col }) => {
  const { computer, player } = useAppSelector((store) => store.bases);
  const { board } = useAppSelector((store) => store.board);
  const { myTurn } = useAppSelector((store) => store.turn);
  const { diceValue, rolledAi, rolledThisTurn } = useAppSelector(
    (store) => store.game
  );
  const dispatch = useAppDispatch();

  const moveFromBaseHuman = () => {
    if (myTurn && rolledThisTurn) {
      if (diceValue === 6 && board[13][6] === 0) {
        dispatch(BasesSlice.actions.playerTakeToken());
        dispatch(
          BoardSlice.actions.moveYellow({
            to: {
              row: 13,
              col: 6,
            },
          })
        );
        if (rolledAi) dispatch(GameSlice.actions.changeRolledAI(false));
        if (rolledThisTurn) dispatch(GameSlice.actions.changeRolled(false));
        dispatch(
          TokensSlice.actions.moveTokenPlayer({
            to: {
              row: 13,
              col: 6,
            },
          })
        );
        dispatch(TurnSlice.actions.changeTurn());
      }
    }
  };
  if (board[row][col] === -1) {
    return (
      <div
        className="white"
        onClick={() => {
          if (myTurn && rolledThisTurn) {
            const move = moveToken("yellow", board, diceValue, row, col);
            const { row: toRow, col: toCol } = move;
            if (!move) {
              dispatch(GameSlice.actions.changeRolledAI(false));
              dispatch(GameSlice.actions.changeRolled(false));
              dispatch(TurnSlice.actions.changeTurn());
              return;
            } else if (move.win) {
              dispatch(BoardSlice.actions.killOne({ row, col }));
              dispatch(GameSlice.actions.giveYellowPoint());
              dispatch(
                TokensSlice.actions.deleteTokenPlayer({
                  row: row as number,
                  col: col as number,
                })
              );
            } else if (move.enemyKilled) {
              dispatch(BoardSlice.actions.killOne({ row: toRow, col: toCol }));
              dispatch(BasesSlice.actions.computerLoseToken());
              dispatch(
                TokensSlice.actions.deleteTokenAI({
                  row: toRow as number,
                  col: toCol as number,
                })
              );
            }
            if (!move.win) {
              dispatch(
                BoardSlice.actions.moveYellow({
                  from: { row, col },
                  to: { row: toRow, col: toCol },
                })
              );
              dispatch(
                TokensSlice.actions.moveTokenPlayer({
                  from: {
                    row: row as number,
                    col: col as number,
                  },
                  to: {
                    row: toRow,
                    col: toCol,
                  },
                })
              );
            }
            dispatch(GameSlice.actions.changeRolledAI(false));
            dispatch(GameSlice.actions.changeRolled(false));
            dispatch(TurnSlice.actions.changeTurn());
          }
        }}
      >
        <Token color="yellow" />
      </div>
    );
  }

  if (board[row][col] === 1) {
    return (
      <div className="white">
        <Token color="red" />
      </div>
    );
  }
  //базы
  if (row < 6 && col < 6) {
    return <div className="green"></div>;
  }
  if (row < 6 && col > 8) {
    if (
      (row === 2 && col === 11 && computer > 0) ||
      (row === 2 && col === 12 && computer > 1) ||
      (row === 3 && col === 11 && computer > 2) ||
      (row === 3 && col === 12 && computer > 3)
    ) {
      return (
        <div className="red">
          <Token color="red" />
        </div>
      );
    }
    return <div className="red"></div>;
  }
  if (row > 8 && col < 6) {
    if (
      (row === 11 && col === 2 && player > 0) ||
      (row === 11 && col === 3 && player > 1) ||
      (row === 12 && col === 2 && player > 2) ||
      (row === 12 && col === 3 && player > 3)
    ) {
      return (
        <div className="yellow" onClick={moveFromBaseHuman}>
          <Token color="yellow" />
        </div>
      );
    }
    return <div className="yellow"></div>;
  }
  if (row > 8 && col > 8) {
    return <div className="blue"></div>;
  }
  //линии победы
  if (row > 0 && row < 6 && col === 7) {
    return <div className="red"></div>;
  }
  if (row > 8 && row < 14 && col === 7) {
    return <div className="yellow"></div>;
  }
  if (row === 7 && col > 0 && col < 6) {
    return <div className="green"></div>;
  }
  if (row === 7 && col > 8 && col < 14) {
    return <div className="blue"></div>;
  }
  //стартовые клетки
  if (row === 6 && col === 1) {
    return <div className="green">START</div>;
  }
  if (row === 8 && col === 13) {
    return <div className="blue">START</div>;
  }
  if (row === 13 && col === 6) {
    return <div className="yellow">START</div>;
  }
  if (row === 1 && col === 8) {
    return <div className="red">START</div>;
  }

  if (row > 5 && row < 9 && col > 5 && col < 9) {
    return <div className="black"></div>;
  }
  return <div className="white"></div>;
};

export default Cell;
