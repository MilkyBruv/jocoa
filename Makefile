windows:

	g++ src/main/main.cpp -o C:/jocoa/jocoa.exe
	g++ src/main/main.cpp -o build/jocoa.exe

linux:

	g++ src/main/main.cpp lib/json.hpp -o build/jocoa
	cd build && sudo mv jocoa /usr/local/bin

test:

	g++ src/main/main.cpp -o build/jocoa.exe
	.\build\jocoa.exe