#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int heigth = 20;
int snakeX, snakeY, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// Variables for tail
int tailX[100];
int tailY[100];
int nTail; //Amount of tail parts

int speed = 200;

// Initial state of game
void Setup(){
    gameOver = false;
    dir = STOP;
    snakeX = width / 2 - 1;
    snakeY = heigth / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % heigth;
    score = 0;
};

// GUI (grafic user interface)
void Draw(){
    system("cls"); //for Linux should be: system ("clear");
    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < heigth; i++){
        for (int j = 0; j < width; j++){
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == snakeY && j == snakeX) //here was a problem (X and Y were replaced)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        print = true;
                        cout << "o";
                    }
                }
                if (!print)
                    cout << " ";
           }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << "#";
        cout << endl;
        cout << "Score: " << score << endl;
};

// Processing player actions (keyboard)
void Input(){
    if (_kbhit()){
        switch (_getch())
        {
        case '4':
            dir = LEFT;
            break;
        case '6':
            dir = RIGHT;
            break;
        case '8':
            dir = UP;
            break;
        case '5':
            dir = DOWN;
            break;
        case '0':
            gameOver = true;
            break;
        }
    }
};

void Logic(){
// Tail behavior
    int prevX = tailX[0]; //tail X-preposition
    int prevY = tailY[0]; //tail Y-preposition
    int prev2X; //tail X-pre-preposition
    int prev2Y; //tail Y-pre-preposition

    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
// Keystroke processing
    switch (dir){
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    }
// variation #1: with borders:
    /*
    if (snakeX > width || snakeX < 0 || snakeY > heigth || snakeY < 0){
        gameOver = true;
        cout << "GAME IS OVER!";
    }
    */
// variation #2: without borders:
    if (snakeX >= width - 1)
        snakeX = 0;
    else if (snakeX < 0)
        snakeX = width - 2;

    if (snakeY >= heigth)
        snakeY = 0;
    else if (snakeY < 0)
        snakeY = heigth - 1;

    for (int i = 0; i < nTail; i++){
        if (tailX[i] == snakeX && tailY[i] == snakeY){
            gameOver = true;
            cout << "GAME IS OVER!";
        }
    }

// what happens when the fruit is eaten
    if (snakeX == fruitX && snakeY == fruitY){
        score += 10;
        if (speed > 0) speed -= 10; //should be greater or even 0 (zero)
        fruitX = rand() % width;
        fruitY = rand() % heigth;
        nTail++;
    }
};

int main()
{
    Setup();
    while (!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(speed);
    }

    return 0;
}
