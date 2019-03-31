CC 		 := g++
CFLAGS   := -Wall -I/src
SRCDIR   := src
SRCEXT   := cpp

TARGET   := bin/runner
BUILDDIR := build

DEPS := $(SRCDIR)/dynArr.h
OBJS := $(BUILDDIR)/main.o $(BUILDDIR)/dynArr.o 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)

run:
	$(TARGET)