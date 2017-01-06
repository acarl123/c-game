/* This is the console executable that makes use of the BullCow class
This acts as the view in an MVC pattern and is responsible for all
user int32eraction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// unreal-friendly syntax
using FText = std::string;
using int32 = int;


FText GetValidGuess();
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

// entry point for application
int main() {
	PrintIntro();

	do
	{
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	FText Guess = "";
	// loop asking for guesses while game is not won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}

	// summarize game
	PrintGameSummary();

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?(y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	char first_letter = Response[0];
	first_letter = toupper(first_letter);

	if (first_letter == 'Y')
	{
		return true;
	}
	else if (first_letter == 'N')
	{
		return false;
	}
	else
	{
		AskToPlayAgain();
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, you won!\n";
	}
	else
	{
		std::cout << "Sorry - better luck next time\n";
	}
}

FText GetValidGuess() {
	//get a guess from the player
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try: " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lowercase input.\n\n";
			break;
		case EGuessStatus::Not_Alpha:
			std::cout << "Please only enter alpha characters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintIntro() {
	// int32roduce the game
	std::cout << "\n\nWelcome to Bulls and Cows\n";
	std::cout << "      ,              ,\n";
	std::cout << "     /               \\\n";
	std::cout << "    ((__ - ^^-, -^^-__))\n";
	std::cout << "      `-_-- - ' `---_-'\n";
	std::cout << "       <__ |o` 'o|__>\n";
	std::cout << "           \\  `  /\n";
	std::cout << "            ): :(\n";
	std::cout << "            :o_o:\n";
	std::cout << "             \"-\"\n";
	printf("Can you guess the %d letter isogram I'm thinking of\n", BCGame.GetHiddenWordLength());
	std::cout << std::endl;
	return;
}
