import * as React from "react";
import { TBoard } from "../../types/board";
import Game from "../game/Game";
import "./board.css";

interface BoardProps {
  board: TBoard;
}

const Board: React.FC<BoardProps> = ({ board }) => {
  return (
    <div className="board">
      <div className="empty"></div>
      <div className="top">
        <div className="top-letter">A</div>
        <div className="top-letter">B</div>
        <div className="top-letter">C</div>
        <div className="top-letter">D</div>
        <div className="top-letter">E</div>
      </div>
      <div className="column">
        <div className="column-number">1</div>
        <div className="column-number">2</div>
        <div className="column-number">3</div>
        <div className="column-number">4</div>
        <div className="column-number">5</div>
      </div>
      <div className="game">
        <Game board={board} />
      </div>
    </div>
  );
};

export default Board;
