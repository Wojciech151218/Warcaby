
#include "GameFileHandler.h"
void initializeGameFileHandler(GameFileHandler * gameFileHandler, Board * board, PieceColour turn){
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
    gameFileHandler->currentGameFile = "currentGame.txt";
    gameFileHandler->gameDirectory = directoryName;
    gameFileHandler->board =board;


}

bool isGameDirectoryEmpty(GameFileHandler *gameFileHandler) {
    // Open the directory
    DIR *dir = opendir(gameFileHandler->gameDirectory);
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
void saveGame(GameFileHandler *gameFileHandler, PieceColour turn) {
    // Create the file path
    char filePath[100]; // Adjust the size as needed
    sprintf(filePath, "%s/%s", gameFileHandler->gameDirectory,gameFileHandler->currentGameFile);

    // Open the file for writing
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file,  turn==White ? "W\n":"B\n");
    printBoardToFile(*gameFileHandler->board, file);
    fclose(file);
}
void resetBoardFile(GameFileHandler* gameFileHandler) {
    // Create the file path
    char filePath[100]; // Adjust the size as needed
    sprintf(filePath, "%s/%s", gameFileHandler->gameDirectory,gameFileHandler->currentGameFile);

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
void readBoardFromFile(GameFileHandler *gameFileHandler, Board *board) {
    FILE * file = fopen(sum_strings(sum_strings(gameFileHandler->gameDirectory,"/"),gameFileHandler->currentGameFile),"r");
    *board = constructBoardFromFile(file);
    fclose(file);
}
PieceColour  readTurnFromTheFile(GameFileHandler gameFileHandler){
    char turnSignature;
    FILE * file = fopen(sum_strings(sum_strings(gameFileHandler.gameDirectory,"/"),gameFileHandler.currentGameFile),"r");
    turnSignature = fgetc(file);
    fclose(file);
    return turnSignature == 'W'? White : Black;
}