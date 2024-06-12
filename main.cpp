#include <iostream>
#include <vector>

using namespace std;

// Hoeveelheid rijen en kolommen
const int ROWS = 6;
const int COLS = 7;

void displayBoard(vector<char> board) {
    // Print de kolom nummers
    for (int i = 0; i < COLS; ++i) {
        cout << " " << i + 1 << " ";
    }
    cout << endl;

    // Print het speelbord
    for (int i = ROWS - 1; i >= 0; --i) {
        for (int j = 0; j < COLS; ++j) {
            cout << "|" << board[i * COLS + j] << " ";
        }
        cout << "|" << endl;
    }

    // Print de onderste lijn
    for (int i = 0; i < COLS + 2; ++i) {
        cout << "---";
    }
    cout << endl;
}

bool isColumnFull(vector<char> board, int col) {
    return board[col] != '.';
}

int dropToken(vector<char>& board, int col, char player) {
    for (int i = ROWS - 1; i >= 0; --i) {
        int index = i * COLS + col;
        if (board[index] == '.') {
            board[index] = player;
            return i; // Retourneer de rij waar de token geplaatst is
        }
    }
    // Kolom is vol
    return -1;
}

bool checkWinner(vector<char> board, char player) {
    // Controleer horizontale winsten
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            int index = i * COLS + j;
            if (board[index] == player && board[index + 1] == player && board[index + 2] == player && board[index + 3] == player) {
                return true;
            }
        }
    }

    // Controleer verticale winsten
    for (int i = 0; i < ROWS - 3; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int index = i * COLS + j;
            if (board[index] == player && board[index + COLS] == player && board[index + 2 * COLS] == player && board[index + 3 * COLS] == player) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    string player1Name, player2Name, player1Color, player2Color;
    char playerTurn = 'X'; // Start met Speler 1 (X)

    cout << "Voer naam Speler 1 in: ";
    getline(cin, player1Name);
    cout << "Voer kleur Speler 1 in: ";
    getline(cin, player1Color);
    cout << "Voer naam Speler 2 in: ";
    getline(cin, player2Name);
    cout << "Voer kleur Speler 2 in: ";
    getline(cin, player2Color);

    vector<char> board(ROWS * COLS, '.'); // Initialiseer het bord met lege plaatsen ('.')

    while (true) {
        displayBoard(board);

        int col;
        cout << (playerTurn == 'X' ? player1Name : player2Name) << "'s beurt (" << playerTurn << "), kies een kolom (1-" << COLS << "): ";
        cin >> col;
        col--; // Pas aan voor 0-gebaseerde indexering

        if (col < 0 || col >= COLS || isColumnFull(board, col)) {
            cout << "Ongeldige kolom. Probeer opnieuw." << endl;
            continue;
        }

        int row = dropToken(board, col, playerTurn);

        if (checkWinner(board, playerTurn)) {
            displayBoard(board);
            cout << (playerTurn == 'X' ? player1Name : player2Name) << " wint!" << endl;
            break;
        }

        playerTurn = (playerTurn == 'X') ? 'O' : 'X'; // Wissel beurten
    }

    return 0;
}

