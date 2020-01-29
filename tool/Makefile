# 2020 David DiPaola. Licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/).

BIN = convert

.PHONY: all
all: $(BIN)

$(BIN): convert.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN)

