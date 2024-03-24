# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -IInc

# Directories
SRCDIR = Src
INCDIR = Inc
BINDIR = build

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
# Object files
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
# Dependency files
DEPS := $(OBJECTS:.o=.d)

# Executable
EXECUTABLE = semaphore

.PHONY: all clean

all: $(BINDIR)/$(EXECUTABLE)

# Rule to link object files into executable
$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@echo "[Linking...]"
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files into object files
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "[Compiling...]"
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

clean:
	rm -rf $(BINDIR)
