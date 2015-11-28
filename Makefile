SRC = \
    lourdes/cpu/mutex.cpp \
    lourdes/cpu/sleep.cpp \
    lourdes/cpu/thread.cpp \
    lourdes/cpu/timer.cpp \
    lourdes/cpu/ping.cpp \
    lourdes/cpu/socket.cpp

OBJ = $(SRC:.cpp=.o)
OUT = liblourdes.a
INCLUDES = -I. -I/usr/local/include
CCFLAGS = -O2
CC = g++

.SUFFIXES: .cpp
.cpp.o:
    $(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
    ar rcs $(OUT) $(OBJ)

clean:
    rm -f $(OBJ) $(OUT) Makefile.bak
