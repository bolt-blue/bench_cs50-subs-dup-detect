CC ?= clang

.PHONY: all
all: benchmark generate-input test
	./test

benchmark:

generate-input:

test:

clean:
	rm benchmark generate-input test
