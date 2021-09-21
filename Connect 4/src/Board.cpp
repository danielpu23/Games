
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Board.h"
using namespace std;

Board::Board(){
    initializeBoard();
}

void Board :: initializeBoard(){
    char rowNumber = '1';
    for(int i = 0; i < NUMROWS; i++){
        for(int j = 0; j < NUMCOLS; j++){
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

bool Board :: checkLegalDrop(int col){
    int height = boardHeight[col-1]; // if height exceeds amount of rows also return false
    if(height > NUMROWS-2){
        return false;
    }
    return true;
}

bool Board :: checkWin(int row, int col, char c){    // function to check if player has won
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
    for(int i = row + 1; i < NUMROWS; i++  ){ // check how many connected discs on bottom
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
    for(int i = col + 1; i < NUMCOLS; i++  ){ // check how many connected discs on right
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
     while(i < NUMROWS && j < NUMCOLS  )    // check how many connected discs are in the top down diagonal (below and right to current disc)
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
    while(i < NUMROWS && j >=0  )    // check how many connected discs are in the bottom up diagonal (below and left to current disc)
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
    while(i >= 0 && j < NUMCOLS )    // check how many connected discs are in the bottom up diagonal (above and right to current disc)
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
bool Board :: dropDisc(int col, char c){ // boolean to check if the drop wins

    int height = boardHeight[col-1]; // since arrays start at 0 and we start at column 1, we must subtract 1
    boardHeight[col-1]++;
    board[NUMROWS-(height+1)][col-1] = c;

    return checkWin(NUMROWS-(height+1), col-1, c);
}

void Board :: printBoard(){   // display the board
    cout << "\nCurrent board: " << endl;
    for(int i = 0; i< NUMROWS; i++){
            cout<<endl;
            for(int j = 0; j<NUMCOLS; j++){
                cout << ' ' << char(board[i][j]);
        }
    }
}
