// Игра Word Jumble.
// Классическая игра-головоломка, в которой пользователь разгнадывает слова с подсказками или без них

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    // Создание двумерного массива строк из слов (word) и подсказок к ним (hint)

    enum fields { WORD, HINT, NUM_FIELDS }; // прием позволяет определить количество элементов (NUM_FIELDS) каждой строки будущего двумерного массива 
    const int NUM_WORDS = 5; // количество "строк" будущего двумерного массива
    const string WORDS[NUM_WORDS][NUM_FIELDS] = // создаем и инициализируем двумерный массив слов и подсказок 
    {
        {"wall", "Do you fill you're banging your head agains something?"}, //первый элемент массива 
        {"glasses", "These might bhelp you see the answer."},               //второй элемент массива 
        {"labored", "Going slowly, is it?"},                                //третий элемент массива 
        {"persistent", "Keep at it."},                                      //четвертый элемент массива 
        {"jumble", "It's what the game is all about."}                      //пятый элемент массива 
    };

    // Выбор случайного слова

    srand(static_cast<unsigned int>(time(0)));
    int choise = (rand() % NUM_WORDS);
    string theWord = WORDS[choise][WORD]; // слово, которое нужно угадать
    string theHint = WORDS[choise][HINT]; // подсказка для загаданного слова

    // Перемешивание слова

    string jumble = theWord; // перемешанный вариант слова
    int length = jumble.size();
    for (int i = 0; i < length; ++i) {
        int index1 = (rand() % length);
        int index2 = (rand() % length);
        char temp = jumble[index1];
        jumble[index1] = jumble[index2];
        jumble[index2] = temp;
    }

    // Приглашение игрока

    cout << "\t\t\tWelcome to Word Jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter 'hint' for a hint.\n";
    cout << "Enter 'quit' to quit the game.\n\n";
    cout << "The jumble is: " << jumble;
    string guess;
    cout << "\n\nYour guess: ";
    cin >> guess;

    // Игоровой цикл

    while ((guess != theWord) && (guess != "quit")) {
        if (guess == "hint")
            cout << theHint;
        else
            cout << "Sorry, that's not it. Please, try again.";
        cout << "\n\nYour guess: ";
        cin >> guess;
    }

    // Завершение игры

    if (guess == theWord)
        cout << "\nThat's it! You guessed it!\n";
    else if (guess == "quit")
        cout << "\nThanks for playing!\n";
return 0;
}