//
// Created by Wojciech on 14.05.2024.
//
#include "GameStateHandler.h"
void initializeGameStateHandler(GameStateHandler * gameStateHandler,Board * board,PieceColour turn){
    char * directoryName = "GameDirectory";
    if (access(directoryName, F_OK)) {
        if (mkdir(directoryName) == -1) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
        if (chmod(directoryName, 0777) == -1) {
            perror("Error setting permissions");
            exit(EXIT_FAILURE);
        }
    }
    gameStateHandler->currentGameFile = "currentGame.txt";
    gameStateHandler->gameDirectory = directoryName;
    gameStateHandler->board =board;


}
GameState getGameState(GameStateHandler* gameStateHandler){}
bool isGameDirectoryEmpty(GameStateHandler *gameStateHandler) {
    // Open the directory
    DIR *dir = opendir(gameStateHandler->gameDirectory);
    if (dir == NULL) {
        perror("Unable to open directory");
        return false; // Error occurred
    }

    // Read directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Exclude . and .. directories
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            return false; // Directory is not empty
        }
    }

    closedir(dir);

    return true; // Directory is empty
}
void saveGame(GameStateHandler *gameStateHandler, PieceColour turn) {
    // Create the file path
    char filePath[100]; // Adjust the size as needed
    sprintf(filePath, "%s/%s", gameStateHandler->gameDirectory,gameStateHandler->currentGameFile);

    // Open the file for writing
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file,  turn==White ? "W\n":"B\n");
    printBoardToFile(*gameStateHandler->board, file);
    fclose(file);
}
void resetBoardFile(GameStateHandler* gameStateHandler) {
    // Create the file path
    char filePath[100]; // Adjust the size as needed
    sprintf(filePath, "%s/%s", gameStateHandler->gameDirectory,gameStateHandler->currentGameFile);

    // Delete the file
    if (remove(filePath) != 0) {
        perror("Error deleting file");
    } else {
        printf("File deleted successfully\n");
    }
}
Board constructBoardFromFile(FILE *file) {
    Board board;
    char pieceSignature;

    char lineBuffer[1024];
    if (fgets(lineBuffer, sizeof(lineBuffer), file) == NULL) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }
    int row = 0;
    int col = 0;
    while ((pieceSignature = fgetc(file)) != EOF) {
        if (pieceSignature == '\n') {  // new line character
            col++;
            row = 0;
        } else {
            if(pieceSignature == ' '){
                board.pieces[row][col] = NULL;
                row++;
                continue;
            }
            Piece * piece = malloc(sizeof (Piece));
            initializePiece(piece,(pieceSignature == 'Q' || pieceSignature == 'O')? White : Black,(pieceSignature != 'O' && pieceSignature != 'o'));

            board.pieces[row][col] = piece;
            row++;
        }
    }
    return board;
}
void readBoardFromFile(GameStateHandler *gameStateHandler, Board *board) {
    FILE * file = fopen(sum_strings(sum_strings(gameStateHandler->gameDirectory,"/"),gameStateHandler->currentGameFile),"r");
    *board = constructBoardFromFile(file);
    fclose(file);
}
PieceColour  readTurnFromTheFile(GameStateHandler gameStateHandler){
    char turnSignature;
    FILE * file = fopen(sum_strings(sum_strings(gameStateHandler.gameDirectory,"/"),gameStateHandler.currentGameFile),"r");
    turnSignature = fgetc(file);
    fclose(file);
    return turnSignature == 'W'? White : Black;
}