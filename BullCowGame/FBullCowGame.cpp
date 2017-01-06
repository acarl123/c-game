#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // must be an isogram (no repeating letters)
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		LetterSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

// receives valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		if (MyHiddenWord.find(Guess[i]) != FString::npos)
		{
			if (Guess[i] == MyHiddenWord[i])
			{
				BullCowCount.Bulls++;
			}
			else
			{
				BullCowCount.Cows++;
			}
		}
	}

	// check if guess matches hidden word
	if (Guess == MyHiddenWord)
	{
		bGameWon = true;
	}

	return BullCowCount;
}
