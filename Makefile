# ============================================================
# TechFix Makefile
# Compiler: g++ | Standard: C++11
# Compatible with Embarcadero DevC++ (MinGW) and Linux/Mac
# ============================================================

CXX      = g++
CXXFLAGS = -Wall -std=c++11
TARGET   = TechFix
HEADERS  = TechFix.h
SRCS     = main.cpp TechFix.cpp
OBJS     = main.o TechFix.o

# Detect OS for clean command (Windows uses del, Unix uses rm)
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    EXE = $(TARGET).exe
else
    RM = rm -f
    EXE = $(TARGET)
endif

# ── Default: build the executable ───────────────────────────
all: $(TARGET)

# ── Link ────────────────────────────────────────────────────
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful! Run with: ./$(TARGET)"

# ── Compile each .cpp ────────────────────────────────────────
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

TechFix.o: TechFix.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c TechFix.cpp

# ── Clean build artifacts ────────────────────────────────────
clean:
	$(RM) $(OBJS) $(EXE)
	@echo "Clean successful!"

# ── Run the program ──────────────────────────────────────────
run: $(TARGET)
	./$(TARGET)

# ── Rebuild from scratch ─────────────────────────────────────
rebuild: clean all

# ── Help ─────────────────────────────────────────────────────
help:
	@echo "TechFix Makefile Commands:"
	@echo "  make         - Build the project"
	@echo "  make run     - Build and run the project"
	@echo "  make clean   - Remove build files"
	@echo "  make rebuild - Clean and rebuild"
	@echo "  make help    - Show this help message"

.PHONY: all clean run rebuild help