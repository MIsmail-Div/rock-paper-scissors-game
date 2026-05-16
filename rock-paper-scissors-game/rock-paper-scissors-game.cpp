#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include<random>
using namespace std;

enum class enChoice { Rock = 1, Paper, Scissors };
enum class enWinner { Player = 1, Computer, Draw };

struct roundInfo {
	short roundNumber;
	enChoice playerChoice;
	enChoice computerChoice;
	enWinner roundWinner;
	string winnerName = "";
};

struct gameResult {
	short gameRounds = 0;
	short playerWinTimes = 0;
	short computerWinTimes = 0;
	short drawTimes = 0;
	enWinner gameWinner;
	string winnerName = "";
};

int readNumber(const string& Message, int From, int To) {
	int Number;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < From || Number > To);
	return Number;
}

enChoice getPlayerChoice() {
	return enChoice(readNumber("\nYour Choice: [1]: Rock, [2]: Paper, [3]: Scissors ? ", 1, 3));
}

int randomNumber(int From, int To) {
	static mt19937 gen(random_device{}());
	uniform_int_distribution<> dist(From, To);
	return dist(gen);
}

enChoice getComputerChoice() {
	return enChoice(randomNumber(1, 3));
}

enWinner getRoundWinner(const roundInfo& round) {
	if (round.playerChoice == round.computerChoice) return enWinner::Draw;
	else if (
		(round.playerChoice == enChoice::Rock && round.computerChoice == enChoice::Scissors) ||
		(round.playerChoice == enChoice::Paper && round.computerChoice == enChoice::Rock) ||
		(round.playerChoice == enChoice::Scissors && round.computerChoice == enChoice::Paper)
		)
		return enWinner::Player;
	else return enWinner::Computer;
}

string choiceName(enChoice choice) {
	string Arr[]{ "Rock","Paper","Scissors" };
	return Arr[int(choice) - 1];
}

string winnerName(enWinner winner) {
	string Arr[]{ "Player","Computer","Draw" };
	return Arr[int(winner) - 1];
}

void setWinnerScreenColor(enWinner winner) {
	switch (winner) {
	case enWinner::Player: system("color 2F"); break;
	case enWinner::Computer: system("color 4F"); break;
	case enWinner::Draw: system("color 6F");
	}
}




void printRoundInfo(const roundInfo& round) {
	cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _Round [" << round.roundNumber << "]_ _ _ _ _ _ _ _ _ _ _ _\n\n";
	cout << "Player Choice   : " << choiceName(round.playerChoice) << endl;
	cout << "Computer Choice : " << choiceName(round.computerChoice) << endl;
	cout << "Round Winner    : " << round.winnerName << endl;
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";



}

enWinner getGameWinner(const gameResult& result) {
	if (result.playerWinTimes > result.computerWinTimes) return enWinner::Player;
	else if (result.computerWinTimes > result.playerWinTimes) return enWinner::Computer;
	else return enWinner::Draw;

}

gameResult updataScore(short gameRounds, short playerWinTimes, short computerWinTimes, short drawTimes) {
	gameResult result;
	result.gameRounds = gameRounds;
	result.playerWinTimes = playerWinTimes;
	result.computerWinTimes = computerWinTimes;
	result.drawTimes = drawTimes;
	result.gameWinner = getGameWinner(result);
	result.winnerName = winnerName(result.gameWinner);
	return result;
}

gameResult playGame() {
	int howManyRounds = readNumber("\nHow Many Rounds (1-10) ? ", 1, 10);
	roundInfo round;
	short playWinTimes = 0, computerWinTimes = 0, drawTimes = 0;
	for (int i = 1; i <= howManyRounds; i++) {
		cout << "\nRound [" << i << "] begins:\n";
		round.roundNumber = i;
		round.playerChoice = getPlayerChoice();
		round.computerChoice = getComputerChoice();
		round.roundWinner = getRoundWinner(round);
		round.winnerName = winnerName(round.roundWinner);

		switch (round.roundWinner) {
		case enWinner::Player: playWinTimes++; break;
		case enWinner::Computer: computerWinTimes++; break;
		case enWinner::Draw: drawTimes++; break;
		}
		printRoundInfo(round);
		setWinnerScreenColor(round.roundWinner);
	}
	return updataScore(howManyRounds, playWinTimes, computerWinTimes, drawTimes);
}


string tabs(int number) {
	string t = "";
	for (int i = 1; i <= number; i++) {
		t += "\t";
	}
	return t;
}

void showScreenGameOver() {
	cout << endl;
	cout << tabs(5) << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n\n";
	cout << tabs(5) << "                       +++ Game Over +++\n\n";
	cout << tabs(5) << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n\n";
}

void printGameResult(const gameResult& result) {
	cout << tabs(5) << "_ _ _ _ _ _ _ _ _ _ _ _ _[Game Result]_ _ _ _ _ _ _ _ _ _\n\n";
	cout << tabs(5) << "Game Rounds        : " << result.gameRounds << endl;
	cout << tabs(5) << "Player Won Times   : " << result.playerWinTimes << endl;
	cout << tabs(5) << "Computer Won Times : " << result.computerWinTimes << endl;
	cout << tabs(5) << "Draw Times         : " << result.drawTimes << endl;
	cout << tabs(5) << "Final Winner       : " << result.winnerName << endl;
	cout << tabs(5) << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n";


}

void resetScreen() {
	system("cls");
	system("color 0F");
}

void startGame() {
	bool playAgain = true;
	do {
		resetScreen();
		gameResult result = playGame();
		showScreenGameOver();
		printGameResult(result);
		setWinnerScreenColor(result.gameWinner);
		cout << tabs(5) << "Do You Want To Play Again (Y/N) ? ";
		cin >> playAgain;

	} while (playAgain == true);
}




int main() {

	startGame();

}