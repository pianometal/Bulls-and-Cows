#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();

bool AskToPlayAgain();

FText GetValidGuess();

// Play a new game

FBullCowGame BCGame;

// --------------------- BEGIN APP

int main ()
{

bool bPlayAgain = false;
    
do
{
    PrintIntro();
    
    PlayGame();
    
    bPlayAgain = AskToPlayAgain();
}

    while (bPlayAgain);
    
    std::cout << std::endl << "Thanks for playing!" << std::endl;
    
return 0;

}

// --------------------- END APP

// --------------------- FUNCTIONS

// Introdcue the game //

void PrintIntro()
{
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game. \n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of? \n";
    std::cout << std::endl;
    
    return;
}

// loop continually until valid guess

FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::INVALID_STATUS;
    do {
        // get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        
        // check guess validity
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status) 
        {
        case EGuessStatus::WRONG_LENGTH:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
            break;
        case EGuessStatus:: NOT_ISOGRAM:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::NOT_LOWERCASE:
            std::cout << "Please enter all lowecase letters.\n\n";
            break;
        default:
            // assuming the guess is valid
            break;
        }

    } while(Status != EGuessStatus::OK); // keep looping until no errors
        return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again? ";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y' ) || (Response[0] == 'Y' );
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // Loop for the number of turns asking for guess while game is NOT won
    // Still tries remaing

    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        // Submit Valid guess to the game //
        FBullCowCount BullCowCount =  BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

    }
    
    PrintGameSummary();
    return;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
}
