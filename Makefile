SOURCES := $(wildcard src/**/*.c)
COMP_ARGS_WIN := $(SOURCES) -o jocoa.exe -std=c99
COMP_ARGS_LINUX := $(SOURCES) -o jocoa -std=c99
WIN_DEST := C:/jocoa
LINUX_DEST := /usr/local/bin
CC := gcc
SHOW_CC_WARNINGS := false

all:
	@echo CC=$(CC)
	@echo SHOW_CC_WARNINGS=$(SHOW_CC_WARNINGS)

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
ifeq ($(SHOW_CC_WARNINGS),true)
	@$(CC) $(COMP_ARGS_WIN)
else
	@$(CC) $(COMP_ARGS_WIN) -w
endif
	@mv ./jocoa.exe "$(WIN_DEST)/jocoa.exe"

linux:
ifeq ($(SHOW_CC_WARNINGS),true)
	@$(CC) $(COMP_ARGS_LINUX)
else
	@$(CC) $(COMP_ARGS_LINUX) -w
endif
	@sudo mv jocoa $(LINUX_DEST)

win-test:
	$(CC) $(COMP_ARGS_WIN)

linux-test:
	$(CC) $(COMP_ARGS_LINUX)