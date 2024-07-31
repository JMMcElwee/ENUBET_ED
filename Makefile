INCDIR=./include
SRCDIR=./src
OBJDIR=./obj

CXX=g++

CXXFLAGS= -I$(INCDIR) -Wall -Wno-unused-command-line-argument -std=c++17 `root-config --cflags`
LDFLAGS=`root-config --ldflags`
LIBS=`root-config --glibs`


TARGET = EventDisplay
LINKDEF = $(TARGET)LinkDef.h

DICT_CXX = $(TARGET)Dict.cxx

H_EXT = hh
DEPS= $(shell find $(INCDIR) -type f -name *.$(H_EXT))
_DEPS = $(patsubst $(INCDIR)/%,%,$(DEPS))
#$(info	DEPS are $(_DEPS))

SRC_EXT = cc
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRC_EXT))

_OBJ = $(SOURCES:.cc=.o)
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(_OBJ))

all: $(TARGET)

lib/$(DICT_CXX):
	rootcling -I$(INCDIR) -f $@ -c $(_DEPS) $(LINKDEF)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET): $(OBJ) lib/$(DICT_CXX)
	 $(CXX)  $(CXXFLAGS) $(LDFLAGS) $(LIBS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) lib/$(TARGET)Dict* $(OBJDIR)/*.o *~ core src/*~ $(INCDIR)/*~
