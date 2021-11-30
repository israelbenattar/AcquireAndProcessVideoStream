CXX=g++

LIBSRC=VideoProcessor.cpp StreamCapture.cpp
LIBOBJ=$(LIBSRC:.cpp=.o)

INCS=-I.
CFLAGS = -Wall -std=c++11 -g  $(INCS) `pkg-config --cflags --libs opencv4` -pthread
CXXFLAGS =  -Wall -std=c++11 -g $(INCS) `pkg-config --cflags --libs opencv4` -pthread
TARGETS = VideoProcessor

all: $(TARGETS)

$(TARGETS): $(LIBOBJ)
	$(CXX) $(LIBOBJ) -o $(TARGETS) $(CXXFLAGS)

clean:
	$(RM) $(TARGETS) $(OSMLIB) $(OBJ) $(LIBOBJ) *~ *core

# depend:
# 	makedepend -- $(CFLAGS) -- $(SRC) $(LIBSRC)
