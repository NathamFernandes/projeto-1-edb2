PROGRAM = app

CXX = gcc

C_FLAGS = -std=c99 -Wall -pedantic

C_SOURCES = src/*.c

INCLUDE_PATH = -I$(PWD)/include

BUILD = $(PWD)/build

all: build_dir
	$(CXX) $(C_FLAGS) $(INCLUDE_PATH) $(C_SOURCES) -o $(BUILD)/$(PROGRAM)
	./$(PROGRAM) "books.csv"

win: build_dir
	$(CXX) $(C_FLAGS) $(INCLUDE_PATH) $(C_SOURCES) -o $(BUILD)/$(PROGRAM)
	./$(PROGRAM) "books.csv"
windev: build_dir
	$(CXX) $(C_FLAGS) $(INCLUDE_PATH) $(C_SOURCES) -o $(BUILD)/$(PROGRAM)
	./$(PROGRAM) "books.csv"

build_dir:
	@if [ ! -d "$(BUILD)" ]; then \
		mkdir -p $(BUILD); \
	fi

clean:
	rm -rf $(BUILD)
