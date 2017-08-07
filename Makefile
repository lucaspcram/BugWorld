# Makefile template

## BEGIN Project specific variables ##

# Compiler and options #
CC=gcc
WARN=-Wall
OPT=#-O2 # no opts for now
STD=#-std=c11 # seems to be breaking the build
CFLAGS=$(WARN) $(OPT) $(STD) -g

# project sources #
EXECNAME=bugworld
INCDIR=-I include
SRCDIR=src
SRCEXT=c
OBJEXT=o
BUILDDIR=build
BUILDSUBDIRS=$(addprefix $(BUILDDIR)/, $(shell find $(SRCDIR)/* -type d -printf '%f\n'))
BINDIR=bin

# test sources #
TESTDIR=test
TESTSRC=bugworld_test
TESTOBJ=$(BUILDDIR)/$(TESTSRC).$(OBJEXT)
TESTEXEC=$(BINDIR)/$(TESTSRC)
TESTDEPEND=$(OBJECTSNOMAIN)

# library information #
LMATH=-lm
LNCURSES=-lncurses
LDFLAGS=$(LNCURSES) $(LMATH)

# misc #
RM=rm -f

## END Project specific variables ##

TARGET=$(BINDIR)/$(EXECNAME)
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
OBJECTSNOMAIN=$(filter-out $(BUILDDIR)/main.$(OBJEXT), $(OBJECTS))

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@mkdir -p $(BINDIR)
	@$(CC) $^ -o $(TARGET) $(LIB) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
# uncomment this line if the src folder has code in subdirs
#@mkdir -p $(BUILDSUBDIRS)
	$(CC) $(CFLAGS) $(INCDIR) -c -o $@ $<

.PHONY: test all clean run runtest
test: $(TARGET)
	@echo "Building tests..."
	@$(CC) $(CFLAGS) -c -o $(TESTOBJ) $(TESTDIR)/$(TESTSRC).$(SRCEXT) $(INCDIR) $(LDFLAGS)
	@$(CC) $(CFLAGS) -o $(TESTEXEC) $(TESTDIR)/$(TESTSRC).$(SRCEXT) $(TESTDEPEND) $(INCDIR) $(LDFLAGS)

all: clean $(TARGET) test

clean:
	@echo "Cleaning...";
	@$(RM) -r $(BUILDDIR) $(BINDIR)

run:
	@echo "Running..."
	@./$(TARGET)

runtest:
	@echo "Running tests..."
	@./$(TESTEXEC)
