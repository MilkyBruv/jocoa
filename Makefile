SOURCES := $(wildcard src/**/*.cpp)
COMP_ARGS := $(SOURCES) -o jocoa.exe -std=c++17

default:
	g++ $(COMP_ARGS)

initwin:
	cd C: && mkdir -p C:/jocoa

gwin:
	make initwin
	g++ $(COMP_ARGS)
	mv .\jocoa.exe C:\jocoa\jocoa.exe

cwin:
	make initwin
	clang++ $(COMP_ARGS)
	mv .\jocoa.exe C:\jocoa\jocoa.exe

glinux:
	g++ $(COMP_ARGS)
	sudo mv jocoa /usr/local/bin

clinux:
	clang++ $(COMP_ARGS)
	sudo mv jocoa /usr/local/bin

test:
	g++ $(COMP_ARGS)
	./jocoa test.json

gwin-test:
	g++ $(COMP_ARGS)

cwin-test:
	clang++ $(COMP_ARGS)

glinux-test:
	g++ $(COMP_ARGS)

clinux-test:
	clang++ $(COMP_ARGS)