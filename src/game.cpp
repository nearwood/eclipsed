#include "game.h"

#include <iostream>

using namespace std;

Game::Game(GameState* setup)
:startState(setup), depth(0)
{
	
}

void Game::play()
{
	cout << "Game start..." << endl;
	std::unordered_map<std::string, int> scores = this->play(startState, 0);
	
	for (auto it = scores.cbegin(); it != scores.cend(); ++it)
		cout << it->first << ": " << it->second << endl;
	
	//cout << "Game end." << endl; //<< scores << endl;
}

std::unordered_map<std::string, int> Game::play(GameState* s, uint depth)
{
	static int count = 0;
	
	/*if (++count % 1000 == 0)*/ cout << "Round: " << s->round << ", Depth: " << depth << ", Plays: " << ++count << endl;
	//cout << "p" << (int)p->num << "r" << s->round << "d" << depth << "p" << ++count << " -- ";
	
	if (s->isGameOver())// || depth == 10)
		return s->getScores();
	
	PlayerBoard *cp = s->getCurrentPlayer();
	std::unordered_map<std::string, int> scores;
	int bestValue;
	std::list<GameState*> children = GameState::generateChildren(*s);
	
	for (auto it = s->players.cbegin(); it != s->players.cend(); ++it)
	{
		PlayerBoard *p = (*it);
		//cout << "Perspective: " << p->name << endl;
		cout << "p" << (int)p->num << "r" << s->round << "d" << depth << "p" << ++count << endl;
		
		if (p == cp)
		{
			bestValue = -1000;
			for (GameState* c : children)
			{
				std::unordered_map<std::string, int> subScores = this->play(c, depth + 1);
				auto it = subScores.find(p->name);
				int value = 0;
				if (it != subScores.cend())
					value = it->second;
				
				bestValue = max(value, bestValue);
			}
			
			scores.insert({ p->name, bestValue });
		}
		else
		{
			bestValue = 1000;
			for (GameState* c : children)
			{
				std::unordered_map<std::string, int> subScores = this->play(c, depth + 1);
				auto it = subScores.find(p->name);
				int value = 0;
				if (it != subScores.cend())
					value = it->second;
				
				bestValue = min(value, bestValue);
			}
			
			scores.insert({ p->name, bestValue });
		}
	}
	
	//cout << ";" << endl;
	
	return scores;
}

void Game::turn()
{
	
}
