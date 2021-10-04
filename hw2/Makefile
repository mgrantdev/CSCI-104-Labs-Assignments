# all: interpreter

interpreter: Interpreter.cpp ProgramState.o LetStatement.o PrintStatement.o EndStatement.o GotoStatement.o ArithmeticStatement.o ConditionStatement.o SubroutineStatement.o Interpreter.o
	g++ -g -Wall Interpreter.cpp ProgramState.o LetStatement.o PrintStatement.o EndStatement.o GotoStatement.o ArithmeticStatement.o ConditionStatement.o SubroutineStatement.o -o interpreter

Interpreter.o: Interpreter.cpp
	g++ -g -Wall Interpreter.cpp -c -o Interpreter.o

ProgramState.o: ProgramState.h ProgramState.cpp
	g++ -g -Wall ProgramState.cpp -c -o ProgramState.o

LetStatement.o: LetStatement.h LetStatement.cpp
	g++ -g -Wall LetStatement.cpp -c -o LetStatement.o

PrintStatement.o: PrintStatement.h PrintStatement.cpp
	g++ -g -Wall PrintStatement.cpp -c -o PrintStatement.o

GotoStatement.o: GotoStatement.h GotoStatement.cpp
	g++ -g -Wall GotoStatement.cpp -c -o GotoStatement.o

ArithmeticStatement.o: ArithmeticStatement.h ArithmeticStatement.cpp
	g++ -g -Wall ArithmeticStatement.cpp -c -o ArithmeticStatement.o

ConditionStatement.o: ConditionStatement.h ConditionStatement.cpp
	g++ -g -Wall ConditionStatement.cpp -c -o ConditionStatement.o

SubroutineStatement.o: SubroutineStatement.h SubroutineStatement.cpp
	g++ -g -Wall SubroutineStatement.cpp -c -o SubroutineStatement.o

EndStatement.o: EndStatement.h EndStatement.cpp
	g++ -g -Wall EndStatement.cpp -c -o EndStatement.o

.PHONY: clean

clean:
	-rm *.o interpreter