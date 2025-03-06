default:
	g++ src/**/*.cpp -o jocoa

gwin:
	cd C: /d && mkdir jocoa
	g++ src/**/*.cpp -o C:/jocoa/jocoa.exe

cwin:
	cd C: /d && mkdir jocoa
	clang++ src/**/*.cpp -o C:/jocoa/jocoa.exe

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