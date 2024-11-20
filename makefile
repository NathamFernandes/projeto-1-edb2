all:
	gcc -I ./include -std=c99 src/*.c -o app && ./app "books.csv"
win:
	gcc -I .\include -std=c99 src/*.c -o app && .\app "books.csv"
windev:
	gcc -I .\include -Wall -pedantic -std=c99 src/*.c -o app