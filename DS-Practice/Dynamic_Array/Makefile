CC 		   := g++
CFLAGS     := -Wall -I/src
SRCDIR     := src
SRCEXT     := cpp
BINDIR     := bin
BUILDDIR   := build
TESTDIR    := test
TARGET     := $(BINDIR)/runner
TESTTARGET := $(BINDIR)/testrunner

DEPS       := $(SRCDIR)/dynArr.h
OBJS       := $(BUILDDIR)/main.o $(BUILDDIR)/dynArr.o
TSUITE     := TestSuite_dynArr
TOBJ       := $(TESTDIR)/TestSuite_dynArr.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(TOBJ): $(TESTDIR)/$(TSUITE).$(SRCEXT)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TESTTARGET): $(TOBJ)
	$(CC) -o $(TESTTARGET) $(TOBJ)

run: $(TARGET)
	@echo ""
	$(TARGET)
	@echo ""

test: $(TESTTARGET)
	@echo ""
	$(TESTTARGET)
	@echo ""

clean:
	rm -f $(BUILDDIR)/*.o $(BINDIR)/* $(TESTDIR)/*.o

.PHONY: clean

.PHONY: run

.PHONY: test