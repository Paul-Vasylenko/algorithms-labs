import { createSlice } from "@reduxjs/toolkit";

interface IBasesState {
  player: IBaseNumber;
  computer: IBaseNumber;
}

type IBaseNumber = 0 | 1 | 2 | 3 | 4;

const initialState: IBasesState = {
  player: 4,
  computer: 4,
};

export const BasesSlice = createSlice({
  name: "basesState",
  initialState,
  reducers: {
    playerTakeToken: (state) => {
      if (state.player > 0) {
        state.player = (state.player - 1) as IBaseNumber;
      }
    },
    playerLoseToken: (state) => {
      state.player = (state.player + 1) as IBaseNumber;
    },
    computerTakeToken: (state) => {
      if (state.computer > 0) {
        state.computer = (state.computer - 1) as IBaseNumber;
      }
    },
    computerLoseToken: (state) => {
      state.computer = (state.computer + 1) as IBaseNumber;
    },
  },
});

export default BasesSlice.reducer;
