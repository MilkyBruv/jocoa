run:

	g++ src/main/main.cpp -o C:/jocoa/jocoa.exe
	g++ src/main/main.cpp -o build/jocoa.exe
	g++ src/main/main.cpp -o releases/jocoa.exe

test:

	g++ src/main/main.cpp -o build/jocoa.exe
	.\build\jocoa.exe