import { createSlice, PayloadAction } from "@reduxjs/toolkit";

interface IBoardState {
  board: StringOrNumber[][];
}

export type StringOrNumber = string | number;

const initialState: IBoardState = {
  board: [
    ["X", "X", "X", "X", "X", "X", 0, 0, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 5, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 0, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 0, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 0, 1, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 0, 0, "X", "X", "X", "X", "X", "X"],
    [0, 0, 0, 0, 0, 0, "X", "WC", "X", 0, 0, 0, 0, 0, 0],
    [0, "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", 0],
    [0, 0, 0, 0, 0, 0, "X", "WP", "X", 0, 0, 0, 0, 0, 0],
    ["X", "X", "X", "X", "X", "X", 0, 5, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 5, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 5, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 5, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 5, 0, "X", "X", "X", "X", "X", "X"],
    ["X", "X", "X", "X", "X", "X", 0, 0, 0, "X", "X", "X", "X", "X", "X"],
  ],
};

export interface ICell {
  row: number;
  col: number;
}
export interface IMove {
  from?: ICell;
  to: ICell;
}

export const BoardSlice = createSlice({
  name: "boardState",
  initialState,
  reducers: {
    moveYellow: (state, { payload }: PayloadAction<IMove>) => {
      const { from, to } = payload;
      if (from) {
        state.board[from.row][from.col] = 0;
      }
      state.board[to.row][to.col] = -1;
    },
    moveRed: (state, { payload }: PayloadAction<IMove>) => {
      const { from, to } = payload;
      if (from) {
        state.board[from.row][from.col] = 0;
      }
      state.board[to.row][to.col] = 1;
    },
    killOne: (state, { payload }: PayloadAction<ICell>) => {
      state.board[payload.row][payload.col] = 0;
    },
  },
});

export default BoardSlice.reducer;
