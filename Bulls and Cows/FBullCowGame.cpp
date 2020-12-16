#pragma once

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map 

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3, 5}, {4, 6}, {5,8}, {6,15} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isogram
    
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen; // set up map
    for (auto Letter : Word)     // for all letters of the word
    {
        Letter = tolower(Letter); // handle mixed case
        if (LetterSeen[Letter]) { // if the letter is in the map
            return false; //we do NOT have an isogram
        }
        else {
            LetterSeen[Letter] = true; // add the letter to the map as seen
        }
    
    }
    
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter)) // if not a lowercase letter
        {
        return false;
        }
    }
    return true;
}

void FBullCowGame::Reset()
{

    const FString HIDDEN_WORD = "planet";
    
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    
    return;
}

// CHECKING THE GUESS

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess))
    {
        return EGuessStatus::NOT_ISOGRAM;
    }
    else if (!IsLowercase(Guess)) // TODO if the guess isn't all lowercase
    {
        return EGuessStatus::NOT_LOWERCASE;
    }
    else if ( Guess.length() != GetHiddenWordLength() )
    {
        return EGuessStatus::WRONG_LENGTH;
    }
    else
    {
        return EGuessStatus::OK;
    }

}

// recives a VALID guess, increments turn, and returns count

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
    
    // loop thruogh the guess
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        // compare letters against the guess
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            if ( Guess [GChar] == MyHiddenWord [MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
                
            }
        }

    }
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}
