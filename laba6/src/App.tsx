import React, { useEffect } from "react";
import "./App.css";
import Avatar from "./components/Avatar";
import Board from "./components/Board";
import Dice from "./components/Dice";
import { useAppDispatch, useAppSelector } from "./hooks/redux";
import { BasesSlice } from "./store/reducers/basesSlice";
import { BoardSlice } from "./store/reducers/boardSlice";
import { GameSlice, StringOrNumber } from "./store/reducers/gameSlice";
import { TokensSlice } from "./store/reducers/tokensSlice";
import { TurnSlice } from "./store/reducers/turnSlice";

function getRandomInt(min: number, max: number): number {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

export function moveToken(
  color: string,
  board: StringOrNumber[][],
  distance: number,
  row: number,
  col: number
): any {
  const enemyColor = color === "yellow" ? 1 : -1;
  const myColor = color === "yellow" ? -1 : 1;

  if (distance === 0) {
    if (board[row][col] === myColor) return undefined;
    if (board[row][col] === enemyColor) return { row, col, enemyKilled: true };
    if (board[row][col] === "X") return undefined;
    if (board[row][col] === "WP" || board[row][col] === "WC")
      return { row, col, win: true };

    return { row, col };
  }
  let direction = "";
  if (col === 6) {
    if (row === 9) direction = "topleft";
    else if (row === 0) direction = "right";
    else direction = "top";
  } else if (col === 7) {
    if (color === "yellow" && row === 14) direction = "top";
    if (color === "red" && row === 14) direction = "left";
    if (color === "yellow" && row === 0) direction = "right";
    if (color === "red" && row < 6) direction = "bot";
    if (color === "yellow" && row > 8) direction = "top";
  } else if (col === 8) {
    if (row === 5) direction = "botright";
    else if (row === 14) direction = "left";
    else direction = "bot";
  } else {
    if (row === 6) {
      direction = "right";
      if (col === 5) direction = "topright";
      if (col === 14) direction = "bot";
    }
    if (row === 7) {
      if (col === 0) direction = "top";
      else direction = "bot";
    }
    if (row === 8) {
      direction = "left";
      if (col === 0) direction = "top";
      if (col === 9) direction = "botleft";
    }
  }
  switch (direction) {
    case "top":
      return moveToken(color, board, distance - 1, row - 1, col);
    case "bot":
      return moveToken(color, board, distance - 1, row + 1, col);
    case "left":
      return moveToken(color, board, distance - 1, row, col - 1);
    case "right":
      return moveToken(color, board, distance - 1, row, col + 1);
    case "topleft":
      return moveToken(color, board, distance - 1, row - 1, col - 1);
    case "topright":
      return moveToken(color, board, distance - 1, row - 1, col + 1);
    case "botleft":
      return moveToken(color, board, distance - 1, row + 1, col - 1);
    case "botright":
      return moveToken(color, board, distance - 1, row + 1, col + 1);
  }
}

function App() {
  const { board } = useAppSelector((store) => store.board);
  const { myTurn } = useAppSelector((store) => store.turn);
  const { diceAiValue, yellow_points, red_points, rolledThisTurn, rolledAi } =
    useAppSelector((store) => store.game);
  const { player, computer } = useAppSelector((store) => store.bases);
  const { tokens: aiTokens } = useAppSelector((store) => store.tokens.ai);
  const dispatch = useAppDispatch();
  const moveFromBaseComputer = () => {
    dispatch(BasesSlice.actions.computerTakeToken());
    dispatch(
      BoardSlice.actions.moveRed({
        to: {
          row: 1,
          col: 8,
        },
      })
    );
    dispatch(TokensSlice.actions.setTokenAI({ to: { row: 1, col: 8 } }));

    if (rolledThisTurn) dispatch(GameSlice.actions.changeRolled(false));
    if (rolledAi) dispatch(GameSlice.actions.changeRolledAI(false));
  };
  const onDiceRoll = (value: number) => {
    if (myTurn) {
      if (value !== 6) {
        if (player === 4) {
          dispatch(TurnSlice.actions.changeTurn());
          return;
        }
      }
      dispatch(GameSlice.actions.changeDiceValue(value));
      dispatch(GameSlice.actions.changeRolled(true));
    } else {
      console.log("computer");
    }
  };
  const giveTurn = () => {
    dispatch(TurnSlice.actions.changeTurn());
  };

  const makeAnyPossibleMove = (dice: number) => {
    let move;
    let counter = 0;
    let row, col;
    while (move === undefined && counter < 8 && aiTokens.length > 0) {
      counter++;
      const randomToken = getRandomInt(0, aiTokens.length - 1);

      row = aiTokens[randomToken].row;
      col = aiTokens[randomToken].col;
      move = moveToken("red", board, dice, row, col);
    }
    if (!move) {
      dispatch(GameSlice.actions.changeRolled(false));
      dispatch(GameSlice.actions.changeRolledAI(false));
      return;
    }
    const { row: toRow, col: toCol } = move;
    if (move.enemyKilled) {
      dispatch(BoardSlice.actions.killOne({ row: toRow, col: toCol }));
      dispatch(
        TokensSlice.actions.deleteTokenPlayer({
          row: toRow as number,
          col: toCol as number,
        })
      );
      dispatch(BasesSlice.actions.playerLoseToken());
    } else if (move.win) {
      dispatch(
        BoardSlice.actions.killOne({
          row: row as number,
          col: col as number,
        })
      );
      dispatch(GameSlice.actions.giveRedPoint());
      dispatch(
        TokensSlice.actions.deleteTokenAI({
          row: row as number,
          col: col as number,
        })
      );
    }
    if (!move.win && counter < 8) {
      dispatch(
        TokensSlice.actions.moveTokenAI({
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
      dispatch(
        BoardSlice.actions.moveRed({
          from: { row: row as number, col: col as number },
          to: { row: toRow, col: toCol },
        })
      );
    }
  };

  const computerTurn = () => {
    // 1. Roll the dice
    // const dice = 6;
    const dice = getRandomInt(1, 6);
    dispatch(GameSlice.actions.changeRolledAI(true));
    dispatch(GameSlice.actions.changeDiceValueAI(dice));

    // 2. If dice is not 6
    if (dice !== 6) {
      //   a) there 4 tokens in base - give turn
      if (computer === 4) {
        dispatch(TurnSlice.actions.changeTurn());
        if (rolledThisTurn) dispatch(GameSlice.actions.changeRolled(false));
        return;
      }
      //   b) there are <4 tokens in base - move one of them that is possible
      else {
        makeAnyPossibleMove(dice);
      }
    }

    // 3. If dice is 6
    else {
      //   a) if there are tokens in base
      if (computer > 0) {
        //     - try to move it from base (check start position for being empty)
        if (board[1][8] === 0) {
          //     - if it is empty => move
          moveFromBaseComputer();
        } else {
          //     - if it is not empty => move any of possible tokens
          makeAnyPossibleMove(dice);
        }
      } else {
        //   b) if there are no tokens in base => move any of possible tokens
        makeAnyPossibleMove(dice);
      }
    }
    // 4. Give turn
    dispatch(TurnSlice.actions.changeTurn());
    if (rolledThisTurn) dispatch(GameSlice.actions.changeRolled(false));
    return;
  };
  useEffect(() => {
    if (!myTurn) {
      computerTurn();
    }
  }, [myTurn]);
  return (
    <div className="App">
      <button onClick={giveTurn}>Give turn</button>
      <div className="playerside">
        <Dice onDiceRoll={onDiceRoll} />
        <Avatar img="./person.jpg" name="You" />
        <h3>Score:{yellow_points}</h3>
      </div>
      <Board board={board} />
      <div className="enemyside">
        <Avatar img="./enemy.jpg" name="Enemy" />
        <h1>Dice value: {diceAiValue}</h1>
        <h3>Score:{red_points}</h3>
      </div>
    </div>
  );
}

export default App;
