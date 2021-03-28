# Defines the C compiler
CC := GCC

# Protection for stack-smashing attack
STACK := -fstack-protector-all -Wstack-protector

# Specifies to GCC the required warnings
WARNS := -Wall -Wextra -pedantic # -pedantic warns on language standards

# Flags for compiling
CFLAGS := -O3 $(STACK) $(WARNS)

# Color prefix for Linux distributions
COLOR_PREFIX := e

# Color definition for print purpose
BROWN=\$(COLOR_PREFIX)[0;33m
BLUE=\$(COLOR_PREFIX)[1;34m
END_COLOR=\$(COLOR_PREFIX)[0m

# Source code directory structure
BINDIR := bin
SRCDIR := src
LIBDIR := lib

# Source code file extension
SRCEXT := c

# Binary name
BINARY := ooc

# %.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.$(SRCEXT))))
OBJECTS :=$(patsubst %,$(LIBDIR)/%.o,$(NAMES))

#
# Compilation Rules
#

default: all

# Help message
help:
	@echo "Object-oriented C"
	@echo "    all      - Compiles and generates binary files"
	@echo "    clean    - Clean the project by removing binaries"
	@echo "    help     - Prints a help message with target rules"

all: $(OBJECTS)
	@echo -en "$(BROWN)LD $(END_COLOR)"
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(CFLAGS) $(LIBS)
	@echo -en "\n--\nBinary file placed at $(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n"

$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo -en "$(BROWN)CC $(END_COLOR)";
	$(CC) -c $^ -o $@ $(CFLAGS) $(LIBS)

# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/*;