#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int numRows = 7; // one row allocated to show the column numbers
const int numCols = 8;
char board [numRows][numCols];
int boardHeight[numCols];

void printInstructions(){
    cout << "You will play Connect 4 against a simple AI on a 6x8 board" << endl;

}

// initialize all values on the board
void initializeBoard(){
    char rowNumber = '1';
    for(int i = 0; i< numRows; i++){
        for(int j = 0; j<numCols; j++){
            if(i == 0){
                board[i][j] = rowNumber++;
            }
            else{
                board[i][j] = '-';
            }
            boardHeight[j] = 0;
        }
    }
}

bool checkLegalDrop(int col){
    int height = boardHeight[col-1]; // if height exceeds amount of rows also return false
    if(height > numRows - 2  ){
        return false;
    }
    return true;
}

bool checkWin(int row, int col){ // function to check if player has won

    return false;
}

bool dropDisc(int col){ // boolean to check if the drop wins

    int height = boardHeight[col-1]; // since arrays start at 0 and we start at column 1, we must subtract 1
    boardHeight[col-1]++;
    board[numRows-(height+1)][col-1] = 'O';

    return checkWin(numRows-(height+1), col-1);
}



void printBoard(){
    cout << "\nCurrent board: " << endl;
    for(int i = 0; i< numRows; i++){
            cout<<endl;
            for(int j = 0; j<numCols; j++){
                cout << ' ' << board[i][j];
            }
    }
}
int main()
{
   printInstructions();
   initializeBoard();
   printBoard();

  bool win = false;
  while(!win){
   cout << "\nSelect a column to drop disc in" << endl;
   char col;
   cin >> col;
   if(col >= '1' && col <='8'){
      int column = col - '0';
      if(checkLegalDrop(column)){
        win = dropDisc(column);
        printBoard();
       }
      else{
        cout << "Can't drop disc since column is full" << endl;
      }
   }
   else{
        cout << "Incorrect column input, select a column between 1 and 8" << endl;
   }
  }
  if(win){
    cout << "Congratulations you win!" << endl;
  }
   return 0;
}
