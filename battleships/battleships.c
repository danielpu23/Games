#include <stdio.h>
#include <stdlib.h>

const int boardRows = 9;          // board is 9x9 size, with one row dedicated to displaying the column numbers and one column dedicated to displaying the row numbers
const int boardColumns = 9;
const int firstValidIndex = 1;    // represents the first index in the board that the AI, user, and board generation can manipulate (applies to both row and column)
const int lastValidIndex = 8;     // represents the last index in the board that the AI, user, and board generation can manipulate (essentially indexes in the array where 1<=row<=8 and 1<=col<=8
const int numShips = 7;           // each player has 7 ships with 14 total coordinates that they need to hit
void titlescreen(){
  	printf("Game rules: \n");
 	printf("You will play Battleships against the AI, and both of your boards are randomly generated \n");
	printf("Both of you will guess a location on the board to strike, and if you hit a battleship,\n");
	printf("it will be hit and an 'x' will be placed at that coordinate. If not, an 'o' will be placed\n");
	printf("There are 7 battleships of size 2. Destroying both parts of a ship will display \"Ship sank\"\n");
	printf("Enter coordinates without spaces, with the column letter in capital letters followed by row number, such as C1\n");
	printf("Whoever destroys all 7 of the opponent's battleships first wins. \nTies can happen if both you and the AI sink all ships on the same turn");
}
void initializeBoard(char board [boardRows][boardColumns]){
	char columnLetter = 'A';
	char rowNumber = '0';
	 for(int i = 0; i<boardRows; i++){
            for(int j = 0; j<boardColumns; j++){            // first column contains letters A to H
                if(i == 0 && j!=0){
                    board[i][j] = columnLetter+j-1;
                }
                else if(j == 0 && i !=0){                   // first row contains numbers 1 to 8
                    board[i][j] = rowNumber+i;
                }
                else if(j == 0 && i==0){                    // (0,0) contains an empty space
                    board[i][j] = ' ';
                }
                else{                                       // every other coordinate is set to '-' by default
                    board[i][j] = '-';
                }
            }
    }
}

void printBoard(char board[boardRows][boardColumns]){       // print the entire board
    for(int i = 0; i<boardRows; i++){
            printf("\n");
            for(int j = 0; j<boardColumns; j++){
                printf("%c ", board[i][j]);
            }
    }
}
void generateBattleships(int shipCoordinates[]){          // The ships coordinates are blocked into groups, with the first ship of size 2 being grouped together at indexes
                                                          // [0,1,2,3], the second at [4,5,6,7], and so on until we reach the last ship (who's coordinates are [24,25,26,27])
    for(int i = 0; i<numShips*4; i+=4){         //we want to have an array of size numShips*2*2 since each ship takes two coordinates and a coordinate contains 2 elements: row and col
        int randomNum = (rand()%lastValidIndex)+firstValidIndex;           //generate 2 random numbers from 1 to 8
        int random = (rand()%lastValidIndex)+firstValidIndex;
        int randomNum2;                         //these random numbers will be paired with the above random numbers later
        int random2;
        for(int j = 0; j<i; j+=2){
            while((shipCoordinates[j] == randomNum) && (shipCoordinates[j+1]==random)){        // Make sure the randomly generated set of random numbers isn't already one in the array
                randomNum = (rand()%lastValidIndex)+firstValidIndex;                           // Generate another set until we produce one that's unique
                random = (rand()%lastValidIndex)+firstValidIndex;
            }
        }
        _Bool acceptableLocation = 0;      //by default this is false, and is used to track if we successfully generated a unique pair of coordinates
        int timesTraversed = 0;            //make sure we don't infinite loop, if we keep getting not acceptable locations, it's likely that there isn't one
        while(acceptableLocation==0){
        int randomDirection = rand()%4;    //generate random number between 0 and 3 that determines direction of paired coordinate spawn
        if(randomDirection == 0){          //try to spawn a ship coordinate directly west
                randomNum2 = randomNum-1;
                random2 = random;
                timesTraversed++;
        }
        else if(randomDirection == 1){ //try to spawn a ship coordinate directly east
                randomNum2 = randomNum+1;
                random2 = random;
                timesTraversed++;
        }
        else if (randomDirection == 2){ //try to spawn a ship coordinate directly north
             randomNum2 = randomNum;
                random2 = random-1;
                timesTraversed++;
        }
        else if (randomDirection == 3){ //try to spawn a ship coordinate directly south
            randomNum2 = randomNum;
                random2 = random+1;
                timesTraversed++;
        }
        if(randomNum2 <= lastValidIndex && randomNum2 >= firstValidIndex && random2 <= lastValidIndex && random2 >= firstValidIndex){ //make sure numbers generated are in valid range
            acceptableLocation = 1;    //set acceptableLocation to true before we check if it's already a generated coordinate
                    for(int k = 0; k<i; k+=2){
                        if((shipCoordinates[k] == randomNum2) && (shipCoordinates[k+1]==random2)){ //if the coordinates happen to be a coordinate pair that's already been generated, make acceptableLocation false
                            acceptableLocation = 0;
                        }
                    }
                }
        if(timesTraversed >=8){         // if we run the above blocks 8 or more times, it's likely an infinite loop and we should select another random coordinate
                break;
            }
        }

        if(timesTraversed < 8 && acceptableLocation == 1){
         shipCoordinates[i] = randomNum;  // Set first row of generated ship to first random number
         shipCoordinates[i+1] = random;   // Set first column of generated ship to second random number
         shipCoordinates[i+2] = randomNum2; // Set second row of generated ship to third random number
         shipCoordinates[i+3] = random2;    // Set second column of generated ship to fourth random number
            }
        else{           //restart loop at same index to generate a new coordinate
          i-=4;
        }
    }
}

_Bool isHit(char c){
    if(c =='x'||c =='o'){                   // if character is 'x' or 'o' it has already been targeted
        return 1;
    }
    return 0;
}
void hitCoordinate(int row, int col, char board [boardRows][boardColumns], int* numOfShips, int aiShipCoordinates [], int size){
        _Bool hitShip = 0;               // keeps track of if a ship was hit or not
        for(int i = 0; i<size; i+=2){
            if(aiShipCoordinates[i] == row && aiShipCoordinates[i+1] == col){         // checks if user hit a ship's coordinate, and if so, decrease shipNum by 1 and set hitShip to true
            board[row][col] = 'x';
            hitShip = 1;
            char column = 'A'+col-1;
            printf("\nYou attacked and hit a ship at %c%d", column, row);
            int startIndex = (i/4)*4;   //Get the starting index of the group of coordinates and check if its entire group has been hit. We divide by 4 to get the block number that the coordinate is in
                                        //and then multiply by 4 to get to the correct starting index of the block. For example, if we found that we hit a ship in index 7 of the coordinate array,
                                        //we divide by 4 to get its block (1), then multiply by 4 to get its starting index (4). In the following if statement we check if the coordinates at 4, 5, 6, and 7 are
                                        //hit to determine if the entire ship is hit.
                if((board[aiShipCoordinates[startIndex]][aiShipCoordinates[startIndex+1]]=='x')&&(board[aiShipCoordinates[startIndex+2]][aiShipCoordinates[startIndex+3]]=='x')){
                    printf("\nYou sank a ship");
                    (*numOfShips)--;                                    //decrement numShips
                }
            break;
        }

   }
        if(hitShip == 0){                       // if user did not hit a ship's coordinate, then they missed
            board[row][col] = 'o';
            char column = 'A'+col-1;
            printf("\nYou attacked and missed at %c%d", column, row);
        }
}

void aiHitCoordinate(char board[boardRows][boardColumns], int* numOfShips, int playerShipCoordinates[], int size){
      int row = (rand()%lastValidIndex)+firstValidIndex;        // generate a number between 1 and 8 as the coordinate for the AI to hit
      int col = (rand()%lastValidIndex)+firstValidIndex;
      while(isHit(board[row][col])==1){                         // generate a new number if those coordinates have already been hit
           row = (rand()%lastValidIndex)+firstValidIndex;
           col = (rand()%lastValidIndex)+firstValidIndex;
      }
      _Bool hitShip = 0;
        for(int i = 0; i<size; i+=2){
            if(playerShipCoordinates[i] == row && playerShipCoordinates[i+1] == col){         // checks if AI hit a ship's coordinate, and if so, decrease shipNum by 1
            board[row][col] = 'x';
            char column = 'A'+col-1;
            printf("\nAI attacked and hit a ship at coordinate %c%d", column ,row);
            hitShip = 1;
            int startIndex = (i/4)*4;   //Get the starting index of the group of coordinates and check if its entire group has been hit. Same procedure as when the player hit a ship's coordinate
            if((board[playerShipCoordinates[startIndex]][playerShipCoordinates[startIndex+1]]=='x')&&(board[playerShipCoordinates[startIndex+2]][playerShipCoordinates[startIndex+3]]=='x')){
                    printf("\nAI sank a ship");
                    (*numOfShips)--;                                    //decrement numShips
            }
            break;
            }
         }
         if(hitShip == 0){                       // if AI did not hit a ship's coordinate, then they missed
         board[row][col] = 'o';
         char column = 'A'+col-1;
         printf("\nAI attacked and missed at coordinate %c%d", column ,row);
         }
}

int main(){
 srand(time(NULL));                             // Need to seed the random generator to make sure rand() works properly
 titlescreen();
 char playerBoard[boardRows][boardColumns];     // Represents board of the player
 char aiBoard[boardRows][boardColumns];         // Represents board of the AI
 initializeBoard(aiBoard);                      // Initialize both boards and print them
 printf("\n\nAI Board \n");
 printBoard(aiBoard);
 initializeBoard(playerBoard);
 printf("\n\nYour Board \n");
 printBoard(playerBoard);
 int playerShipCoordinates[numShips*4];         // Stores the coordinates of the ships on the player's board
 generateBattleships(playerShipCoordinates);
 int aiShipCoordinates[numShips*4];             // Stores the coordinates of the ships on the AI's board
 generateBattleships(aiShipCoordinates);
 int numPlayerShips = numShips;
 int numAIShips = numShips;
 char column;
 int row;
 while(numPlayerShips>0 && numAIShips>0 ){             //While the user or AI hasn't won, keep playing
    printf("\n\nPlease enter a valid coordinate: ");
    scanf(" %c", &column);
    scanf("%d", &row);
    int columnCoordinate = column-'A'+1;               // Convert from character to respective column value
    while(row < firstValidIndex || row > lastValidIndex || columnCoordinate < firstValidIndex || columnCoordinate > lastValidIndex || isHit(aiBoard[row][columnCoordinate])==1){  // while loop that makes sure that the user inputs correctly
        if(row < firstValidIndex || row > lastValidIndex || columnCoordinate < firstValidIndex || columnCoordinate > lastValidIndex){   // if the user inputs an invalid set of coordinates, keep asking them until they input a valid set
            printf("\nCoordinate is not valid. Please enter a valid coordinate: ");
            scanf(" %c", &column);
            scanf("%d", &row);
            columnCoordinate = column-'A'+1;
        }
        else if(isHit(aiBoard[row][columnCoordinate])==1){    //check if user aleady hit the specified coordinate, makes user enter another coordinate until they hit one that's not been hit already
                printf("\nCoordinate has already been hit. Enter another coordinate: ");
                scanf(" %c", &column);
                scanf("%d", &row);
                columnCoordinate = column-'A'+1;
        }
    }
        int size = sizeof(aiShipCoordinates)/sizeof(aiShipCoordinates[0]);
        hitCoordinate(row, columnCoordinate, aiBoard, &numAIShips, aiShipCoordinates, size); // player hits the corresponding coordinate
        aiHitCoordinate(playerBoard, &numPlayerShips, playerShipCoordinates, size);          // AI hits a random coordinate
        printf("\n\nAI Board \n");                                                        // print the board states
        printBoard(aiBoard);
        printf("\n\nYour Board \n");
        printBoard(playerBoard);
        if(numAIShips == 1){                                                           // print number of ships left on each board
        printf("\nThere is %d ship left on the AI's board", numAIShips);
        }
        else{
            printf("\nThere are %d ships left on the AI's board", numAIShips);
        }
        if(numPlayerShips == 1){
        printf("\nThere is %d ship left on your board", numPlayerShips);
        }
        else{
        printf("\nThere are %d ships left on your board", numPlayerShips);
        }
    }

    if(numPlayerShips==0&&numAIShips==0){                         // If both you and the AI have no ships left, you tie
        printf("\nThere is a tie");
    }
    else if(numAIShips==0)   {                                    // If only the AI has no ships left, you win
    printf("\nYou win");
    }
    else{                                                     // Otherwise, you lose
    printf("\nYou lose");
    }
}
