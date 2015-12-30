#include "game.h"

#include <iostream>

using namespace std;

/* http://www.scribd.com/doc/77523125/Eclipse-English-Rule-Book

function minimax(node, depth, maximizingPlayer)
    if depth = 0 or node is a terminal node
        return the heuristic value of node
    if maximizingPlayer
        bestValue := -∞
        for each child of node
            val := minimax(child, depth - 1, FALSE)
            bestValue := max(bestValue, val)
        return bestValue
    else
        bestValue := +∞
        for each child of node
            val := minimax(child, depth - 1, TRUE)
            bestValue := min(bestValue, val)
        return bestValue

(* Initial call for maximizing player *)
minimax(origin, depth, TRUE)
*/

Game::Game(GameState setup)
:startState(setup), depth(0)
{
	
}

void Game::play()
{
	cout << "Game start..." << endl;
	std::unordered_map<std::string, int> scores = this->play(&startState, 0);
	
	for (auto it = scores.cbegin(); it != scores.cend(); ++it)
		cout << it->first << ": " << it->second << endl;
	
	//cout << "Game end." << endl; //<< scores << endl;
}

std::unordered_map<std::string, int> Game::play(GameState* s, uint depth)
{
	cout << "Round: " << s->round << ", Depth: " << depth << endl;
	
	if (s->isGameOver() || depth == 10)
		return s->getScores();
	
	//while not at final state or max depth
	
	//Need multiplayer (3+) logic
	//for each player run minimax against all other players.
	
	PlayerBoard *cp = s->getCurrentPlayer();
	std::unordered_map<std::string, int> scores;
	for (auto it = s->players.cbegin(); it != s->players.cend(); ++it)
	{
		PlayerBoard *p = (*it);
		if (p == cp)
		{
			cout << "Perspective: " << p->name << endl;
			int bestValue = -1000;
			for (GameState* c : s->getChildren())
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
			cout << "Opponent: " << p->name << endl;
			int bestValue = 1000;
			for (GameState* c : s->getChildren())
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
	
	return scores;
}

void Game::turn()
{
	
}
