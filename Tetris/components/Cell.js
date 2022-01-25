import React from 'react';
import { StyledCell } from './StyledComponents';
import { TETROMINOES } from '../Tetrominoes';

// React.memo makes sure we only re-render the changed cells
const Cell = ({ type }) => (
  <StyledCell type={type} color={TETROMINOES[type].color}>
    {console.log('rerender cell')}
  </StyledCell>
);

export default React.memo(Cell);