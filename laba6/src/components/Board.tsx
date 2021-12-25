import * as React from "react";
import { StringOrNumber } from "../store/reducers/boardSlice";
import "./board.css";
import Cell from "./Cell";

interface BoardProps {
  board: StringOrNumber[][];
}

const Board: React.FC<BoardProps> = ({ board }) => {
  return (
    <div className="board">
      {board.map((row, i) => {
        return row.map((col, j) => {
          return <Cell row={i} col={j} key={i + j} />;
        });
      })}
    </div>
  );
};

export default Board;
