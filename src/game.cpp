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
	cout << "Game end." << endl;
	
	for (auto it = scores.cbegin(); it != scores.cend(); ++it)
		cout << it->first << ": " << it->second << endl;
}

//maxn
std::unordered_map<std::string, int> Game::play(GameState* s, uint depth)
{
	static int count = 0;
	
	/*if (++count % 1000 == 0)*/ cout << "Round: " << s->round << ", Depth: " << depth << ", Plays: " << ++count << endl;
	//cout << "p" << (int)p->num << "r" << s->round << "d" << depth << "p" << ++count << " -- ";
	
	if (s->isGameOver())// || depth == 10)
		return s->getScores();
	
	PlayerBoard *cp = s->getCurrentPlayer();
	std::unordered_map<std::string, int> scores;
	scores.insert({ cp->name, -1000 });
	cout << "Player: " << cp->name << endl;
	//int bestValue = -1000;
	std::list<GameState*> children = GameState::generateChildren(*s);
	
	for (GameState *c : children)
	{
		std::unordered_map<std::string, int> subScores = this->play(c, depth + 1);
		auto it = subScores.find(cp->name);
		if (it != subScores.cend())
		{
			int v = it->second;
			auto it2 = scores.find(cp->name);
			int bestValue = 0;
			if (it2 != scores.cend() && v > it2->second) //>=?
			{
				bestValue = it2->second;
				scores.at(cp->name) = bestValue;
				//move = m
			}
		}
		//else if (v == it->second) //pick one out of equivalent moves
	}
	
	return scores;
}

void Game::turn()
{
	
}
