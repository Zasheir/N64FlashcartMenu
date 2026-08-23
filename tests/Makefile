CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror
CPPFLAGS += -I../src

TEST_BIN = test_save_folder
SOURCES = test_save_folder.c ../src/menu/path.c ../src/menu/save_folder.c

.PHONY: all test clean
all: test

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -f $(TEST_BIN)
