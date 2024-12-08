.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG -Iheaders
DEBUG_FLAGS   = -g -O0 -Wall -Iheaders
RELEASE_EXEC  = sumOfSquares
DEBUG_EXEC    = sumOfSquares-dbg
SOURCES       = main.cpp Auth.cpp ClientDataBase.cpp Communicator.cpp HandlerVector.cpp Logger.cpp server.cpp StartInterface.cpp
LIBRARY       = -lboost_program_options -lcryptopp


OBJECTS = $(SOURCES:.cpp=.o)

all: release

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(OBJECTS)
	$(Compiler) $(RELEASE_FLAGS) $(OBJECTS) -o $(RELEASE_EXEC) $(LIBRARY)


%.o: %.cpp
	$(Compiler) $(RELEASE_FLAGS) -c $< -o $@

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC) $(OBJECTS)
