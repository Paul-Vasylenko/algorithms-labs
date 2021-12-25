import { combineReducers, configureStore } from "@reduxjs/toolkit";
import basesReducer from "./reducers/basesSlice";
import boardReducer from "./reducers/boardSlice";
import turnReducer from "./reducers/turnSlice";
import gameReducer from "./reducers/gameSlice";
import tokensReducer from "./reducers/tokensSlice";

const rootReducer = combineReducers({
  bases: basesReducer,
  board: boardReducer,
  turn: turnReducer,
  game: gameReducer,
  tokens: tokensReducer,
});

export const setupStore = () => {
  return configureStore({
    reducer: rootReducer,
  });
};

export type RootState = ReturnType<typeof rootReducer>;
export type AppStore = ReturnType<typeof setupStore>;
export type AppDispatch = AppStore["dispatch"];
