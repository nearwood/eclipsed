# TODO

1. ~~valgrind~~
1. Fix never ending game after sector placing implementation
  a. Graph short game in viz
  a. Don't let AI go into crazy disc debt (limit to expected income?)
  a. implement alpha-beta pruning
  a. Add dynamic programming via GameState hashes
  a. may have to monte-carlo the move choice logic
  a. or just have a time limit and pick the best
1. Fix/Figure out phantom memory leak with PlayerBoard
1. Fix all generic integral types to fixed-size types
