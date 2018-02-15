CC=arm-linux-gnueabihf-g++ -g
#CC=arm-linux-gnueabihf-gcc -g
#CC=gcc -g

#CFLAGS=-c -Wall --sysroot=/usr/local/carlson-minot/crosscompilers/arm-none-linux-gnueabi/libc-2013.11-33-sysroot
CFLAGS=-c -Wall
#CFLAGS=-c -Wall

SOURCES=qmain.c logging.c SPI.c
INCDIR=
LIBS=Includes
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=SPI
 
 
all: $(SOURCES) $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJECTS) -I=$(LIBS)
    $(CC) $(SOURCES) -I=$(LIBS) $< -o $@
    
qmain.o:
    $(CC) $(CFLAGS) -I=$(INCDIR) $< -o $@
    
logging.o:
    $(CC) $(CFLAGS) -I=$(INCDIR) $< -o $@
    
SPI.o:
    $(CC) $(CFLAGS) -I=$(INCDIR) $< -o $@
 
clean:
    rm -rf *.o $(EXECUTABLE)

