import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { ICell, TBoard } from "../../types/board";

const initialState: TBoard = [
  [0, 1, 0, 1, 0],
  [0, 0, -1, 0, 0],
  [0, 0, 0, 0, 0],
  [0, 0, 1, 0, 0],
  [0, -1, 0, -1, 0],
];

// const initialState: TBoard = [
//   [0, 0, 0, 0, 0],
//   [0, 0, 0, 0, -1],
//   [0, 0, 0, 0, 0],
//   [0, 0, 0, 0, -1],
//   [0, 0, 0, 0, -1],
// ];

export const BoardSlice = createSlice({
  name: "board",
  initialState,
  reducers: {
    moveFrom: (state, action: PayloadAction<ICell>) => {
      const { row, col } = action.payload;
      state[row][col] = 0;
    },
    setWhite: (state, action: PayloadAction<ICell>) => {
      const { row, col } = action.payload;
      state[row][col] = 1;
    },
    setBlack: (state, action: PayloadAction<ICell>) => {
      const { row, col } = action.payload;
      state[row][col] = -1;
    },
  },
});

export default BoardSlice.reducer;
