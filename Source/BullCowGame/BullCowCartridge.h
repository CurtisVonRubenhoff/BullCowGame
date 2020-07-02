// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
  GENERATED_BODY()

public:
  virtual void BeginPlay() override;
  virtual void OnInput(const FString &Input) override;

  // Your declarations go below!
private:
  void ShowGameRules() const;
  void ShowGameStatus() const;
  void ShowFlavorTextForInput(const FString &Input) const;
  void WinGame() const;
  void LoseGame() const;
  void WrongAnswer(const FString &Input);
  void CheckGuess(const FString &Input);
  void SetupGame();
  void CreateValidWords();
  void GetBullsCows(const FString& Guess, int32& BullCount, int32& CowCount) const;

  bool IsIsogram(const FString &Word) const;
  FString PickRandomWord() const;

  UPROPERTY(EditAnywhere)
  FString HiddenWord = "neighbor";
  
  UPROPERTY(EditAnywhere)
  int32 Lives = 3;

  TArray<FString> PossibleWords;
  TArray<FString> ValidWords;
  bool bGameOver = false;

};
