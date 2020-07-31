#pragma once
#include "Core.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>

struct score {
	score() {}
	score(std::string _playerTag, UINT16 _playerScore) {
		playerTag = _playerTag;
		playerScore = min(9999, _playerScore);
	}

	UINT16 playerScore = 0;
	std::string playerTag = "---";


	std::ifstream& read(std::ifstream& in) {
		std::string data;
		std::getline(in, data);
		if (data.empty())
			return in;
		playerTag = data.substr(0, 3);
		data = data.substr(3, 4);
		try{
			playerScore = stoul(data);
		}
		catch (std::invalid_argument) {}
		return in;
	}

	std::ofstream& write(std::ofstream& out) {
		out << playerTag << playerScore << "\n";
		return out;
	}

#pragma region Comparison
	bool operator< (const score o) const {
		return playerScore < o.playerScore;
	}	
	bool operator> (const score o) const {
		return playerScore > o.playerScore;
	}	
	bool operator == (const score o) const {
		return playerScore == o.playerScore;
	}
#pragma endregion

};

class scoreboard {
public:
	scoreboard() {
		
		std::ifstream savedScores("scoreboard");


		while (!savedScores.eof()) {
			if (savedScores.peek() == EOF)
				break;
			score s = score();
			s.read(savedScores);
			savedScores_v.push_back(s);

		}
		savedScores.close();
		for (score s : savedScores_v) {
			std::cout << s.playerTag << s.playerScore << std::endl;
		}
	}

	UINT16 gameScore = 0;

	void drawBoard(Core::Graphics& g) {
		UINT8 _a = 0, _b = 0, _c = 0, _d = 0;
		std::string a, b, c, d, f = "";
		if (gameScore >= 9999) {
			_a = 9;
			_b = 9;
			_c = 9;
			_d = 9;
		}
		else {
			_a = floor(gameScore / 1000);
			_b = floor((gameScore % 1000) / 100);
			_c = floor((gameScore % 100) / 10);
			_d = gameScore % 10;
		}
		a = getFace(_a);
		b = getFace(_b);
		c = getFace(_c);
		d = getFace(_d);

		for (int i = 0; i < 5; i++) {
			f += 
				a.substr(0, a.find('\n')) + 
				b.substr(0, b.find('\n')) +
				c.substr(0, c.find('\n')) +
				d.substr(0, d.find('\n') + 1);

			a = a.substr(a.find('\n') + 1, a.length() - a.find('\n') - 1);
			b = b.substr(b.find('\n') + 1, b.length() - b.find('\n') - 1);
			c = c.substr(c.find('\n') + 1, c.length() - c.find('\n') - 1);
			d = d.substr(d.find('\n') + 1, d.length() - d.find('\n') - 1);
		}
		g.DrawString(220, 0, f.c_str());
			
	}

	void drawSavedScores(Core::Graphics& g) {
		std::string board;
		
		for (score s : savedScores_v) {
			std::string sf;
			sf.resize(s.playerScore < 10 ? 3 : 3-floor(log10(s.playerScore)), '0');
			sf += std::to_string(s.playerScore);
			board += s.playerTag + "                   " + sf + "\n";
		}

		g.DrawString(210, 385, board.c_str());
	}

	void submitScore(std::string tag, UINT16 _score) {
		savedScores_v.push_back(score(tag, _score));
		std::sort(savedScores_v.begin(), savedScores_v.end(), std::greater<score>());
	}

	void writeScores() {
		std::sort(savedScores_v.begin(), savedScores_v.end(),std::greater<score>());
		savedScores_v.resize(10);

		std::ofstream savedScores("scoreboard");
		if (savedScores.is_open()) {
			for (score s : savedScores_v) {
				s.write(savedScores);
			}
		}
	}

	std::string getFace(UINT8 i) {
		switch(i) {
		case 0:
			return std::string(ZERO);
		case 1:
			return std::string(ONE);
		case 2:
			return std::string(TWO);
		case 3:
			return std::string(THREE);
		case 4:
			return std::string(FOUR);
		case 5:
			return std::string(FIVE);
		case 6:
			return std::string(SIX);
		case 7:
			return std::string(SEVEN);
		case 8:
			return std::string(EIGHT);	
		case 9:
			return std::string(NINE);
		default:
			return "";
		}
	}

	char tagCycleDown(char c) {
		if (c == '-')
			return 'z';
		if (c == 'A')
			return '-';
		return c - 1;
	}
	char tagCycleUp(char c) {
		if (c == '-')
			return 'A';
		if (c == 'z')
			return '-';
		return c + 1;
	}

private:
	std::vector<score> savedScores_v;

#pragma region Typeface

#pragma region ZERO
const std::string ZERO =
		" ___ \n"
		"|  /|\n"
		"| + |\n"
		"|/  |\n"
		" --- \n";
#pragma endregion

#pragma region ONE
	const std::string ONE =
		" _   \n"
		"  |  \n"
		"  +  \n"
		"  |  \n"
		" --- \n";
#pragma endregion

#pragma region TWO
	const std::string TWO =
		" ___ \n"
		"    |\n"
		" -+- \n"
		"|    \n"
		" --- \n";
#pragma endregion

#pragma region THEE
	const std::string THREE =
		" ___ \n"
		"    |\n"
		" -+- \n"
		"    |\n"
		" --- \n";
#pragma endregion

#pragma region FOUR
	const std::string FOUR =
		" .  .\n"
		" |  |\n"
		" -+-|\n"
		"    |\n"
		"    |\n";
#pragma endregion

#pragma region FIVE
	const std::string FIVE =
		" ___ \n"
		"|    \n"
		" -+- \n"
		"    |\n"
		" --- \n";
#pragma endregion

#pragma region SIX
	const std::string SIX =
		" ___ \n"
		"|    \n"
		"|-+- \n"
		"|   |\n"
		" --- \n";
#pragma endregion

#pragma region SEVEN
	const std::string SEVEN =
		" ___ \n"
		"    |\n"
		"   + \n"
		"  /  \n"
		" /   \n";
#pragma endregion

#pragma region EIGHT
	const std::string EIGHT =
		" ___ \n"
		"|   |\n"
		" -+- \n"
		"|   |\n"
		" --- \n";
#pragma endregion

#pragma region NINE
	const std::string NINE =
		" ___ \n"
		"|   |\n"
		" -+-|\n"
		"    |\n"
		" --- \n";
#pragma endregion

#pragma endregion
};

extern scoreboard sb;