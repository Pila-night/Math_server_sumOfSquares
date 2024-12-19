.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG 
DEBUG_FLAGS   = -g -O0 -Wall 
RELEASE_EXEC  = unit
DEBUG_EXEC    = unit-dbg
SOURCES       = UnitTest.cpp Auth.cpp ClientDataBase.cpp Communicator.cpp HandlerVector.cpp Logger.cpp server.cpp StartInterface.cpp
LIBARY        = -lboost_program_options -lcryptopp -lUnitTest++
all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): $(SOURCES)
	$(Compiler) $(DEBUG_FLAGS) $(SOURCES) -o $(DEBUG_EXEC) $(LIBARY)

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(SOURCES)
	$(Compiler) $(RELEASE_FLAGS) $(SOURCES) -o $(RELEASE_EXEC) $(LIBARY)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)
