PROGRAM = app

CXX = gcc

C_FLAGS = -std=c99 -Wall -pedantic

C_SOURCES = src/*.c

INCLUDE_PATH = -I$(PWD)/include
INCLUDE_PATH_WIN = -I ./include

BUILD = build

all: build_dir
	$(CXX) $(C_FLAGS) $(INCLUDE_PATH) $(C_SOURCES) -o $(BUILD)/$(PROGRAM)
	./$(BUILD)/$(PROGRAM) "seeders/books.csv"

win: build_dir_win
	$(CXX) $(C_FLAGS) $(INCLUDE_PATH_WIN) $(C_SOURCES) -o $(BUILD)/$(PROGRAM)
	./$(BUILD)/$(PROGRAM) "seeders/books.csv"

run: 
	./$(BUILD)/$(PROGRAM) "seeders/books.csv"

build_dir:
	@if [ ! -d "$(BUILD)" ]; then \
		mkdir -p $(BUILD); \
	fi

build_dir_win:
	@if not exist "$(BUILD)" ( mkdir "$(BUILD)" )

clean:
	rm -rf $(BUILD)