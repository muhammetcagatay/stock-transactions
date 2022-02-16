hepsi: derle calistir

derle: 
	gcc -I ./include/ -o ./lib/Emir.o -c ./src/Emir.c
	gcc -I ./include/ -o ./lib/cJSON.o -c ./src/cJSON.c
	gcc -I ./include/ -o ./lib/Banka.o -c ./src/Banka.c
	gcc -I ./include/ -o ./lib/Hisse.o -c ./src/Hisse.c
	gcc -I ./include/ -o ./lib/Portfoy.o -c ./src/Portfoy.c
	gcc -I ./include/ -o ./lib/KarZarar.o -c ./src/KarZarar.c
	gcc -I ./include/ -o ./bin/Test  ./lib/Hisse.o ./lib/Emir.o ./lib/Banka.o ./lib/cJSON.o ./lib/Portfoy.o ./lib/KarZarar.o ./src/Test.c

calistir:
	./bin/Test