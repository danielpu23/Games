#ifndef BOARD_H
#define BOARD_H

#define NUMROWS 7
#define NUMCOLS 8

class Board{
private:
    int board[NUMROWS][NUMCOLS];
    int boardHeight[NUMCOLS];
public:
    Board();
    void initializeBoard();
    bool checkLegalDrop(int col);
    bool checkWin(int row, int col, char c);
    bool dropDisc(int col, char c);
    void printBoard();
};

#endif // BOARD_H
