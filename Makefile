# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Linker flags
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
INCDIR = include
SRCDIR = src
OBJDIR = obj

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp

# Object files
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SOURCES)))

# Executable name
EXEC = main

# Default target
all: $(EXEC)

# Link the object files to create the final executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Compile main.cpp into object file
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean target to remove generated files
clean:
	rm -rf $(OBJDIR) $(EXEC)

# Phony targets
.PHONY: all clean
