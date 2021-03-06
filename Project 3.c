//============================================================================= 
// PROGRAMMER:    Eren Ozbay      
// PANTHER ID:    2452687
// CLASS:         COP4338, Online Section  
// SEMESTER:      Summer 2021 
// Project:       Assignment 3
// DUE:           06/17/2021
//=============================================================================

#include<stdio.h>
#include<math.h>
#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1
#define EMPTY 0
#define ROOK 4
#define KNIGHT 2
#define BISHOP 3
#define KING 6
#define QUEEN 5
#define PAWN 1

static int board[8][8] = { {-4, -2, -3, -5, -6, -3, -2, -4},
                            {-1, -1, -1, -1, -1, -1, -1, -1},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {1, 1, 1, 1, 1, 1, 1, 1},
                            {4, 2, 3, 5, 6, 3, 2, 4} };
static int isLegalMove(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    int piece = board[srcI][srcJ];//moved piece...
    int pieceType = abs(piece);
    switch (pieceType) {
    case ROOK:
        if (((abs(srcI - trgI)) > 0) && (abs(srcJ - trgJ)) > 0) { //means the rook moved horizontal and vertical
            return 0;
        }
        else if (((abs(srcI - trgI)) > 0) ) { //move vertical
            if (srcI < trgI) { //move down
                for (i = 1; i < trgI - srcI; i++)
                    if (board[srcI + i][srcJ] != EMPTY)
                        return 0;
            }
            else {
                for (i = 1; i < srcI - trgI; i++) //move up
                    if (board[srcI - i][srcJ] != EMPTY)
                        return 0;
            }
        }
        else if (((abs(srcJ - trgJ)) > 0)) { //move horizontal
            if (srcJ < trgJ) { //moves right
                for (i = 1; i < trgJ - srcJ; i++)
                    if (board[srcI][srcJ+i] != EMPTY)
                        return 0;
            }
            else {
                for (i = 1; i < srcJ - trgJ; i++) //move left
                    if (board[srcI][srcJ-i] != EMPTY)
                        return 0;
            }
        }
        else
            for (;;);
        break;

    case PAWN:
        if (piece > 0 && (srcI < trgI))//white piece cannot move back
            return 0;
        if (piece < 0 && (srcI > trgI))//black piece cannot move back
            return 0;
        if ((abs(srcJ - trgJ)) > 0)    // pawn cannot move left or right
        return 0;
        
       if ((piece < 0 && srcI == 1) || (piece > 0 && srcI == 6)) { //checks the correct pawn is not in starting row
           if ((abs(srcI - trgI) == 2) || (abs(srcI - trgI) == 1)) {
               if(piece > 0)    //white piece
                   for (i = 1; i < srcI - trgI; i++) { //move up
                       if (board[srcI - i][srcJ] != EMPTY)
                           return 0;
                   }
               if(piece < 0)    //black piece
                   for (i = 1; i < trgI - srcI; i++) //move up
                       if (board[srcI + i][srcJ] != EMPTY)
                           return 0;  
           }
           else 
               return 0;
        }
       else if (abs(srcI - trgI) != 1) { //only allows 1 move up
           return 0;
       }

        break;
    case KNIGHT://L shape
        return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
        break;
    case BISHOP:
        if (abs(srcI - trgI) != abs(srcJ - trgJ)) //means not a diagnol move
            return 0;
        if (srcI < trgI && srcJ < trgJ) {//case 1
            for (i = 1; i < trgI - srcI; i++)
                if (board[srcI + i][srcJ + i] != EMPTY)
                    return 0;
        }
        else if (srcI < trgI && srcJ > trgJ) {//case 2
            for (i = 1; i < trgI - srcI; i++)
                if (board[srcI + i][srcJ + i] != EMPTY)
                    return 0;
        }
        else if (srcI > trgI && srcJ < trgJ) { //case 3
            for (i = 1; i < srcI - trgI; i++)
                if (board[srcI + i][srcJ + i] != EMPTY)
                    return 0;
        }
        else if (srcI > trgI && srcJ > trgJ) { //case 4
            for (i = 1; i < srcI - trgI; i++)
                if (board[srcI + i][srcJ + i] != EMPTY)
                    return 0;
        }
        else 
            for (;;);

        break;
    case QUEEN: 
       //if it moves diagnolly, vertically or horizontally
        if ((abs(srcI - trgI) == abs(srcJ - trgJ)) || (((abs(srcI - trgI)) > 0) || (abs(srcJ - trgJ)) > 0)) {
            //if it is not diagnolly and moves both horizontal and vertical at the same time it is illegal
            if ((abs(srcI - trgI) != abs(srcJ - trgJ)) && (((abs(srcI - trgI)) > 0) && (abs(srcJ - trgJ)) > 0))
                return 0;
            else if (((abs(srcI - trgI)) > 0)) { //move vertical
                if (srcI < trgI) { //move down
                    for (i = 1; i < trgI - srcI; i++)
                        if (board[srcI + i][srcJ] != EMPTY)
                            return 0;
                }
                else {
                    for (i = 1; i < srcI - trgI; i++) //move up
                        if (board[srcI - i][srcJ] != EMPTY)
                            return 0;
                }
            }
            else if (((abs(srcJ - trgJ)) > 0)) { //move horizontal
                if (srcJ < trgJ) { //moves right
                    for (i = 1; i < trgJ - srcJ; i++)
                        if (board[srcI][srcJ + i] != EMPTY)
                            return 0;
                }
                else {
                    for (i = 1; i < srcJ - trgJ; i++) //move left
                        if (board[srcI][srcJ - i] != EMPTY)
                            return 0;
                }
            }
            else if (abs(srcI - trgI) != abs(srcJ - trgJ)) { //means not a diagnol move
                return 0;
            }
            else if (srcI < trgI && srcJ < trgJ) {//case 1
                for (i = 1; i < trgI - srcI; i++)
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
            }
            else if (srcI < trgI && srcJ > trgJ) {//case 2
                for (i = 1; i < trgI - srcI; i++)
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
            }
            else if (srcI > trgI && srcJ < trgJ) { //case 3
                for (i = 1; i < srcI - trgI; i++)
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
            }
            else if (srcI > trgI && srcJ > trgJ) { //case 4
                for (i = 1; i < srcI - trgI; i++)
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
            }
            else
                for (;;);
            break;
        }
    case KING:
        //makes the king allowed to move in any 1 direction
        if ((trgI == srcI + 1 && srcJ == trgJ) || (trgI == srcI - 1 && srcJ == trgJ)||
            (trgI == srcI && trgJ == srcJ + 1)|| (trgI == srcI && trgJ == srcJ - 1) ||
            (trgI == srcI + 1 && trgJ == srcJ + 1) || (trgI == srcI - 1 && trgJ == srcJ - 1)||
            (trgI == srcI + 1 && trgJ == srcJ - 1) || (trgI == srcI - 1 && trgJ == srcJ + 1)){
        break;
    }
        else {
            return 0;
        }
    return 1;//legal move
    }
}
static int isLegalCapture(int srcI, int srcJ, int trgI, int trgJ) {
    int piece = board[srcI][srcJ];//moved piece...
    int pieceType = abs(piece);

    return 1;//legal move
}
static int turn = WHITE;
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}
handleMove() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for mv command! It must be in the form of mv ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the rest of illegal command..
        return;
    }
    sourceFile = source[0];//source = "a5", sourceFile = 'a'
    targetFile = target[0];
    sourceRank = source[1] - '0';//source = "a5", sourceRank = 5
    targetRank = target[1] - '0';
    //board[sourceI][sourceJ]: source square...
    //board[targetI][targetJ]: target square...
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if (board[sourceI][sourceJ] * turn < 0) {
        printf("Turn violation, it's %s to move\n", turn == 1 ? "white" : "black");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
        printf("Invalid move: either source square is empty or target square is not empty\n");
        return;
    }
    if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess move\n");
        return;
    }
    //end of error checking....

    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = EMPTY;
    turn *= -1;//WHITE --> BLACK and BLACK --> WHITE
}
handleCapture() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for cp command! It must be in the form of cp ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }
    sourceFile = source[0];
    targetFile = target[0];
    sourceRank = source[1] - '0';
    targetRank = target[1] - '0';
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if (board[sourceI][sourceJ] * turn < 0) {
        printf("Turn violation, it's %s to move", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if (board[sourceI][sourceJ] * board[targetI][targetJ] > 0) {
        printf("Violation, %s cannot capture its own piece.", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] == EMPTY) {
        printf("Invalid capture: either source square is empty or target square is empty");
        return;
    }
    if (!isLegalCapture(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess capture");
        return;
    }
    //end of error checking....
    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = 0;
    turn *= -1;
}
handleShow() {
    int i, j;
    printf("board\t");
    for (i = 0; i < 8; i++)//file labels...
        printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
    for (i = 0; i < 8; i++)//table itself
        for (j = 0; j < 9; j++)
            printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ? '\n' : '\t');
}
main() {
    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    while (1) {//infinite while loop...
        printf("Please enter a new command...\n");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        if (strcmp(command, "quit") == 0)//if command === "quit"
            break;
        else if (!strcmp(command, "mv"))//if command == "mv"
        {
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else
                handleMove();
        }
        else if (!strcmp(command, "cp"))//if command == "cp"
        {
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else
                handleCapture();
        }
        else if (!strcmp(command, "show"))//if command == "show"
        {
            if (lastCharacter != '\n') {//show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the invalid show command...	
            }
            else
                handleShow();
        }
        else {
            printf("invalid command! Your command must start either with quit, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}