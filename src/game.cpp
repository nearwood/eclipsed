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
:depth(0), startState(setup)
{
	
}

void Game::play()
{
	cout << "Game start..." << endl;
	int v = this->play(&startState, 0, startState.getFirstPlayer());
	cout << "Game end: " << v << endl;
}

//not sure how to handle >2 players...
int Game::play(GameState* s, uint depth, Player* p)
{
	cout << "Depth: " << depth << ", Play: " << s << endl;
	while (!s->isGameOver() && depth != 10)
	{//while not at final state or max depth
		//for (Player* p : players)
		if (s->getCurrentPlayer() == p)
		{
			int bestValue = -1000;
			for (GameState* c : s->getChildren())
			{
				int value = this->play(c, depth + 1, p); //s->nextPlayer?
				bestValue = max(value, bestValue);
			}
			return bestValue;
		}
		else
		{
			int bestValue = 1000;
			for (GameState* c : s->getChildren())
			{
				int value = this->play(c, depth + 1, p); //s->nextPlayer?
				bestValue = min(value, bestValue);
			}
			return bestValue;
		}
		
	//for p1...pN
		//action phase
		//starting with p1
		//allow action (or pass)
		//go to next player
		//repeat until all players pass, first passer is p1 next round
		//combat phase
		//upkeep phase
	}
	
	return s->getVP(p);
}

void Game::turn()
{
	
}
