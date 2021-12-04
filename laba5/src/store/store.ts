import { combineReducers, configureStore } from "@reduxjs/toolkit";
import boardReducer from "./reducers/boardSlice";
import turnReducer from "./reducers/turnSlice";
import moveReducer from "./reducers/moveSlice";
import GameStateReducer from "./reducers/gameStateSlice";

const rootReducer = combineReducers({
  turn: turnReducer,
  board: boardReducer,
  move: moveReducer,
  game: GameStateReducer,
});

export const setupStore = () => {
  return configureStore({
    reducer: rootReducer,
  });
};

export type RootState = ReturnType<typeof rootReducer>;
export type AppStore = ReturnType<typeof setupStore>;
export type AppDispatch = AppStore["dispatch"];
