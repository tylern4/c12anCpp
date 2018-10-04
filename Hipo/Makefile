
INCDIR := inc
SRCDIR := src
OBJDIR := build

INCCORE := ../Core/inc
LIBCORE := ../Core

INCHIPO := $(HOME)/software/Clas12Tool/Hipo
LIBHIPO := $(HOME)/software/Clas12Tool/lib

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++11
INCLUDES := -I$(INCCORE) -I$(INCHIPO)
LIBS := -L$(LIBCORE) -L$(LIBHIPO)

all: $(OBJECTS)
	$(CXX) -I$(INCDIR)  $(INCLUDES) $(LIBS) -o libhipoBase.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) $(INCLUDES) $(LIBS) -c $< -o $@

clean:
	rm build/*; rm libhipoBase.so
