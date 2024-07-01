########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = Clock
VERSION = \"1.1.0\"
EXT = .cpp
SRCDIR = src
OBJDIR = obj

# Additional data flags
DATA_FLAGS = -DAPP_NAME=\"$(APPNAME)\" \
			 -DAPP_VERSION=$(VERSION)
CXXFLAGS := $(CXXFLAGS) $(DATA_FLAGS)

# SDL2 config
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs)
SDL2_IMAGE_CFLAGS := $(shell pkg-config --cflags SDL2_image)
SDL2_IMAGE_LDFLAGS := $(shell pkg-config --libs SDL2_image)
CXXFLAGS := $(CXXFLAGS) $(SDL2_CFLAGS) $(SDL2_IMAGE_CFLAGS)
LDFLAGS := $(LDFLAGS) $(SDL2_LDFLAGS) $(SDL2_IMAGE_LDFLAGS)

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

#######################################################################
############################### Tests #################################
#######################################################################

# Tests settings
TESTSDIR = tests
TESTSRCS = $(wildcard $(TESTSDIR)/*$(EXT))
TESTBINS = $(TESTSRCS:$(TESTSDIR)/%$(EXT)=$(TESTSDIR)/%)

# Building rule for test .o files
$(OBJDIR)/%.test.o: $(TESTSDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Builds test executables
$(TESTSDIR)/%: $(OBJDIR)/%.test.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Runs the tests
.PHONY: test
test: $(TESTBINS)
	@for test in $^; do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME) $(OBJDIR)/*.test.o $(TESTBINS)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE) $(OBJDIR)\\*.test.o $(TESTBINS:.exe)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)