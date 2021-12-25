import * as React from "react";
import "./token.css";

interface TokenProps {
  color: string;
}

const Token: React.FC<TokenProps> = ({ color }) => {
  if (color === "yellow") {
    return (
      <div className="token">
        <img src="./yellowtoken.webp" alt={color} width={45} height={45} />
      </div>
    );
  }
  if (color === "red") {
    return (
      <div className="token">
        <img src="./redtoken.png" alt={color} width={45} height={45} />
      </div>
    );
  }
  return <div></div>;
};

export default Token;
