import { createSlice, PayloadAction } from "@reduxjs/toolkit";

const initialState = {
  yourTurn: true,
};

export const TurnSlice = createSlice({
  name: "turn",
  initialState,
  reducers: {
    giveTurn: (state, action: PayloadAction<boolean>) => {
      state.yourTurn = action.payload;
    },
  },
});

export default TurnSlice.reducer;
