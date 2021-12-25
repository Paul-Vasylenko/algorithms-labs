import * as React from "react";
import DiceComp from "react-dice-roll";
import { useAppSelector } from "../hooks/redux";
interface DiceProps {
  onDiceRoll: (value: number) => void;
}

const Dice: React.FC<DiceProps> = ({ onDiceRoll }) => {
  const { myTurn } = useAppSelector((store) => store.turn);
  const { rolledThisTurn } = useAppSelector((store) => store.game);

  return (
    <div className="dice">
      <DiceComp
        size={60}
        onRoll={(value) => onDiceRoll(value)}
        disabled={!myTurn || rolledThisTurn}
        // cheatValue={6}
      />
    </div>
  );
};

export default Dice;
