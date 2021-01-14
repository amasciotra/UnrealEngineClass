// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "WordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(WordList);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }        
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
    //set lives
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("The hiddenword is: %s "), *HiddenWord);
    PrintLine(TEXT("Welcome to BullCow Game"));
    PrintLine(TEXT("Please guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives"), Lives);

    PrintLine(TEXT("Please press enter After the Guess"));
}

void UBullCowCartridge::EndGame()
{   
    bGameOver = true;
    PrintLine(TEXT("Press Enter to Play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
        if (HiddenWord == Guess)
        {   
            PrintLine(TEXT("You win"));
            EndGame();
            return;
        }

        if (HiddenWord.Len() != Guess.Len())
        {
            PrintLine(TEXT("The HiddenWord is %i characters long"), HiddenWord.Len());
            PrintLine(TEXT("You entered a %i character long word"), Guess.Len());
            return;

        }

        if(!IsIsogram(Guess))
        {
            PrintLine(TEXT("You did not input a valid Isogram, please try again"));
            return;
        }


        Lives-=1;
        PrintLine(TEXT("You have %i lives remaining"), Lives);
        if(Lives == 0)
        {
            PrintLine(TEXT("You have lost the Game"));
            PrintLine(TEXT("Your hiddenWord was %s"), *HiddenWord);
            EndGame();
            return;
        }   

        //show bulls and counts
        int32 Bulls;
        int32 Cows;
        FBullCowCount Count = GetBullCows(Guess);
        PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);

        PrintLine(TEXT("Guess Again"));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 j = 0;
    int32 i = 0;
    for(i = 0; i < Word.Len()-1; i++)
    {
        for (j = i+1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        } 
    }
    return true;

}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for(FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i]){
            Count.Bulls+=1;
        }
        else
        {
            for (int32 j = 0; j < Guess.Len(); j++)
            {
                if (Guess[i] == HiddenWord[j])
                {
                    Count.Cows+=1;
                    break;
                }
            }
        }
    }
    return Count;
}

