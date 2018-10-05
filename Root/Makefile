
INCDIR := inc
SRCDIR := src
OBJDIR := build

INCCORE := ../Core/inc
LIBCORE := ../Core

INCHipo := ../Hipo/inc
LIBHipo := ../Hipo


ROOT := $(shell root-config --cflags) $(shell root-config --libs)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++11

BUILD := $(shell mkdir -p build)

CFLAGS := $(CFLAGS) $(ROOT)

INCLUDES := -I$(INCCORE) -I$(INCHipo)
LIBS := -L$(LIBCORE) -L$(LIBHipo)

.PHONY: all clean
all: $(BUILD) $(OBJECTS)
	$(CXX) -I$(INCDIR)  $(INCLUDES) $(LIBS) -o libtestRoot.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR)  $(INCLUDES) $(LIBS) -c $< -o $@

clean:
	rm build/*; rm libfoo.so; rm -rf build
