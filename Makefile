# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DEBUG 
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# pliki naglowkowe
INC = 

# biblioteki
LIB =  -lm -lpthread -lrt

zad2: zad2.o 
	$(LOADER) $(OPT) zad2.o -o zad2 $(LIB)

zad2.o: zad2.c 
	$(CCOMP) -c $(OPT) zad2.c $(INC) 

zad3: zad3.o 
	$(LOADER) $(OPT) zad3.o -o zad3 $(LIB)

zad3.o: zad3.c 
	$(CCOMP) -c $(OPT) zad3.c $(INC)


clean:
	rm -f *.o
