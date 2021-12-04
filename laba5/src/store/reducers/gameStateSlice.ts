import { createSlice, PayloadAction } from "@reduxjs/toolkit";

type TGameState = "going" | "blackWin" | "whiteWin" | "draw";
interface IGameState {
  state: TGameState;
}

const initialState: IGameState = {
  state: "going",
};

export const GameStateSlice = createSlice({
  name: "gameState",
  initialState,
  reducers: {
    setResultOfGame: (state, action: PayloadAction<TGameState>) => {
      state.state = action.payload;
    },
  },
});

export default GameStateSlice.reducer;
