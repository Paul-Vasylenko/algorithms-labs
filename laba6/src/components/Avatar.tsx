import * as React from "react";
import './avatar.css'


interface AvatarProps {
  img: string;
  name: string;
}

const Avatar: React.FC<AvatarProps> = ({ img, name }) => {
  return (
    <div className="avatar">
      <img src={img} alt="avatar" />
      <p>{name}</p>
    </div>
  );
};

export default Avatar;
