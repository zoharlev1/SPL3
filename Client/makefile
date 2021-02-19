CFLAGS:= -c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread


all: Client


Client: bin/action.o bin/actionExit.o bin/actionJoin.o bin/actionLogout.o bin/Book.o bin/Client.o bin/connectionHandler.o bin/KeyboardInput.o bin/ServerReader.o bin/main.o
	@echo 'Building target: client'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/Client bin/action.o bin/actionExit.o bin/actionJoin.o bin/actionLogout.o bin/Book.o bin/Client.o bin/connectionHandler.o bin/KeyboardInput.o bin/ServerReader.o bin/main.o $(LDFLAGS)
	@echo 'Finished building target: Client'
	@echo ' '

bin/action.o: src/action.cpp
	g++ $(CFLAGS) -o bin/action.o src/action.cpp

bin/actionExit.o: src/actionExit.cpp
	g++ $(CFLAGS) -o bin/actionExit.o src/actionExit.cpp

bin/actionJoin.o: src/actionJoin.cpp
	g++ $(CFLAGS) -o bin/actionJoin.o src/actionJoin.cpp

bin/actionLogout.o: src/actionLogout.cpp
	g++ $(CFLAGS) -o bin/actionLogout.o src/actionLogout.cpp

bin/Book.o: src/Book.cpp
	g++ $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/KeyboardInput.o: src/KeyboardInput.cpp
	g++ $(CFLAGS) -o bin/KeyboardInput.o src/KeyboardInput.cpp

bin/ServerReader.o: src/ServerReader.cpp
	g++ $(CFLAGS) -o bin/ServerReader.o src/ServerReader.cpp    

bin/main.o: src/main.cpp
	g++ $(CFLAGS) -o bin/main.o src/main.cpp    


clean:
	rm -f bin/*