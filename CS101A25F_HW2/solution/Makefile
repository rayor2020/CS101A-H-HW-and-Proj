# Makefile for Library Management System
# Supports both Windows (MinGW/MSYS2) and Linux compilation

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
DEBUGFLAGS = -std=c++14 -Wall -Wextra -g -DDEBUG

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
DATADIR = data

# Target executable
TARGET = library_system
ifeq ($(OS),Windows_NT)
    TARGET = library_system.exe
endif

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Header files
HEADERS = $(wildcard $(INCDIR)/*.h)

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Create data directory if it doesn't exist
$(DATADIR):
	mkdir -p $(DATADIR)

# Build target
$(TARGET): $(OBJECTS) | $(DATADIR)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete! Executable: $(TARGET)"

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Debug build
debug: CXXFLAGS = $(DEBUGFLAGS)
debug: $(TARGET)

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	if exist $(TARGET) del $(TARGET)
else
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
endif

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install (copy to system directory - optional)
install: $(TARGET)
ifeq ($(OS),Windows_NT)
	@echo "Manual installation required on Windows"
else
	sudo cp $(TARGET) /usr/local/bin/
endif

# Create sample data files
setup-data: | $(DATADIR)
	@echo "Creating sample data files..."
	@echo "5|978-0-7432-7356-5|The Da Vinci Code|Dan Brown|Mystery|2003|1|||0|0" > $(DATADIR)/books.txt
	@echo "2|978-0-553-29698-2|A Brief History of Time|Stephen Hawking|Science|1988|1|||0|0" >> $(DATADIR)/books.txt
	@echo "Sample data files created in $(DATADIR)/"

# Help target
help:
	@echo "Library Management System - Makefile Help"
	@echo "=========================================="
	@echo "Available targets:"
	@echo "  all        - Build the project (default)"
	@echo "  debug      - Build with debug symbols"
	@echo "  clean      - Remove build files"
	@echo "  run        - Build and run the program"
	@echo "  setup-data - Create sample data files"
	@echo "  install    - Install to system (Linux only)"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make           # Build the project"
	@echo "  make clean     # Clean build files"
	@echo "  make run       # Build and run"
	@echo "  make debug     # Build with debugging"

# Phony targets
.PHONY: all debug clean run install setup-data help