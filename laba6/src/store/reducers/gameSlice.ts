import { createSlice, PayloadAction } from "@reduxjs/toolkit";

interface IGameState {
  diceValue: number;
  rolledThisTurn: boolean;
  rolledAi: boolean;
  diceAiValue: number;
  state: GameState;
  yellow_points: number;
  red_points: number;
}

type GameState = "going" | "yellow" | "red";

export type StringOrNumber = string | number;

const initialState: IGameState = {
  diceValue: 1,
  rolledThisTurn: false,
  diceAiValue: 1,
  rolledAi: false,
  state: "going",
  yellow_points: 0,
  red_points: 0,
};

export const GameSlice = createSlice({
  name: "gameState",
  initialState,
  reducers: {
    changeDiceValue: (state, action: PayloadAction<number>) => {
      state.diceValue = action.payload;
    },
    changeRolled: (state, { payload }: PayloadAction<boolean>) => {
      state.rolledThisTurn = payload;
    },
    changeDiceValueAI: (state, action: PayloadAction<number>) => {
      state.diceAiValue = action.payload;
    },
    changeRolledAI: (state, { payload }: PayloadAction<boolean>) => {
      state.rolledAi = payload;
    },
    giveYellowPoint: (state) => {
      state.yellow_points += 1;
    },
    giveRedPoint: (state) => {
      state.red_points += 1;
    },
    changeGameState: (state, action: PayloadAction<GameState>) => {
      state.state = action.payload;
    },
  },
});

export default GameSlice.reducer;
