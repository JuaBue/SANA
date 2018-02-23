CC=arm-linux-gnueabihf-g++ -g
#CC=arm-linux-gnueabihf-gcc -g
#CC=gcc -g

#CFLAGS=-c -Wall --sysroot=/usr/local/carlson-minot/crosscompilers/arm-none-linux-gnueabi/libc-2013.11-33-sysroot
CFLAGS=-Wall -pthread
#CFLAGS=-c -Wall

SOURCES=qmain.c logging.c SPI.c ads1299.c
INCDIR=
LIBS=Includes
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=SPI
 
 
all:
	$(CC) $(CFLAGS) $(SOURCES) -I$(LIBS) -o $(EXECUTABLE)
    
qmain.o: qmain.c
	$(CC) $(CFLAGS) -I$(LIBS) $< -o $@
    
logging.o: logging.c
	$(CC) $(CFLAGS) -I$(LIBS) $< -o $@
    
SPI.o: SPI.c
	$(CC) $(CFLAGS) -I$(LIBS) $< -o $@
 
clean:
	rm -rf *.o $(EXECUTABLE)

