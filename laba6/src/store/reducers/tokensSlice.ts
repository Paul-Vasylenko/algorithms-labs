import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { ICell, IMove } from "./boardSlice";

interface ITokens {
  ai: {
    tokens: ICell[];
  };
  player: {
    tokens: ICell[];
  };
}

const initialState: ITokens = {
  ai: {
    tokens: [],
  },
  player: {
    tokens: [],
  },
};

export const TokensSlice = createSlice({
  name: "tokensState",
  initialState,
  reducers: {
    moveTokenAI: (state, { payload }: PayloadAction<IMove>) => {
      state.ai.tokens = state.ai.tokens.filter(
        (token) =>
          !(token.col === payload.from?.col && token.row === payload.from.row)
      );
      state.ai.tokens.push(payload.to);
    },
    setTokenAI: (state, { payload }: PayloadAction<IMove>) => {
      state.ai.tokens.push(payload.to);
    },
    deleteTokenAI: (state, { payload }: PayloadAction<ICell>) => {
      const newState = state.ai.tokens.filter(
        (token) => !(token.col === payload.col && token.row === payload.row)
      );
      state.ai.tokens = newState ?? [];
    },
    moveTokenPlayer: (state, { payload }: PayloadAction<IMove>) => {
      state.player.tokens = state.player.tokens.filter(
        (token) =>
          !(token.col === payload.from?.col && token.row === payload.from.row)
      );
      state.player.tokens.push(payload.to);
    },
    setTokenPlayer: (state, { payload }: PayloadAction<IMove>) => {
      state.player.tokens.push(payload.to);
    },
    deleteTokenPlayer: (state, { payload }: PayloadAction<ICell>) => {
      const newState = state.player.tokens.filter(
        (token) => !(token.col === payload.col && token.row === payload.row)
      );
      state.player.tokens = newState ?? [];
    },
  },
});

export default TokensSlice.reducer;
//0-0
