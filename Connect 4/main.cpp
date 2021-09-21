#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
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
    if(height > numRows-2){
        return false;
    }
    return true;
}

bool checkWin(int row, int col, char c){    // function to check if player has won
    int connectedDiscs = 0;
    for(int i = row; i >= 0; i-- ){ // check how many connected discs on top
        if(board[i][col] == c){
            connectedDiscs++;
            if(connectedDiscs >= 4){ // if 4 discs are connected vertically then player won
                return true;
            }
        }
        else{
            break;
        }
    }
    for(int i = row + 1; i < numRows; i++  ){ // check how many connected discs on bottom
        if(board[i][col] == c){
            connectedDiscs++;
             if(connectedDiscs >= 4){
                return true;
             }
        }
        else{
            break;
        }
    }
    connectedDiscs = 0;             // reset to see if right to left has 4 in a row
    for(int i = col; i >= 0; i-- ){ // check how many connected discs on left
        if(board[row][i] == c){
            connectedDiscs++;
            if(connectedDiscs >= 4){ // if 4 discs are connected horizontally then player won
                return true;
            }
        }
        else{
            break;
        }
    }
    for(int i = col + 1; i < numCols; i++  ){ // check how many connected discs on right
        if(board[row][i] == c){
            connectedDiscs++;
             if(connectedDiscs >= 4){
                return true;
             }
        }
        else{
            break;
        }
    }

    connectedDiscs = 0;
    int i = row;                // i represents row, j col
    int j = col;
    while(i >= 0 && j >=0  )    // check how many connected discs are in the top down diagonal (above and left to current disc)
    {
        if(board[i][j] == c){
            connectedDiscs++;
            if(connectedDiscs >= 4){
                return true;
            }
            i--;
            j--;
        }
        else{
            break;
        }
    }

     connectedDiscs--;    // remove double count most recently dropped disc
     i = row;
     j = col;
     while(i < numRows && j < numCols  )    // check how many connected discs are in the top down diagonal (below and right to current disc)
        {
        if(board[i][j] == c){
            connectedDiscs++;
              if(connectedDiscs >= 4){
                return true;
            }
            i++;
            j++;
        }
        else{
            break;
        }
    }

    connectedDiscs = 0;
     i = row;
     j = col;
    while(i < numRows && j >=0  )    // check how many connected discs are in the bottom up diagonal (below and left to current disc)
    {
        if(board[i][j] == c){
            connectedDiscs++;
             if(connectedDiscs >= 4){
                return true;
            }
            i++;
            j--;
        }
        else{
            break;
        }
    }

     connectedDiscs--;
     i = row;
     j = col;
    while(i >= 0 && j < numCols )    // check how many connected discs are in the bottom up diagonal (above and right to current disc)
    {
        if(board[i][j] == c){
            connectedDiscs++;
            if(connectedDiscs >= 4){
                return true;
            }
            i--;
            j++;
        }
        else{
            break;
        }
    }
    return false;
}

bool dropDisc(int col, char c){ // boolean to check if the drop wins

    int height = boardHeight[col-1]; // since arrays start at 0 and we start at column 1, we must subtract 1
    boardHeight[col-1]++;
    board[numRows-(height+1)][col-1] = c;

    return checkWin(numRows-(height+1), col-1, c);
}

bool aiDropDisc(){
    int randomCol = rand()%8 + 1; // random column from 0 to 7
    while(!checkLegalDrop(randomCol)){ // make sure random column is valid
        int randomCol = rand()%8 + 1;
    }
    return dropDisc(randomCol, 'X');
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
   srand(time(NULL)); // random seeds for number generation
   printInstructions();
   initializeBoard();
   printBoard();

  bool AIWin = false;
  bool win = false;
  while(!win && !AIWin){
   cout << "\nSelect a column to drop disc in" << endl;
   char col;
   cin >> col;
   if(col >= '1' && col <='8'){
      int column = col - '0';
      if(checkLegalDrop(column)){
        win = dropDisc(column, 'O');
        if(win){   // AI doesn't drop if you win
            printBoard();
            break;
        }
        AIWin = aiDropDisc();
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
    cout << "\nCongratulations you win!" << endl;
  }
  else{
    cout << "\nThe AI has beaten you..." << endl;
  }
   return 0;
}
