#include <iostream>
#include <ctime>

bool firstMove(){
    int first_move;
    srand(time(NULL));
    first_move = rand()%2;
    switch (first_move)
    {
    case 0:
        return true;
        break;
    case 1:
        return false;
        break;
    default:
        break;
    }
}
void chooseSymbol(char &player1, char &player2){
    char choice;
    do{
        std::cout << "Choose ( X or O ): " << '\n';
        std::cin >> choice;
        if (choice == 'x' or choice == 'X'){
            player1 = 'X';
            player2 = 'O';
        }
        else if (choice == 'o' or choice == 'O'){
            player1 = 'O';
            player2 = 'X';
        }
        else{
            std::cout << "Invalid choice" << '\n';
        }
    }while((choice != 'o') && (choice != 'O') && (choice != 'x') && (choice != 'X'));
}
std::string chooseMode(){
    int choice;
    do{
        std::cout << "Do you want to play:\n 1. Against the computer.\n 2. Multiplayer.\nChoose 1 or 2: ";
        std::cin >> choice;
        switch(choice){
            case 1:
                return "Computer";
                break;
            case 2:
                return "Multiplayer";
                break;
            default:
                std::cout << "Invalid choice" << '\n';
                break;
        }
    }while(choice != 1 && choice != 2);
}
void drawBoard(char spaces[9]){
    std::cout << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << '\n';
    std::cout << "_____|_____|_____" << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << '\n';
    std::cout << "_____|_____|_____" << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << '\n';
}
void play(char spaces[9], int move, char player){
    spaces[move] = player;
    drawBoard(spaces);
}
bool checkWin(char spaces[9], char player){
    if ((spaces[0] == player) && (spaces[4] == player) && (spaces[8] == player)){
        return true;
    }
    if ((spaces[2] == player) && (spaces[4] == player) && (spaces[6] == player)){
        return true;
    }
    for (int i =0; i<9; i++){
        if(i%3 == 0){
            if ((spaces[i] == player) && (spaces[i+1] == player) && (spaces[i+2] == player)){
                return true;
            }
        }
        if(i<3){
            if ((spaces[i] == player) && (spaces[i+3] == player) && (spaces[i+6] == player)){
                return true;
            }
        }
    }
    return false;
}
bool checkDraw(char spaces[9]){
    for (int i = 0; i<9; i++){
        if (spaces[i] == ' '){
            return false;
        }
    }
    return true;
}
int playerMove(char spaces[9]){
    int move;
    do{
        std::cout << "What's your move ? : ";
        std::cin >> move;
        if (spaces[move] == ' '){
            return move;
        }
        else {
            std::cout << "Invalid move" << '\n';
    }
    }while(spaces[move] != ' ' || move < 0 || move >= 9);
}
int computerMove(char spaces[9], char computer, char player){
    int move;
    for (int i = 0; i < 9; i++){
        if(spaces[i] == ' '){
            spaces[i] = computer;
            if(checkWin(spaces, computer)){
                return i;
            }
            spaces[i] = ' ';
        }
    }
    for (int i = 0; i < 9; i++){
        if(spaces[i] == ' '){
            spaces[i] = player;
            if(checkWin(spaces, player)){
                return i;
            }
            spaces[i] = ' ';
        }
    }
    do{
        srand(time(NULL));
        move = rand()%10;
    } while (spaces[move] != ' ');
    return move;
}

int main(void){
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    std::string mode = chooseMode();
    if (mode == "Computer"){
        char player;
        char computer;
        chooseSymbol(player, computer);
        bool running = true;
        int pmove;
        int cmove;
        std::cout << "************** TIC-TAC-TOE **************" << '\n';
        drawBoard(spaces);
        if (firstMove()){
            std::cout << "You will start first:" << '\n';
            while (running){
                pmove = playerMove(spaces);
                std::cout << "Your move: " << '\n';
                play(spaces, pmove, player);
                if(checkWin(spaces, player)){
                    std::cout << "CONGATULATIONS! YOU WON!" << '\n';
                    running = false;
                    break;
                }
                if(checkDraw(spaces)){
                    std::cout << "It's a tie." << '\n';
                    running = false;
                    break;
                }
                cmove = computerMove(spaces, computer, player);
                std::cout << "The computer's move: " << '\n';
                play(spaces, cmove, computer);
                if(checkWin(spaces, computer)){
                    std::cout << "UNFORTUNATELY, YOU LOST!" << '\n';
                    running = false;
                    break;
                }
                if(checkDraw(spaces)){
                    std::cout << "It's a tie." << '\n';
                    running = false;
                    break;
                }
            }
        }
        else{
            std::cout << "The computer will start first:" << '\n';
            while (running){
                cmove = computerMove(spaces, computer, player);
                std::cout << "The computer's move: " << '\n';
                play(spaces, cmove, computer);
                if(checkWin(spaces, computer)){
                    std::cout << "UNFORTUNATELY, YOU LOST!" << '\n';
                    running = false;
                    break;
                }
                if(checkDraw(spaces)){
                    std::cout << "It's a tie." << '\n';
                    running = false;
                    break;
                }
                pmove = playerMove(spaces);
                std::cout << "Your move: " << '\n';
                play(spaces, pmove, player);
                if(checkWin(spaces, player)){
                    std::cout << "CONGATULATIONS! YOU WON!" << '\n';
                    running = false;
                    break;
                }
                if(checkDraw(spaces)){
                    std::cout << "It's a tie." << '\n';
                    running = false;
                    break;
                }
            }
        }
        std::cout << "*****************************************" << '\n';
    }
    else{
        char player1;
        char player2;
        chooseSymbol(player1, player2);
        bool running = true;
        int p1move;
        int p2move;
        std::cout << "************** TIC-TAC-TOE **************" << '\n';
        drawBoard(spaces);
        while (running){
            p1move = playerMove(spaces);
            std::cout << "Player 1's move: " << '\n';
            play(spaces, p1move, player1);
            if(checkWin(spaces, player1)){
                std::cout << "CONGATULATIONS! PLAYER 1 WON!" << '\n';
                running = false;
                break;
            }
            if(checkDraw(spaces)){
                std::cout << "It's a tie." << '\n';
                running = false;
                break;
            }
            p2move = playerMove(spaces);
            std::cout << "Player 2's move: " << '\n';
            play(spaces, p2move, player2);
            if(checkWin(spaces, player1)){
                std::cout << "CONGATULATIONS! PLAYER 2 WON!" << '\n';
                running = false;
                break;
            }
            if(checkDraw(spaces)){
                std::cout << "It's a tie." << '\n';
                running = false;
                break;
            }
        }
        std::cout << "*****************************************" << '\n';   
    }
    return 0;
}