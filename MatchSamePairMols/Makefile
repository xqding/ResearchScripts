HOME=/home/xqding
LIB_DIR=-L$(HOME)/local/lib -L$(HOME)/lib64
INCLUDE_DIR=-I$(HOME)/local/include/openbabel-2.0
LIBS=-lopenbabel
CFLAGS=-g
CC=gcc

BUILD = ./build
SOURCE = ./src

programs = $(BUILD)/MatchSamePairMols

all:$(programs)

$(BUILD)/%.o: $(SOURCE)/%.cpp
	mkdir -p $(BUILD); $(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

$(programs): %: %.o
	$(CC) $(LIB_DIR) $(LIBS) $(objects) $< -o $@

clean:
	rm $(programs) $(BUILD)/MatchSamePairMols.o
