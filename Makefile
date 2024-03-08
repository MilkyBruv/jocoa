win:

	cd C: /d && mkdir jocoa
	g++ src/jocoa/jocoa.cpp -o C:/jocoa/jocoa.exe
	g++ src/jocoa/jocoa.cpp -o build/jocoa.exe

linux:

	g++ src/jocoa/jocoa.cpp lib/json.hpp -o build/jocoa
	cd build && sudo mv jocoa /usr/local/bin

test:

	g++ src/jocoa/jocoa.cpp -o build/jocoa.exe
	.\build\jocoa.exe