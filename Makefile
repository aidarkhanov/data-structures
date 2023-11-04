all:
	@clang -o main.out -std=c2x -Wall -Werror -pedantic main.c

clean:
	@rm main.out
