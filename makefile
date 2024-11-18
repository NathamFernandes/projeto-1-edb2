all:
	gcc -std=c99 src/*.c -o app && ./app "books.csv"
