import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { ICell } from "../../types/board";
interface IMoveState {
  chosenFigure: ICell | null;
  possibleMoves: ICell[];
}

const initialState: IMoveState = {
  chosenFigure: null,
  possibleMoves: [],
};

export const MoveSlice = createSlice({
  name: "move",
  initialState,
  reducers: {
    chooseFigure: (state, action: PayloadAction<ICell | null>) => {
      state.chosenFigure = action.payload;
    },
    setPossibleMoves: (state, action: PayloadAction<ICell[]>) => {
      state.possibleMoves = action.payload;
    },
  },
});

export default MoveSlice.reducer;
