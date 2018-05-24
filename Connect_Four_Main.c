#include "stdio.h"

#define N 4

typedef signed char Byte;
typedef signed char Bool;
typedef unsigned char uByte;

void Initialize_Board(char* Board, uByte* Stack_Height);
char Get_Response(uByte* Stack_Height);
void Update_Board(char* Board,  Byte Player, uByte Row, uByte Col);
void Display_Board(char* Board);
Bool Check_For_Winner(char* Board);
Bool Full_Board(uByte* Stack_Height);

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

void Initialize_Board(char* Board, uByte* Stack_Height) {
  // This function is used to initialize the board to a set of empty spaces

  int i,j;                          // Counter variables
  for(i = 0; i < N; i++) {
    Stack_Height[i] = 0;          // Each column starts with 0 pieces

    for(j = 0; j < N; j++) {
      Board[i*N+j] = ' ';
    } // for(j = 0; j < N; j++) {
  } // for(i = 0; i < N; i++) {
} // void Initialize_Board(uByte* Board, uByte* Stack_Height) {

char Get_Response(uByte* Stack_Height) {
  // This function is used to get a response from the player

  char Player_Input;                // Stores Input
  Bool Valid_Input = 0;             // True only if Input is an integer from 1 to N
  Byte i;                           // Counter Variable

  do { // while(!Valid_Input)
    // Prompt
    printf("Enter a column number (0,1...%d). 'q' to quit: ",(N-1));

    // Get Input
    scanf("%c",&Player_Input);

    // Check if player wants to quit
    if(Player_Input == 'q' || Player_Input == 'Q')
      return Player_Input;

    // If not, we then we expec the input to be an integer. However, we
    // read in the input as a chacter. Thus, if the player entered a '0'
    // then Player_Input will read 48. We need to subtract 48 from the
    // Player_Input.
    Player_Input -= 48;

    // Check for valid Input
    for(i = 0; i < N; i++) {
        if(Player_Input == i) {
        Valid_Input = 1;     // Input is vaid!
        Stack_Height[i]++;   // Add a piece to the selected column
        break;
      } // if(Player_Input == i) {
    } // for(int i = 1; i <= N; i++) {

    // Make sure that selected column is not full
    if(Valid_Input && Stack_Height[Player_Input] > N) {
      printf("Column %d is Full. ",Player_Input);
      Stack_Height[Player_Input]--;
      Valid_Input = 0;
    } // if(Valid_Input && Stack_Height[Player_Input] >= N) {
    else if(!Valid_Input) {
      printf("Invalid input! ");
    }

    // clear input buffer
    while(getchar() != '\n');
  } while(!Valid_Input);

  return Player_Input;
} // char Get_Response(uByte* Stack_Height) {

void Update_Board(char* Board, Byte Player, uByte Row, uByte Col) {
  char Symbol;
  if(Player == 1)
    Symbol = 'X';
  else
    Symbol = 'O';

  Board[Row*N + Col] = Symbol;
} // void Update_Board(char* Board, Byte Player, char Row, char Col) {

void Display_Board(char* Board) {
  // This function is used to display the board after each turn in the game

  int i,j;                          // Counter variables
  for(i = N-1; i >= 0; i--) {
    printf("| ");
    for(j = 0; j < N; j++) {
      printf("%c ", Board[i*N+j]);
    } // for(j = 0; j < N; j++) {
    printf("|\n");
  } // for(i = 0; i < N; i++) {
} // void Display_Board(uByte Board) {

Bool Check_For_Winner(char * Board) {
  uByte i,j, row, col;     // Row and Col are aliases for i, j to make code more intuitive
  char Cell_Symbol;

  /* To check if there's a winner, we need to check if there are any lines
    of four X's or O's on the board. To do this, we cycle through each
    element of the board. For each cell, we check if that cell is part of a
    Vertical, Diagional (two possible), and Horizontal, line of four.
  */
  for(i = 0; i < N; i++) {
    for(j = 0; j < N; j++) {
      row = i;
      col = j;

      Cell_Symbol = Board[i*N+j];

      // Only check if current cell is not a spaces
      if(Cell_Symbol == ' ')
        continue;

      /*  Vertical Check:
        Here we check if the three cells above us have the same value as the
        current cell.

        A vertical line of four will always have a bottom-most element. This
        means that if there is a Vertical line of four then there must be some
        element on the board such that this element and the three elements above
        it all contain the same symbol.

        This means that we can not be in Rows 0, 1, or 2.
      */
      if(row > 2 &&
         Board[(i-1)*N+j] == Cell_Symbol &&
         Board[(i-2)*N+j] == Cell_Symbol &&
         Board[(i-3)*N+j] == Cell_Symbol){
           return 1;
      } // if(row > 2 &&

      /*  Upward-Diagional Check:
        Here we check if the three cells in the North-East diagional direction
        (above and to the right) have the same value as the current cell.

        A Uppward-Diagional line of four will always have some bottom left-most
        element. This means that if there is a Upward-Diagional line of four
        then there must be some element on the board such that this element and
        the three elements in the North-East direction to it all contain the
        same symbol.

        This means that we can not be in Rows N-1, N-2, or N-3, or in Coluns
        N-1, N-2, or N-3.
      */
      if(row < ((N-1)-2) && col < ((N-1)-2) &&
         Board[(i+1)*N+(j+1)] == Cell_Symbol &&
         Board[(i+2)*N+(j+2)] == Cell_Symbol &&
         Board[(i+3)*N+(j+3)] == Cell_Symbol){
           return 1;
      } // if(row < ((N-1)-2) && col < ((N-1)-2) &&


      /*  Horizontal Check:
        Here we check if the three cells in the East direction (to our right)
        have the same value as the current cell.

        A Horizontal line of four will always have some left-most element. This
        means that if there is a Horizontal line of four then there must be some
        element on bht board such that this element and the three elements to
        the right of it all contain the same symbol.

        This means that we can not be in Columns N-1, N-2, or N-3.
      */
      if(col < ((N-1)-2) &&
         Board[i*N+(j+1)] == Cell_Symbol &&
         Board[i*N+(j+2)] == Cell_Symbol &&
         Board[i*N+(j+3)] == Cell_Symbol){
           return 1;
      } // if(col < ((N-1)-2) &&

      /*  Downward-Diagional Check:
        Here we check if the three cells in the South-East diagional direction
        (below and to the right) have the same value as the current cell.

        A Downward-Diagional line of four will always have some upper left-most
        element. This means that if there is a diagional line of four then there
        must be some element on the board such that this element and the three
        elements in the South-East direction to it all contain the same symbol.

        This means that we can not be in Rows 0, 1, or 2. or Columns N-1, N-2,
        or N-3.
      */
      if(row > 2 && col < ((N-1)-2) &&
         Board[(i-1)*N+(j+1)] == Cell_Symbol &&
         Board[(i-2)*N+(j+2)] == Cell_Symbol &&
         Board[(i-3)*N+(j+3)] == Cell_Symbol){
           return 1;
      } // if(row > 2 && col < ((N-1)-2) &&

    } // for(col = 0; col < N; col++) {
  } // for(row = 0; row < N; row++) {

  return 0;
} // Bool Check_For_Winner(char * Board) {

Bool Full_Board(uByte* Stack_Height) {
  int i;
  Bool Is_Full = 1;

  for(i = 0; i < N; i++) {
    if(Stack_Height[i] != N) {
      Is_Full = 0;
      break;
    } // if(Stack_Height[i] != N) {
  } // for(i = 0; i < N; i++) {
  return Is_Full;
} // Bool Full)Board(uByte* Stack_Height) {
