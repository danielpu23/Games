import styled from 'styled-components';

import bgImage from '../background.png';

// adds styles to visible components

export const StyledCell = styled.div`
  width: auto;
  /* border-radius: 6px; */
  background: rgba(${props => props.color}, 1);
  border: ${props => (props.type === 0 ? '0px solid' : '5px solid')};
  border-top-color: rgba(${props => props.color}, 0.1);
  border-bottom-color: rgba(${props => props.color}, 0.1);
  border-left-color: rgba(${props => props.color}, 0.3);
  border-right-color: rgba(${props => props.color}, 0.3);
`;

export const StyledDisplay = styled.div`
  box-sizing: border-box;
  display: flex;
  align-items: center;
  margin: 0 0 30px 0;
  padding: 20px;
  border: 3px solid #444;
  min-height: 40px;
  width: 100%;
  border-radius: 10px;
  color: ${props => (props.gameOver ? 'red' : '#555')};
  background: #000;
  font-family: Pixel, Arial, Helvetica, sans-serif;
  font-size: 1rem;
`;

export const StyledGameOver = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 20px;
  color: #888;
  background: #000;
  position: absolute;
  top: 200px;
  left: 75px);
  width: 150px;
  height: 100px;
  z-index: 1000;
  border: 2px solid #888;
  font-family: Pixel, Arial, Helvetica, sans-serif;
`;

export const StyledStage = styled.div`
  display: grid;
  grid-template-rows: repeat(
    ${props => props.height},
    calc(25vw / ${props => props.width})
  );
  grid-template-columns: repeat(${props => props.width}, 1fr);
  grid-gap: 1px;
  border: 2px solid #444;
  width: 100%;
  max-width: 22vw;
  background: #111;
`;

export const StyledTetrisWrapper = styled.div`
  width: 100vw;
  height: 100vh;
  background: url(${bgImage}) #000;
  background-size: cover;
  overflow: hidden;
`;

export const StyledTetris = styled.div`
  display: flex;
  align-items: flex-start;
  padding: 40px;
  margin: 0 auto;
  max-width: 1000px;
  aside {
    width: 100%;
    max-width: 200px;
    display: block;
    padding: 0 20px;
  }
`;