#if !defined(_BOARD_FUNCTIONS_HEADER)
#define _BOARD_FUNCTIOS_HEADER

void Initialize_Board(char* Board, uByte* Stack_Height);
char Get_Response(uByte* Stack_Height);
void Update_Board(char* Board,  Byte Player, uByte Row, uByte Col);
void Display_Board(char* Board);
Bool Check_For_Winner(char* Board);
Bool Full_Board(uByte* Stack_Height);

#endif
