all: read_csv.o
	gcc -o main read_csv.o
read_csv.o: read_csv.c
	gcc -c read_csv.c
run:
	./main
