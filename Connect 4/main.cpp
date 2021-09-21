#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Board.h"

using namespace std;

void printInstructions(){
    cout << "You will play Connect 4 against a simple AI on a 6x8 board" << endl;

}
bool aiDropDisc(Board* b){
    int randomCol = rand()%8 + 1;         // random column from 1 to 8
    while(!b->checkLegalDrop(randomCol)){ // make sure random column is valid
        int randomCol = rand()%8 + 1;
    }
    return b->dropDisc(randomCol, 'X');
}
int main()
{
   srand(time(NULL)); // random seeds for number generation
   Board* bptr = new Board();
   printInstructions();
   bptr->initializeBoard();
   bptr->printBoard();

  bool AIWin = false;
  bool win = false;
  while(!win && !AIWin){
   cout << "\nSelect a column to drop disc in" << endl;
   char col;
   cin >> col;
   if(col >= '1' && col <='8'){
      int column = col - '0';
      if(bptr->checkLegalDrop(column)){
        win = bptr->dropDisc(column, 'O');
        if(win){   // AI doesn't drop if you win
            bptr->printBoard();
            break;
        }
        AIWin = aiDropDisc(bptr);
        bptr->printBoard();
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
