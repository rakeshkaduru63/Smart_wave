CC = gcc
CFLAGS = -Wall -g
LIBS = -lmosquitto -lpthread

SRCS = main.c client.c
OBJS = $(SRCS:.c=.o)
TARGET = mqtt_app

all: $(TARGET)

$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c client.h
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f $(TARGET) $(OBJS)
