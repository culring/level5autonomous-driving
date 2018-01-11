CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		level5-autonomous-driving.o

LIBS =

TARGET =	level5-autonomous-driving.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
