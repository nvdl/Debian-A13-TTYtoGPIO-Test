CC=gcc
CFLAGS=-Wall -std=c99

CPP=g++
CPPFLAGS=-Wall -c -O3

LDFLAGS=-Wall -O3 -lgpio

# $@ = automatic variable which matches the file name of the target of the rule
# $< = automatic variable which denotes the first dependency

OBJECTS= main.o

temp:
	gcc main.c -lgpio -o ttytogpio.exe

all: test

test: $(OBJECTS)
	@echo ============================================================
	@echo Linking...
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo ============================================================

main.o: main.c
	@echo ============================================================
	@echo Compiling $< to $@
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	@echo "Cleaning..."
	$(shell rm *.o 2> /dev/null)
	$(shell rm test 2> /dev/null)
	@echo "Done"