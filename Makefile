SOURCES := $(wildcard src/**/*.cpp)

default:
	g++ src/**/*.cpp -o jocoa

initwin:
	cd C: && mkdir -p C:/jocoa

gwin:
	g++ $(SOURCES) -o jocoa.exe
	mv .\jocoa.exe C:\jocoa\jocoa.exe

cwin:
	make initwin
	clang++ $(SOURCES) -o jocoa.exe
	mv .\jocoa.exe C:\jocoa\jocoa.exe

glinux:
	g++ src/**/*.cpp -o jocoa
	sudo mv jocoa /usr/local/bin

clinux:
	clang++ src/**/*.cpp -o jocoa
	sudo mv jocoa /usr/local/bin

test:
	g++ src/**/*.cpp -o jocoa
	./jocoa test.json

gwin-test:
	g++ src/**/*.cpp -o jocoa.exe

cwin-test:
	clang++ src/**/*.cpp -o jocoa.exe

glinux-test:
	g++ src/**/*.cpp -o jocoa

clinux-test:
	clang++ src/**/*.cpp -o jocoa