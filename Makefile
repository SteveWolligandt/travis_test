BIN=travis_test
COV=travis_test_coverage
SRC=main.cpp
STD=-std=c++11

all: run run.cov

$(BIN): $(SRC)
	g++ $(STD) -o $(BIN) $(SRC)

$(COV): $(SRC)
	g++ $(STD) -o $(COV) $(SRC) -fprofile-arcs -ftest-coverage -lgcov

run: $(BIN)
	./$(BIN)

run.cov: $(COV)
	./$(COV) > /dev/null

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f travis_test
	rm -f travis_test_coverage