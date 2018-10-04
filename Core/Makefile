
INCDIR := inc
SRCDIR := src
OBJDIR := build

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++11

all: $(OBJECTS)
	$(CXX) -I$(INCDIR) -o libfoo.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm build/*; rm libfoo.so
