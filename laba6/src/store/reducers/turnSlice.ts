import { createSlice, PayloadAction } from "@reduxjs/toolkit";

interface ITurnState {
  myTurn: boolean;
}

export type StringOrNumber = string | number;

const initialState: ITurnState = {
  myTurn: true,
};

export const TurnSlice = createSlice({
  name: "turnState",
  initialState,
  reducers: {
    changeTurn: (state) => {
      state.myTurn = !state.myTurn;
    },
  },
});

export default TurnSlice.reducer;
