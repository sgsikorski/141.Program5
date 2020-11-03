/* Program5.cpp
*  Scott Sikorski
*  Summer 2020 - Mobasheri
*  Battleship game program. Allows for the user to guess where the ships are.
*  Grants a win if all the ships are hit. Grants a loss if the user runs out of moves.
*  Terminal based system where it shows the user where the ships are located if they choose to do so.
*  This can only be done 3 times the entire time. Shows a view without them that also gives where the user
*  has guessed already.
*/

#include <iostream>  // In and out handling
#include <fstream>   // File handling
#include <string>    // String manipulation
#include <vector>    // Vector manipulation
#include <cctype>    // Character manipulation
#include <cstdlib>   // Grants random numbers

using namespace std;

// Displays directions
void displayDirections(){
    cout << "\n"
         << "Welcome to the game of Battleship. \n"
         << "                                                                 \n"
         << "You can choose to play this game or let the computer play.       \n"
         << "You will have a 10 x 10 board and up to 8 ships in any round.    \n"
         << "You can request to view the original board containing ship       \n"
         << "coordinates up to 3 times.                                       \n"
         << "                                                                 \n"
         << "Choose coordinates and attack the ships. You have 3 guesses for  \n"
         << "each ship. Successfully destroy all ships to win the game.       \n"
         << "                                                                 \n"
         << "                                                                 \n"
         << "For each attack provide two inputs:                              \n"
         << "   row (A-J), column (0-9)                                       \n" << endl;
}

// Board class - 6 private data members, 8 public data functions
class battleBoard{
    public:
        // Sets the userRows to their initial values
        void setRows(){
            userRows[0] = "    0 1 2 3 4 5 6 7 8 9   ";
            userRows[1] = "  |---------------------| ";
            userRows[2] = "A | o o o o o o o o o o |";
            userRows[3] = "B | o o o o o o o o o o |";
            userRows[4] = "C | o o o o o o o o o o |";
            userRows[5] = "D | o o o o o o o o o o |";
            userRows[6] = "E | o o o o o o o o o o |";
            userRows[7] = "F | o o o o o o o o o o |";
            userRows[8] = "G | o o o o o o o o o o |";
            userRows[9] = "H | o o o o o o o o o o |";
            userRows[10] = "I | o o o o o o o o o o |";
            userRows[11] = "J | o o o o o o o o o o |";
            userRows[12] = "  |---------------------| ";
        }

        // Prints the player view
        void printPlayer(){
            cout << "        Player view" << endl;
            //cout << userRows[0] << endl;
            for(int i = 0; i < 13; i++){
                cout << userRows[i] << endl;
            }
        }

        // Reads in the file and puts in a string vector to use
        void readFile(){
            cout << "Reading ships and coordinates\n"
                 << "you can't place more than 8 ships on a board\n"
                 << "Reading each ship coordinates:\n";
            // Throws an error if file isn't found.
            inStream.open("shipData.txt");
            if(!inStream.is_open()){
                cout << "Unable to find shipData.txt. Exiting program." << endl;
                exit(-1);
            }
            string nextAttack;
            char rowChoice;
            int colChoice;
            
            // Sets data field to empty and reads in strings from file
            for (int i = 0; i < 13; i++){
               originalRows[i] = userRows[i];
            }
            while(getline(inStream, nextAttack)){
               nextAttacks.push_back(nextAttack);
            }
            
            for (int i = 0; i < nextAttacks.size(); i++){
                // If it is a move then converts string to char and int for each position
                if(nextAttacks.at(i).find(" ") != string::npos){
                    rowChoice = (nextAttacks.at(i).substr(0, 1))[0];
                    colChoice = stoi(nextAttacks.at(i).substr(2, 1));
                    remainingShips = remainingShips + 1;
                    // Manipulates the data field strings to insert the ship at the data position
                    for (int i = 0; i < 13; i++){
                        if (rowChoice == userRows[i].at(0)){
                            originalRows[i].erase(colChoice * 2 + 4, 1);
                            originalRows[i].insert(colChoice * 2 + 4, "S", 1);
                        }
                    } 
                } 
            
            }
        }

        // Prints the data field for the original view
        void printOriginal(){
            cout << endl;
            cout << "        Original view" << endl;
            for (int i = 0; i < 13; i++){
                cout << originalRows[i] << endl;
            }
        }


        // Checks from originalRows then updates userRows
        void checkAttack(string userInput){
            // User and original data position, if ship was hit
            char userRowChoice;
            int userColChoice;
            char checkRowChoice;
            int checkColChoice;
            int hit = 0;
            int invalid = 0;
            
            // Checks if the user wants to exit the program or inputs an invalid move
            if(userInput.find(" ") != string::npos){
                userRowChoice = (userInput.substr(0, 1))[0];
                userColChoice = stoi(userInput.substr(2, 1));
            } 
            userInput[0] = toupper(userInput[0]);
            if(userInput[0] == 'X'){
               cout << "Exiting program..." << endl;
               exit(-1);
            }
            if (userInput[0] != 'A' && userInput[0] != 'B' && userInput[0] != 'C' && userInput[0] != 'D'
                && userInput[0] != 'E' && userInput[0] != 'F' && userInput[0] != 'G' && userInput[0] != 'H'
                && userInput[0] != 'I' && userInput[0] != 'J'){
                   cout << "Invalid coordinates. Please try again!" << endl;
                   getline(cin, userInput);
                   invalid = 1;
                   checkAttack(userInput);
                }
            else if(stoi(userInput.substr(2, 2)) > 10){
                   cout << "Invalid coordinates. Please try again!" << endl;
                   getline(cin, userInput);
                   invalid = 1;
                   checkAttack(userInput);
            } 
            
            // Gets the current data position and checks if the user inputted position matches
            // If it does, calls updateHit, if not no ship is hit then calls updateMiss
            for (int i = 0; i < nextAttacks.size(); i++){
                if(nextAttacks.at(i).find(" ") != string::npos){
                    checkRowChoice = (nextAttacks.at(i).substr(0, 1))[0];
                    checkColChoice = stoi(nextAttacks.at(i).substr(2, 1));
                } else{
                   continue;
                }
                if ((userRowChoice == checkRowChoice) && (userColChoice == checkColChoice)){
                    cout << "You have hit a ship!" << endl;
                    updateHit(userInput);
                    hit = 1;
                }
            }
            if (hit != 1 && invalid == 0){
               updateMiss(userInput);
            }
            

        }

        // Called to manipulate user and original view to include a hit
        void updateHit(string userInput){
            char rowUpdate;
            int colUpdate;

            rowUpdate = userInput.substr(0, 1)[0];
            colUpdate = stoi(userInput.substr(2, 1));
            // Manipulates the strings for a hit
            for (int i = 0; i < 13; i++){
                if (rowUpdate == userRows[i].at(0)){
                        userRows[i].erase(colUpdate * 2 + 4, 1);
                        userRows[i].insert(colUpdate * 2 + 4, "H", 1);
                        originalRows[i].erase(colUpdate * 2 + 4, 1);
                        originalRows[i].insert(colUpdate * 2 + 4, "H", 1);
                    }
            }
            // Decreases remainingShips and resets moveAmount
            remainingShips--;
            moveAmount = remainingShips * 3;

        }

        // Called to manipulate user and original view to include a miss
        void updateMiss(string userInput){
           cout << "You have missed!" << endl;
            char rowUpdate;
            int colUpdate;

            rowUpdate = userInput.substr(0, 1)[0];
            colUpdate = stoi(userInput.substr(2, 1));
            // Manipulates the strings for a miss
            for (int i = 0; i < 13; i++){
                if (rowUpdate == userRows[i].at(0)){
                        userRows[i].erase(colUpdate * 2 + 4, 1);
                        userRows[i].insert(colUpdate * 2 + 4, "M", 1);
                        originalRows[i].erase(colUpdate * 2 + 4, 1);
                        originalRows[i].insert(colUpdate * 2 + 4, "M", 1);
                    }
            }
            // Decrements current moveAmount
            moveAmount--;
            
        }
        
        // Checks if moveAmount is zero if so the user loses
        void checkLose(){
            if (moveAmount == 0){
                cout << "Sorry! You ran out of turns.\n"
                     << "Thanks for playing.  Exiting... \n";
                exit(-1);
            }
        }
        
        // Checks if there are still remainingships to be hit, if there are then the user hasn't won yet
        int checkWin(){
            if (remainingShips > 0){
                return 1;
            } else{
                return 0;
            }
        }
        
    // Private declaration of data members
    private:
        string userRows[13];
        string originalRows[13];
        ifstream inStream;
        vector<string> nextAttacks;
        int moveAmount = -1;
        int remainingShips = 0;

}; 


int main(){
    // Directions, sets player rows, and reads file
    displayDirections();
    battleBoard board;
    board.setRows();
    board.readFile();
    // Variable declaration for menu options and userInput 
    char wantToPlay;
    char showOriginal;
    string userInput;
    int showOriginalCount = 0;

    // Checks if user wants to see board for the first time
    cout << "View the original board?";
    cin >> showOriginal;
    cin.ignore(1, '\n');
    cout << endl;
    showOriginal = tolower(showOriginal);
    if(showOriginal == 'y'){
        // Prints the original board if user wants to do, increments count
        board.printOriginal();
        showOriginalCount++;
    }
    cout << endl;
    board.printPlayer();
    
    // Checks if user is going to play, if not then exits
    cout << "Do you want to play?";
    cin >> wantToPlay;
    cin.ignore(1, '\n');
    cout << endl;
    wantToPlay = tolower(wantToPlay);

    if(wantToPlay == 'x'){
        cout << "Exiting program..." << endl;
        exit(-1);
    }
    
    while (wantToPlay == 'y'){
        // Gets coordinates in form of a string and converts characters to uppercase
        cout << "Enter the coordinate for attack";
        getline(cin, userInput);
        cout << endl;
        for (int i = 0; i < userInput.length(); i++){
            userInput[i] = toupper(userInput[i]);
        }
        // Exits if user wants to stop playing
        if(userInput.find("x") != string::npos || userInput.find("X") != string::npos){
            cout << "Exiting program..." << endl;
            exit(-1);
        }
        
        // calls checkAttack with string userInput
        board.checkAttack(userInput);
        // Allows for board option if user still has more to do
        if(showOriginalCount < 3){
            // Displays board if user wants to see it
            cout << "View the original board?";
            cin >> showOriginal;
            cin.ignore(1, '\n');
            cout << endl;
            showOriginal = tolower(showOriginal);
            if(showOriginal == 'y'){
                board.printOriginal();
                showOriginalCount++;
            }
        }
        cout << endl;
        board.printPlayer();
        
        // Checks for the win first because moveAmount is set to remainingShips * 3 which = 0 when remainingShips is 0
        // Exits if no ships remain, exits if user runs out of moves. 
        if(!board.checkWin()){
            cout << "Congratulations! You won!" << endl;
            cout << "Thanks for playing.  Exiting... " << endl;
            exit(-1);
        }
        board.checkLose();

    }

    return 0;
}