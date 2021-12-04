import { ICell } from "../types/board";
import GameHelper from "../helpers/GameHelper";
import { SCORE } from "./../types/board";

class Game {
  private USER_TURN = false;
  private AI_TURN = true;
  computerTurn(board: number[][]): ICell[] {
    let result: ICell[] = [];
    let bestScore = -2;
    const boardCopy: number[][] = [];
    for (let i = 0; i < 5; i++) {
      boardCopy.push([...board[i]]);
    }
    const exception = {};
    try {
      boardCopy.forEach((row, i) => {
        row.forEach((cell, j) => {
          if (cell === 1) {
            const possibleMoves = GameHelper.calculatePossibleMoves(
              i,
              j,
              boardCopy
            );
            possibleMoves.forEach((possibleMove) => {
              const { row: moveRow, col } = possibleMove;
              boardCopy[moveRow][col] = 1;
              boardCopy[i][j] = 0;
              const score = this.minimax(boardCopy, 0, this.USER_TURN);
              if (
                score === 1 &&
                GameHelper.checkForWin(boardCopy, SCORE.AI_WIN)
              ) {
                result = [possibleMove, { row: i, col: j }];
                throw exception;
              }
              boardCopy[moveRow][col] = 0;
              boardCopy[i][j] = 1;
              if (score >= bestScore) {
                bestScore = score;
                result = [possibleMove, { row: i, col: j }];
              }
            });
          }
        });
      });
    } catch (e) {
      if (e !== exception) throw e;
    }
    return result;
  }

  minimax = (board: number[][], depth: number, isAiTurn: boolean): number => {
    if (GameHelper.checkForWin(board, SCORE.USER_WIN)) {
      return SCORE.USER_WIN;
    } else if (GameHelper.checkForWin(board, SCORE.AI_WIN)) {
      return SCORE.AI_WIN;
    } else if (GameHelper.checkForDraw()) {
      return SCORE.DRAW;
    } else if (depth === 5) {
      return GameHelper.estimateNow(board);
    }
    let bestScore = isAiTurn ? -20 : 20;
    if (isAiTurn) {
      //chose move that is the best for us
      board.forEach((row, i) => {
        row.forEach((cell, j) => {
          if (cell === 1) {
            const possibleMoves = GameHelper.calculatePossibleMoves(
              i,
              j,
              board
            );
            possibleMoves.forEach((possibleMove) => {
              const { row: moveRow, col } = possibleMove;
              board[moveRow][col] = 1;
              board[i][j] = 0;
              const score = this.minimax(board, depth + 1, this.USER_TURN);
              board[moveRow][col] = 0;
              board[i][j] = 1;
              bestScore = Math.max(score, bestScore);
            });
          }
        });
      });
    } else {
      //enemy chooses the move the is the best for him and worst for us
      board.forEach((row, i) => {
        row.forEach((cell, j) => {
          if (cell === -1) {
            const possibleMoves = GameHelper.calculatePossibleMoves(
              i,
              j,
              board
            );
            possibleMoves.forEach((possibleMove) => {
              const { row: moveRow, col } = possibleMove;
              board[moveRow][col] = -1;
              board[i][j] = 0;
              const score = this.minimax(board, depth + 1, this.AI_TURN);
              board[moveRow][col] = 0;
              board[i][j] = -1;
              bestScore = Math.min(score, bestScore);
            });
          }
        });
      });
    }

    return bestScore;
  };
}

export default new Game();
