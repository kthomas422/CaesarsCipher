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
INSTALL_DIR = ~/bin


.PHONY: default
default: $(TARGET)


$(TARGET): driver.o caesar.o parse_file.o
	$(CC) $(LFLAGS) $^ -o $@


driver.o: driver.c
	$(CC) $(CFLAGS) $< -o $@


caesar.o: caesar.c caesar.h
	$(CC) $(CFLAGS) $< -o $@


parse_file.o: parse_file.c parse_file.h
	$(CC) $(CFLAGS) $< -o $@


.PHONY: install
install: $(TARGET) | $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/$(TARGET)


$(INSTALL_DIR):
	mkdir $(INSTALL_DIR)


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
	rm -rf $(PACKAGE_NAME).tgz $(TARGET)

