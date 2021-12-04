import * as React from "react";
import { Colors } from "../../types/colors-enum";
import "./figure.css";
import clsx from "clsx";

interface FigureProps {
  color: Colors;
  chosen?: boolean;
  onFigureClick?: (e: any) => void;
}

const Figure: React.FC<FigureProps> = ({ color, chosen, onFigureClick }) => {
  return (
    <div
      className={clsx({
        figure: true,
        white: color === Colors.white,
        black: color === Colors.black,
        chosen,
      })}
      onClick={onFigureClick}
    ></div>
  );
};

export default Figure;
