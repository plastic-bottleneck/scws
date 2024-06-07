CC = cc
LIBS = -lmicrohttpd
TARGET = scws
SRC = scws.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
