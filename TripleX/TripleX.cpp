#include <iostream>
#include <ctime>

void PrintIntroduction(int Difficulty)
{
    std::cout << "\n\nYou are a secret agen breaking into a level " << Difficulty << " secure server room \n";
    std::cout << "You need to enter the correct codes to continue... \n\n";
}
bool PlayGame(int Difficulty)
{
    
    PrintIntroduction(Difficulty);
    const int CodeA = (rand() % Difficulty) + 1;
    const int CodeB = (rand() % Difficulty) + 1;
    const int CodeC = (rand() % Difficulty) + 1;
    const int CodeSum = CodeA+CodeB+CodeC;
    const int CodeProduct = CodeA*CodeB*CodeC;

    std::cout << "There are 3 numbers in the Code \n";
    std::cout << "The sum of the 3 codes is: " << CodeSum<< std::endl;
    std::cout << "The product of the 3 codes is: " << CodeProduct<< std::endl;

    // Store players Guess'
    int GuessA, GuessB, GuessC; 
    std::cin >> GuessA >> GuessB >> GuessC;
    
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    // check if correct 
    if(GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "You win! \n" ;
        return true;
    }
    else
    {
        std::cout << "You suck \n";
        return false;
    }
}

int main()
{
    srand(time(NULL));
    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;

    while(LevelDifficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();
        std::cin.ignore();

        if (bLevelComplete)
        {
            LevelDifficulty+=1;
            std::cout << "You will now keep going\n";
        }
        else
        {
            std::cout << "Please Try Again, you failed";
        }
    }

    std::cout << "You beat the game, congrats loser \n";

    return 0;
}