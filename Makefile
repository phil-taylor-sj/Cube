LIB = lib\libsfml
LIBS = -Llib -lsfml-graphics -lsfml-window -lsfml-system
TEST_LIBS = $(LIBS) -lgtest -lgtest_main -pthread
INCLUDES = -Iinclude -Ilib/SFML/include
TEST_INCLUDES = $(INCLUDES) -Itests 
CC = g++
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
CFLAGS = -g -Wall

# Define the target executable
TARGET = bin/Cube.exe
TEST_TARGET = bin/TestCube.exe

# Define the source files
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)

# Define the test files
TEST_SRCS = $(wildcard $(TEST_DIR)/**/*.cpp $(TEST_DIR)/*.cpp)

# Define the object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Rule to build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(TEST_LIBS)

# Rule to build test object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c -o $@ $<

# Ensure the obj and bin directories exist before compilation
$(OBJS) $(TEST_OBJS): | $(OBJ_DIR)
$(TARGET) $(TEST_TARGET): | $(BIN_DIR)

# Create the obj and bin directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Clean target to remove generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)
