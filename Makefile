BIN=travis_test
SRC=main.cpp
STD=-std=c++11

all: $(BIN)

$(BIN): $(SRC)
	g++ $(STD) -o $(BIN) $(SRC)

run: $(BIN)
	./$(BIN)