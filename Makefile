SOURCES := $(wildcard src/**/*.cpp)
COMP_ARGS_WIN := $(SOURCES) -o jocoa.exe -std=c++17
COMP_ARGS_LINUX := $(SOURCES) -o jocoa -std=c++17

default:
	g++ $(COMP_ARGS)

initwin:
	cd C: && mkdir -p C:/jocoa

gwin:
	make initwin
	g++ $(COMP_ARGS_WIN)
	mv .\jocoa.exe C:\jocoa\jocoa.exe

cwin:
	make initwin
	clang++ $(COMP_ARGS_WIN)
	mv .\jocoa.exe C:\jocoa\jocoa.exe

glinux:
	g++ $(COMP_ARGS_LINUX)
	sudo mv jocoa /usr/local/bin

clinux:
	clang++ $(COMP_ARGS_LINUX)
	sudo mv jocoa /usr/local/bin