import React, { useState } from 'react';

import { createStage, checkCollision } from '../GameManager';
import { StyledTetrisWrapper, StyledTetris } from './StyledComponents';

import { useInterval } from '../hooks/useInterval';
import { usePlayer } from '../hooks/usePlayer';
import { useStage } from '../hooks/useStage';
import { useGameStatus } from '../hooks/useGameStatus';

import Stage from './Stage';
import Display from './Display';
import StartButton from './StartButton';

const Board = () => {
  const [dropTime, setDropTime] = useState(null);
  const [gameOver, setGameOver] = useState(false);

  const [player, updatePlayerPos, reset, playerRotate] = usePlayer();
  const [stage, setStage, rowsCleared] = useStage(player, reset);
  const [score, setScore, rows, setRows, level, setLevel] = useGameStatus(
    rowsCleared
  );

  const moveTetronimo = dir => {
    if (!checkCollision(player, stage, { x: dir, y: 0 })) { // allow movement of the tetronimo if it doesn't collide with another
      updatePlayerPos({ x: dir, y: 0 });
    }
  };

  const keyUp = ({ keyCode }) => {
    if (!gameOver) {
      // Key goes up if user does not hold down button
      if (keyCode === 40) {
        setDropTime(1000 / (level + 1));
      }
    }
  };

   // Reset window and start over
  const startGame = () => {
    
    setStage(createStage());
    setDropTime(1000);
    reset();
    setScore(0);
    setLevel(1);
    setRows(0);
    setGameOver(false);
  };

  const drop = () => {
    // Increase level and speed of tetronimos when player has cleared 10 rows
    if (rows > (level + 1) * 10) {
      setLevel(prev => prev + 1);
      setDropTime(1000 / (level + 1) + 100);
    }

    if (!checkCollision(player, stage, { x: 0, y: 1 })) {
      updatePlayerPos({ x: 0, y: 1, collided: false });
    } else {
      // If tetronimo reaches the top the game ends
      if (player.pos.y < 1) {
        setGameOver(true);
        setDropTime(null);
      }
      updatePlayerPos({ x: 0, y: 0, collided: true });
    }
  };

  const dropTetronimo = () => {
    // We don't need to run the interval when we use the arrow down to
    // move the tetromino downwards. So deactivate it for now.
    setDropTime(null);
    drop();
  };

  // Start game
  useInterval(() => {
    drop();
  }, dropTime);

  const move = ({ keyCode }) => {
    if (!gameOver) {
      if (keyCode === 37) {          // move tetronimo left
        moveTetronimo(-1);
      } else if (keyCode === 39) {   // move tetronimo right
        moveTetronimo(1);
      } else if (keyCode === 40) {   // move tetronimo down
        dropTetronimo();
      } else if (keyCode === 38) {   // rotate on up key
        playerRotate(stage, 1);
      }
    }
  };

  return (
    <StyledTetrisWrapper
      role="button"
      tabIndex="0"
      onKeyDown={e => move(e)}
      onKeyUp={keyUp}
    >
      <StyledTetris>
        <Stage stage={stage} />
        <aside>
          {gameOver ? (
            <Display gameOver={gameOver} text= "Game Over" />
          ) : (
            <div>
              <Display text={`Score: ${score}`} />
              <Display text={`Level: ${level}`} />
              <Display text={`Lines: ${rows}`} />

            </div>
          )}
          <StartButton callback={startGame} />
        </aside>
      </StyledTetris>
    </StyledTetrisWrapper>
  );
};

export default Board;