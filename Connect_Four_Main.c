#include "stdio.h"

#define N 4

// Type definitions
typedef signed char Byte;
typedef signed char Bool;
typedef unsigned char uByte;

// Header files
#include "Board_Functions.h"

// Source files
#include "Board_Functions.c"

int main() {
  // Set up local variables
  char Board[N*N];                  // Stores the connect four board
  uByte Stack_Height[N];            // Used to store number of pieces in each column.
  Bool No_Winner = 1;               // False if there is a winner
  Byte Player = 0;                  // Keeps track of which player is playing
  char Player_Input;                // Player input

  // Initialize Board
  Initialize_Board(Board, Stack_Height);

  // Dispaly Initial board
  Display_Board(Board);

  // Loop until there is a winner
  do { // while(!Is_Winner)
    // Update whose turn it is
    Player = (Player+1)%2;

    // Prompt player
    if(Player == 1)
      printf("Player X's turn. ");
    else
      printf("Player O's turn. ");

    // Get player's response
    Player_Input = Get_Response(Stack_Height);

    // Check for quit
    if(Player_Input == 'q' || Player_Input == 'Q')
      return 0;

    // Update Board
    Update_Board(Board, Player, (Stack_Height[Player_Input]-1), (uByte)Player_Input);

    // Display Board
    Display_Board(Board);

    // Check for a Winner
    No_Winner = !Check_For_Winner(Board);

    // Check if board is full.
    if(Full_Board(Stack_Height)) {
      printf("Board is full. No one won. So sad \n");
      break;
    }
  } while(No_Winner);

  return 0;
} // int main()
