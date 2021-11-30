CXX = g++

LIBSRC = VideoProcessor.cpp StreamCapture.cpp
LIBOBJ = $(LIBSRC:.cpp=.o)

CXXFLAGS = -O3 -std=c++11 -g

OPENCV_INC = `pkg-config opencv --cflags`
OPENCV_LIBS = `pkg-config opencv --libs`

INCLUDE_DIRS = $(OPENCV_INC)
LIBS = -lstdc++ -pthread $(OPENCV_LIBS)

TARGETS = VideoProcessor

all: $(TARGETS)

$(TARGETS) : $(LIBOBJ)
	$(CXX) $(LIBOBJ) $(INCLUDE_DIRS) -o $(TARGETS) $(CXXFLAGS) $(LIBS)

clean:
	$(RM) $(TARGETS) $(OSMLIB) $(OBJ) $(LIBOBJ) *~ *core