import React from 'react';
import { StyledDisplay } from './StyledComponents';

const Display = ({ gameOver, text }) => (
  <StyledDisplay gameOver={gameOver}>{text}</StyledDisplay>
);

export default Display;