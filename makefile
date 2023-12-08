# Makefile
compile:
	MinGW32-make compileCard
	MinGW32-make compileHandEval
	g++ -Wall driver.cpp Card.o HandEvaluator.o
compileCard:
	g++ -Wall Card.cpp -c
compileHandEval:
	g++ -Wall HandEvaluator.cpp -c