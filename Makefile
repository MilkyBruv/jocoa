SOURCES := $(wildcard src/**/*.cpp)
COMP_ARGS_WIN := $(SOURCES) -o jocoa.exe -std=c++17
COMP_ARGS_LINUX := $(SOURCES) -o jocoa -std=c++17
WIN_DEST := C:/jocoa
LINUX_DEST := /usr/local/bin
CXX := g++
SHOW_CXX_WARNINGS := false

all:
	@echo CXX=$(CXX)
	@echo SHOW_CXX_WARNINGS=$(SHOW_CXX_WARNINGS)

ifeq ($(OS),Windows_NT)
	@echo DEST=$(WIN_DEST)
	@make initwin -s
	@make win -s
else
	@echo DEST=$(LINUX_DEST)
	@make linux -s
endif
	@echo Done

initwin:
	@cd C: && mkdir -p "$(WIN_DEST)"

win:
	@make initwin
ifeq ($(SHOW_CXX_WARNINGS),true)
	@$(CXX) $(COMP_ARGS_WIN)
else
	@$(CXX) $(COMP_ARGS_WIN) -w
endif
	@mv ./jocoa.exe "$(WIN_DEST)/jocoa.exe"

linux:
ifeq ($(SHOW_CXX_WARNINGS),true)
	@$(CXX) $(COMP_ARGS_LINUX)
else
	@$(CXX) $(COMP_ARGS_LINUX) -w
endif
	@sudo mv jocoa $(LINUX_DEST)

win-test:
	$(CXX) $(COMP_ARGS_WIN)

linux-test:
	$(CXX) $(COMP_ARGS_LINUX)