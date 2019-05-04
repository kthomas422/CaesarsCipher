# Kyle Thomas
# Makefile for Caesar' Cipher


CC = gcc

### Development Flags
CFLAGS = -c -g -Wall -Wstrict-prototypes
LFLAGS = -g -Wall -Wstrict-prototypes

### Production Flags
#CFLAGS = -c -O3
#LFLAGS = -O3

PACKAGE_NAME = CaesarsCipher
TARGET = caesar


.PHONY: default
default: $(TARGET)


$(TARGET): driver.o caesar.o
	$(CC) $(LFLAGS) $^ -o $@


driver.o: driver.c
	$(CC) $(CFLAGS) $< -o $@


caesar.o: caesar.c caesar.h
	$(CC) $(CFLAGS) $< -o $@


.PHONY: package
package: Makefile *.c *.h
	mkdir $(PACKAGE_NAME)
	cp driver.c $(PACKAGE_NAME)/
	cp caesar.c $(PACKAGE_NAME)/
	cp caesar.h $(PACKAGE_NAME)/
	cp Makefile $(PACKAGE_NAME)/
	tar -czvf $(PACKAGE_NAME).tgz $(PACKAGE_NAME)
	rm -rf $(PACKAGE_NAME)


.PHONY: clean
clean:
	rm -rf *.o


.PHONY: immaculate
immaculate: clean
	rm -rf $(PACKAGE_NAME).tgz $(PROG)

