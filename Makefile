#------------------------------------------------------------------------------
# Compilation and Linking
#------------------------------------------------------------------------------

CC=g++

STDLIB=-std=c++11
WARNINGS=-Wall -Wextra -Werror
OPTLVL=-O4
SFML=-lsfml-system -lsfml-graphics -lsfml-audio -lsfml-window

CFLAGS=$(STDLIB) $(OPTLVL) $(WARNINGS)
LFLAGS=$(STDLIB) $(OPTLVL) $(WARNINGS) $(SFML)

#------------------------------------------------------------------------------
# Output
#------------------------------------------------------------------------------

TARGET=giants

SRCDIR=src
OBJDIR=obj
BINDIR=bin

#------------------------------------------------------------------------------
# System Detection
#------------------------------------------------------------------------------

UNAME_S := $(shell uname -s)

#------------------------------------------------------------------------------
# Input
#------------------------------------------------------------------------------

SRC := $(wildcard $(SRCDIR)/*.cc)
INC := $(wildcard $(SRCDIR)/*.h)
OBJ := $(SRC:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

#------------------------------------------------------------------------------
# Dirty Work
#------------------------------------------------------------------------------

seperator := @printf "%0.s-" {1..80}; echo ''

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ) $(SRC) $(INC) | $(BINDIR)
	$(seperator)
	@echo Linking objects
	@$(CC) $(LFLAGS) $(OBJ) -o $@
	$(seperator)
	@echo "Executable: "$(TARGET)

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
	
.PHONY: clean
clean:
	rm -rf $(OBJDIR)/ $(TARGET) $(GIANTS)
