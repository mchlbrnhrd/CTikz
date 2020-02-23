SRC = CException.cpp CTikz.cpp main.cpp
BIN = bin/CTikzApp

CTikzApp: $(SRC)
	mkdir -p bin
	g++ -o $(BIN) $(SRC)

clean:
	rm -rf $(BIN)


