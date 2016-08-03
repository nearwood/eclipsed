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
	static int count = 0;//, gameCount = 0;
	
	if (s->isGameOver())
	{
		//++gameCount;
		return s->getScores();
	}
	
	if (++count % 250000 == 0) 
		cout << "Round: " << s->round << ", Depth: " << depth << ", Play: " << count << endl;
		//cout << "Round: " << s->round << ", Depth: " << depth << ", Play: " << count << ", Game: " << gameCount << endl;
	//cout << "p" << (int)p->num << "r" << s->round << "d" << depth << "p" << ++count << " -- ";
	
	PlayerBoard *cp = s->getCurrentPlayer();
	std::unordered_map<std::string, int> scores;
	int bestValue = -1000; //sturtevant uses maxn here to avoid else case for scores->find()
	std::list<GameState*> children = GameState::generateChildren(*s);
	
	for (GameState *c : children)
	{
		scores = this->play(c, depth + 1);
		auto it = scores.find(cp->name);
		if (it != scores.cend())
		{
			int currentValue = it->second;
			if (currentValue > bestValue) //>=?
			{
				scores.at(cp->name) = currentValue;
				//move = m
			}
				//else if (v == it->second) //pick one out of equivalent moves
		}
		
		delete c;
	}

	return scores;
}

void Game::turn()
{
	
}

Game::~Game()
{//TODO find out how startState->map is getting deleted earlier
	//delete startState;
}
