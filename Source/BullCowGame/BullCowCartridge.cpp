// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
  Super::BeginPlay();
  CreateValidWords();
  SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
  ClearScreen();

  if (bGameOver)
  {
    SetupGame();
  }
  else
  {
    CheckGuess(Input);
  }
}

void UBullCowCartridge::CheckGuess(const FString &Input)
{
  if (Input == HiddenWord)
  {
    bGameOver = true;
    WinGame();
  }
  else
  {
    WrongAnswer(Input);
  }
}

void UBullCowCartridge::SetupGame()
{
  Lives = 5;
  bGameOver = false;
  HiddenWord = PickRandomWord();
  ShowGameRules();
}

void UBullCowCartridge::WrongAnswer(const FString &Input)
{
  Lives--;

  if (Lives < 1)
  {
    bGameOver = true;
    LoseGame();
    return;
  }

  ShowFlavorTextForInput(Input);
  ShowGameStatus();
}

void UBullCowCartridge::WinGame() const
{

  PrintLine(TEXT("Hooray you guessed it!"));
  PrintLine(TEXT("Press [Enter] to start again."));
}
void UBullCowCartridge::LoseGame() const
{
  PrintLine(TEXT("Wrong again. That's GAME OVER, hotshot."));
  PrintLine(TEXT("BTW, the word was %s"), *HiddenWord);
  PrintLine(TEXT("Press [Enter] to try again."));
}

void UBullCowCartridge::ShowFlavorTextForInput(const FString &Input) const
{
  if (Input.Len() != HiddenWord.Len())
  {
    PrintLine(TEXT("I said it's %i letters long, asshole."), HiddenWord.Len());
    PrintLine(TEXT("Try again."));
  }

  else if (!IsIsogram(Input))
  {
    PrintLine("Do you know what an isogram is?\nNo repeating letters, dingdong.");
  }

  else
  {
    PrintLine(TEXT("Hmmm... Not quite. Try again."));
  }

  int32 Bulls, Cows;
  GetBullsCows(Input, Bulls, Cows);
  PrintLine(TEXT("You have %i Bulls and %i Cows"), Bulls, Cows);
}

void UBullCowCartridge::ShowGameRules() const
{
  PrintLine(TEXT("Welcome to this shitty game."));
  PrintLine(TEXT("\nYou have three attempts to guess the\n_mystery_ word."));
  PrintLine(TEXT("\nThe word is currently %i letters long."), HiddenWord.Len());
  PrintLine(TEXT("\nType your guess and press [ENTER] to \nstart."));
}

void UBullCowCartridge::ShowGameStatus() const
{
  PrintLine(TEXT("\nYou have %i tries left."), Lives);
  PrintLine(TEXT("The word is %i letters long."), HiddenWord.Len());
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
  bool bRepeatedChars = false;

  for (int32 i = 0; i < Word.Len(); i++)
  {
    for (int32 c = i + 1; c < Word.Len(); c++)
    {
      if (Word[c] == Word[i])
      {
        return false;
      }
    }
  }

  return true;
}

void UBullCowCartridge::GetBullsCows(const FString& Guess, int32& Bulls, int32& Cows) const
{
  Bulls = 0;
  Cows = 0;

  for(int32 i = 0; i < Guess.Len(); i++)
  {
    if (Guess[i] == HiddenWord[i])
    {
      Bulls++;
      continue;
    }

    for (int32 j = 0; j <Guess.Len(); j++)
    {
      if (Guess[i] == HiddenWord[j])
      {
        Cows++;
        break;
      }
    }
  }
}

FString UBullCowCartridge::PickRandomWord() const
{
  return ValidWords[FMath::RandRange(0, ValidWords.Num())];
}

void UBullCowCartridge::CreateValidWords() 
{
  for (FString Word : Words)
  {
    if (Word.Len() >= 3 && Word.Len() <= 10 && IsIsogram(Word))
    {
      ValidWords.Emplace(Word);
    }
  }
}
