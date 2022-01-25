export const TETROMINOES = {
    0: { shape: [[0]], color: '0, 0, 0' }, // represents space for shapes

    // 0 represents space that can be taken up by a tetromino after rotation
    I: {
      shape: [[0, 'I', 0, 0],   // cyan I tetronimo
              [0, 'I', 0, 0], 
              [0, 'I', 0, 0], 
              [0, 'I', 0, 0]],

         color: '80, 230, 230',
    },
    J: { 
        shape: [[0, 'J', 0],    // blue J tetronimo
                [0, 'J', 0], 
                ['J', 'J', 0]], 
       
        color: '35, 95, 225' },
    L: {
        shape: [[0, 'L', 0],   // orange L tetronimo
               [0, 'L', 0], 
               [0, 'L', 'L']],

        color: '225, 175, 35',
    },

    S: { 
        shape: [[0, 'S', 'S'],  // green S tetronimo
               ['S', 'S', 0], [0, 0, 0]],
               
        color: '50, 200, 55' },

    Z: { 
          shape: [['Z', 'Z', 0],    // red Z tetronimo
                  [0, 'Z', 'Z'], 
                  [0, 0, 0]], 
    
          color: '227, 78, 78' },

    T: {
        shape: [[0, 0, 0], 
                ['T', 'T', 'T'],  // purple T tetronimo
                [0, 'T', 0]],
        color: '135, 60, 200',
    },

    O: {
      shape: [['O', 'O'],   // yellow O tetronimo
             ['O', 'O']], 
      
      color: '223, 217, 36' }
   
  };
  
  export const randomTetromino = () => { // generate a random tetronimo
    const tetromino = 'IJLSZTO';
    const rand = tetromino[Math.floor(Math.random() * tetromino.length)];
    return TETROMINOES[rand];
  };