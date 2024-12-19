.PHONY: all debug release clean test

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG 
DEBUG_FLAGS   = -g -O0 -Wall 
RELEASE_EXEC  = sumOfSquares
TEST_EXEC     = UnitTest
SOURCES       = Auth.cpp ClientDataBase.cpp Communicator.cpp HandlerVector.cpp Logger.cpp server.cpp StartInterface.cpp
LIBRARY       = -lboost_program_options -lcryptopp

OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = UnitTest.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: release

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(OBJECTS) main.o
	$(Compiler) $(RELEASE_FLAGS) $(OBJECTS) main.o -o $(RELEASE_EXEC) $(LIBRARY)

test: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS) $(OBJECTS)
	$(Compiler) $(RELEASE_FLAGS) $(TEST_OBJECTS) $(OBJECTS) -o $(TEST_EXEC) $(LIBRARY) -lUnitTest++

%.o: %.cpp
	$(Compiler) $(RELEASE_FLAGS) -c $< -o $@

clean:
	rm -f $(RELEASE_EXEC) $(TEST_EXEC) $(OBJECTS) $(TEST_OBJECTS) main.o
