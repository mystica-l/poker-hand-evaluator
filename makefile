# Makefile
compile:
	make compileCard
	make compileHandEval
	g++ -Wall driver.cpp Card.o HandEvaluator.o -o PokerEvaluator.exe
run:
	./PokerEvaluator.exe
compileCard:
	g++ -Wall Card.cpp -c
compileHandEval:
	g++ -Wall HandEvaluator.cpp -c