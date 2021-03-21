all: Clean BuildMain RunProgram

BuildMain:
	mkdir -p bin/program
	g++ -o bin/program/main main.cpp

RunProgram:
	./bin/program/main

Clean: 
	rm -rf bin