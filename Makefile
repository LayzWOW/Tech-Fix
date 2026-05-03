# Makefile for TechFix - Device Repair Management System
# Compatible with g++ and Embarcadero DevC++

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = TechFix

# Source files
SOURCES = main.cpp TechFix.cpp

# Object files
OBJECTS = main.o TechFix.o

# Header files
HEADERS = TechFix.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile main.cpp
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile TechFix.cpp
TechFix.o: TechFix.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c TechFix.cpp

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean successful!"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild (clean and build)
rebuild: clean all

# Help
help:
	@echo "TechFix Makefile Commands:"
	@echo "  make         - Build the project"
	@echo "  make run     - Build and run the project"
	@echo "  make clean   - Remove build files"
	@echo "  make rebuild - Clean and rebuild"
	@echo "  make help    - Show this help message"

.PHONY: all clean run rebuild help
