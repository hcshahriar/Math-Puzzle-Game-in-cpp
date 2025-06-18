#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

void displayMenu();
int getDifficulty();
void playGame(int difficulty);
int generateQuestion(int difficulty);
int generateRandomNumber(int min, int max);
void clearInputBuffer();

int main() {
    srand(time(0)); 
    
    int choice;
    int difficulty;
    
    do {
        displayMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                difficulty = getDifficulty();
                playGame(difficulty);
                break;
            case 2:
                cout << "Thanks for playing! Goodbye.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 2);
    
    return 0;
}

void displayMenu() {
    cout << "\n=== Math Puzzle Game ===\n";
    cout << "1. Start Game\n";
    cout << "2. Quit\n";
    cout << "Enter your choice: ";
}

int getDifficulty() {
    int choice;
    cout << "\nSelect Difficulty Level:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "Enter your choice (1-3): ";
    
    while(true) {
        cin >> choice;
        clearInputBuffer();
        
        if(choice >= 1 && choice <= 3) {
            return choice;
        } else {
            cout << "Invalid choice. Please enter 1, 2, or 3: ";
        }
    }
}

void playGame(int difficulty) {
    int score = 0;
    int questions = 5; 
    int attempts = 3;
    
    cout << "\nStarting game with " << questions << " questions...\n";
    cout << "You have " << attempts << " attempts per question.\n\n";
    
    for(int i = 1; i <= questions; i++) {
        cout << "Question " << i << ":\n";
        int correctAnswer = generateQuestion(difficulty);
        int playerAnswer;
        bool correct = false;
        
        for(int attempt = 1; attempt <= attempts; attempt++) {
            cout << "Attempt " << attempt << ": ";
            cin >> playerAnswer;
            clearInputBuffer();
            
            if(playerAnswer == correctAnswer) {
                cout << "Correct! Well done.\n";
                score++;
                correct = true;
                break;
            } else {
                if(attempt < attempts) {
                    cout << "Incorrect. Try again.\n";
                } else {
                    cout << "Incorrect. The correct answer was: " << correctAnswer << endl;
                }
            }
        }
    }
    
    cout << "\nGame Over!\n";
    cout << "Your score: " << score << " out of " << questions << endl;
}

int generateQuestion(int difficulty) {
    int num1, num2;
    int operation;
    int min, max;
    
    
    switch(difficulty) {
        case 1: // Easy
            min = 1;
            max = 10;
            operation = rand() % 2; // Only addition or subtraction
            break;
        case 2: // Medium
            min = 5;
            max = 20;
            operation = rand() % 3; // Addition, subtraction, or multiplication
            break;
        case 3: // Hard
            min = 10;
            max = 30;
            operation = rand() % 4; // All operations
            break;
    }
    
    num1 = generateRandomNumber(min, max);
    num2 = generateRandomNumber(min, max);
    
    
    if(operation == 3) {
        while(num2 == 0 || num1 % num2 != 0) {
            num1 = generateRandomNumber(min, max);
            num2 = generateRandomNumber(1, max); 
        }
    }
    
    int answer;
    string opSymbol;
    
    switch(operation) {
        case 0: // Addition
            answer = num1 + num2;
            opSymbol = "+";
            break;
        case 1: // Subtraction
            answer = num1 - num2;
            opSymbol = "-";
            break;
        case 2: // Multiplication
            answer = num1 * num2;
            opSymbol = "*";
            break;
        case 3: // Division
            answer = num1 / num2;
            opSymbol = "/";
            break;
    }
    
    cout << "What is " << num1 << " " << opSymbol << " " << num2 << "? ";
    return answer;
}

int generateRandomNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
