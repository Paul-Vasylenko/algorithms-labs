import React from "react";
import "./App.css";
import Board from "./components/board/Board";
import { useAppSelector } from "./hooks/redux";

function App() {
  const board = useAppSelector((store) => store.board);
  const gameState = useAppSelector((store) => store.game.state);
  return (
    <>
      <button
        onClick={() =>
          alert(`The players have three pieces each. They are placed as shown in the figure.
    Movement: A piece slides orthogonally or diagonally until stopped by
    an occupied square or the border of the board. Black always moves first.
    
    Objective: To get three in a row, orthogonally or diagonally. The row must be connected.`)
        }
      >
        Rules
      </button>
      <div className="app">
        <h1>Neutreeko</h1>
        {gameState === "going" ? <p>The game is hard..</p> : null}
        {gameState === "blackWin" ? <p>Black win the game!</p> : null}
        {gameState === "whiteWin" ? <p>white win the game!</p> : null}
        {gameState === "draw" ? <p>Draw!</p> : null}

        <Board board={board} />
      </div>
    </>
  );
}

export default App;
