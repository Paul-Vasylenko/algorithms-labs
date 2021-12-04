export type TBoard = number[][];

export interface ICell {
  row: number;
  col: number;
}

export const SCORE = {
  USER_WIN: -1,
  DRAW: 0,
  AI_WIN: 1,
};
