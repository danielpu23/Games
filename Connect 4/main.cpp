#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
const int numRows = 6;
const int numCols = 8;
char board [numRows][numCols];

void printInstructions(){
    cout << "You will play Connect 4 against a simple AI" << endl;

}

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
        }
    }
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
   return 0;
}
