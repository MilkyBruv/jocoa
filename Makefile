default:
	g++ src/**/*.cpp -o jocoa
	./jocoa

win:
	cd C: /d && mkdir jocoa
	g++ src/**/*.cpp -o jocoa
	g++ src/**/*.cpp -o C:/jocoa/jocoa.exe

linux:
	g++ src/**/*.cpp -o jocoa
	sudo mv jocoa /usr/local/bin

clinux:
	clang++ src/**/*.cpp -o jocoa
	sudo mv jocoa /usr/local/bin