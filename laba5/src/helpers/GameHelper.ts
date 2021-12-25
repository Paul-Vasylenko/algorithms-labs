import { ICell } from "../types/board";

interface ITurnInfo {
  from: ICell;
  to: ICell;
}

class GameHelper {
  private lastThreePlayerTurns: ITurnInfo[] = [];
  private lastThreeAITurns: ITurnInfo[] = [];

  calculatePossibleMoves = (
    row: number,
    col: number,
    board: number[][]
  ): ICell[] => {
    const result: ICell[] = [];
    //TOP
    for (let i = row; i > 0; i--) {
      if (board[i - 1][col] !== 0) {
        result.push({ row: i, col });
        break;
      } else if (i - 1 === 0) {
        result.push({ row: i - 1, col });
        break;
      }
    }
    //BOT
    for (let i = row; i < 4; i++) {
      if (board[i + 1][col] !== 0) {
        result.push({ row: i, col });
        break;
      } else if (i + 1 === 4) {
        result.push({ row: i + 1, col });
        break;
      }
    }
    //LEFT
    for (let i = col; i > 0; i--) {
      if (board[row][i - 1] !== 0) {
        result.push({ row, col: i });
        break;
      } else if (i - 1 === 0) {
        result.push({ row, col: i - 1 });
        break;
      }
    }
    //RIGHT
    for (let i = col; i < 4; i++) {
      if (board[row][i + 1] !== 0) {
        result.push({ row, col: i });
        break;
      } else if (i + 1 === 4) {
        result.push({ row, col: i + 1 });
        break;
      }
    }
    //TOP RIGHT DIAGONAL
    for (let i = row, j = col; i > 0 && j < 4; i--, j++) {
      if (board[i - 1][j + 1] !== 0) {
        if (i !== row || j !== col) result.push({ row: i, col: j });
        break;
      } else if (i - 1 === 0 || j + 1 === 4) {
        result.push({ row: i - 1, col: j + 1 });
        break;
      }
    }
    //TOP LEFT DIAGONAL
    for (let i = row, j = col; i > 0 && j > 0; i--, j--) {
      if (board[i - 1][j - 1] !== 0) {
        if (i !== row || j !== col) result.push({ row: i, col: j });
        break;
      } else if (i - 1 === 0 || j - 1 === 0) {
        result.push({ row: i - 1, col: j - 1 });
        break;
      }
    }
    //BOT RIGHT DIAGONAL
    for (let i = row, j = col; i < 4 && j < 4; i++, j++) {
      if (board[i + 1][j + 1] !== 0) {
        if (i !== row || j !== col) result.push({ row: i, col: j });
        break;
      } else if (i + 1 === 4 || j + 1 === 4) {
        result.push({ row: i + 1, col: j + 1 });
        break;
      }
    }
    //BOT LEFT DIAGONAL
    for (let i = row, j = col; i < 4 && j > 0; i++, j--) {
      if (board[i + 1][j - 1] !== 0) {
        if (i !== row || j !== col) result.push({ row: i, col: j });
        break;
      } else if (i + 1 === 4 || j - 1 === 0) {
        result.push({ row: i + 1, col: j - 1 });
        break;
      }
    }
    return result.filter((cell) => {
      if (!(cell.row === row && cell.col === col)) return cell;
    });
  };
  checkForWin = (board: number[][], side: number): boolean => {
    //left -> right
    for (let i = 0; i < 5; i++) {
      let sum = 0;
      for (let j = 0; j < 5; j++) {
        if (board[i][j] === side) {
          sum += board[i][j];
        }
      }
      if (sum === side * 3) {
        const resultCollumn = [];
        for (let k = 0; k < 5; k++) resultCollumn.push(board[i][k]);
        // console.log(resultCollumn.join(""));

        let count = 0;
        for (let m = 0; m < resultCollumn.length - 1; m++) {
          if (resultCollumn[m] === side && resultCollumn[m + 1] === side)
            count++;
        }
        if (count === 2) {
          return true;
        }
      }
    }
    //top -> bot
    for (let i = 0; i < 5; i++) {
      let sum = 0;
      for (let j = 0; j < 5; j++) {
        if (board[j][i] === side) {
          sum += board[j][i];
        }
      }
      if (sum === side * 3) {
        const resultCollumn = [];
        for (let k = 0; k < 5; k++) resultCollumn.push(board[k][i]);
        // console.log(resultCollumn.join(""));

        let count = 0;
        for (let m = 0; m < resultCollumn.length - 1; m++) {
          if (resultCollumn[m] === side && resultCollumn[m + 1] === side)
            count++;
        }
        if (count === 2) {
          return true;
        }
      }
    }
    // right top diagonal
    for (let i = 2; i < 5; i++) {
      let sum = 0;
      for (let j = 0; j < i + 1; j++) {
        if (board[i - j][j] === side) {
          sum += board[i - j][j];
        }
      }
      if (sum === side * 3) {
        const resultDiagonal = [];
        for (let k = 0; k < i + 1; k++) {
          resultDiagonal.push(board[i - k][k]);
          // console.log(resultDiagonal.join(""));

          let count = 0;
          for (let m = 0; m < resultDiagonal.length - 1; m++) {
            if (resultDiagonal[m] === side && resultDiagonal[m + 1] === side)
              count++;
          }
          if (count === 2) {
            return true;
          }
        }
      }
    }

    // right bot diagonal
    for (let j = 2; j >= 0; j--) {
      let sum = 0;
      for (let i = 0; i < 5 - j; i++) {
        if (board[i][j + i] === side) {
          sum += board[i][j + i];
        }
      }
      if (sum === side * 3) {
        const resultDiagonal = [];
        for (let k = 0; k < 5 - j; k++) {
          resultDiagonal.push(board[k][j + k]);
          // console.log(resultDiagonal.join(""));
          let count = 0;
          for (let m = 0; m < resultDiagonal.length - 1; m++) {
            if (resultDiagonal[m] === side && resultDiagonal[m + 1] === side)
              count++;
          }
          if (count === 2) {
            return true;
          }
        }
      }
    }
    return false;
  };

  addPlayerTurn = (from: ICell, to: ICell) => {
    if (this.lastThreePlayerTurns.length === 3) {
      this.lastThreePlayerTurns.shift();
    }
    this.lastThreePlayerTurns.push({ from, to });
  };

  addAITurn = (from: ICell, to: ICell) => {
    if (this.lastThreeAITurns.length === 3) {
      this.lastThreeAITurns.shift();
    }
    this.lastThreeAITurns.push({ from, to });
  };

  checkForDraw = (): boolean => {
    console.log("Last 3 turns human", this.lastThreePlayerTurns);
    console.log("Last 3 turns AI", this.lastThreeAITurns);

    if (
      this.lastThreeAITurns.length < 3 ||
      this.lastThreePlayerTurns.length < 3
    )
      return false;
    const aiFirst = this.lastThreeAITurns[0];
    const sameAITurns = this.lastThreeAITurns.filter(
      (info) =>
        info.from.row === aiFirst.from.row &&
        info.from.col === aiFirst.from.col &&
        info.to.row === aiFirst.to.row &&
        info.to.col === aiFirst.to.col
    );
    if (sameAITurns.length !== 2) return false;
    if (
      this.lastThreeAITurns[0].from.col !== this.lastThreeAITurns[1].to.col ||
      this.lastThreeAITurns[0].from.row !== this.lastThreeAITurns[1].to.row
    )
      return false;

    const playerFirst = this.lastThreePlayerTurns[0];
    const samePlayerTurns = this.lastThreePlayerTurns.filter(
      (info) =>
        info.from.row === playerFirst.from.row &&
        info.from.col === playerFirst.from.col &&
        info.to.row === playerFirst.to.row &&
        info.to.col === playerFirst.to.col
    );
    if (samePlayerTurns.length !== 2) return false;
    if (
      this.lastThreePlayerTurns[0].from.col !==
        this.lastThreePlayerTurns[1].to.col ||
      this.lastThreePlayerTurns[0].from.row !==
        this.lastThreePlayerTurns[1].to.row
    )
      return false;
    return true;
  };
  estimateNow = (board: number[][]): number => {
    const side = 1;
    let result = 0;
    //left -> right
    for (let i = 0; i < 5; i++) {
      let sum = 0;
      for (let j = 0; j < 5; j++) {
        if (board[i][j] === side) {
          sum += board[i][j];
        }
      }
      if (sum === 2) result += 0.2;
      else if (sum === 3) result += 0.3;
    }
    //top -> bot
    for (let i = 0; i < 5; i++) {
      let sum = 0;
      for (let j = 0; j < 5; j++) {
        if (board[j][i] === 1) {
          sum += board[j][i];
        }
      }
      if (sum === 2) result += 0.2;
      else if (sum === 3) result += 0.3;
    }
    // right top diagonal
    for (let i = 2; i < 5; i++) {
      let sum = 0;
      for (let j = 0; j < i + 1; j++) {
        if (board[i - j][j] === side) {
          sum += board[i - j][j];
        }
      }
      if (sum === 2) result += 0.2;
      else if (sum === 3) result += 0.3;
    }

    // right bot diagonal
    for (let j = 2; j >= 0; j--) {
      let sum = 0;
      for (let i = 0; i < 5 - j; i++) {
        if (board[i][j + i] === side) {
          sum += board[i][j + i];
        }
      }
      if (sum === 2) result += 0.2;
      else if (sum === 3) result += 0.3;
    }
    return result;
  };
}

export default new GameHelper();
