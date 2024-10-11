INCDIR=./include
SRCDIR=./src
OBJDIR=./obj
LIBDIR=./lib

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

all: CHECK_DIR $(TARGET)

CHECK_DIR:
	@if [ ! -d "$(LIBDIR)" ]; then \
		echo "Directory $(LIBDIR) does not exist. Creating it..."; \
		mkdir -p $(LIBDIR); \
	fi
	@if [ ! -d "$(OBJDIR)" ]; then \
		echo "Directory $(OBJDIR) does not exist. Creating it..."; \
		mkdir -p $(OBJDIR); \
	fi

$(LIBDIR)/$(DICT_CXX):
	rootcling -I$(INCDIR) -f $@ -c $(_DEPS) $(LINKDEF)
	@if [ ! -f "$(TARGET)Dict_rdict.pcm" ]; then \
		ln -s $(LIBDIR)/$(TARGET)Dict_rdict.pcm; \
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET): $(OBJ) $(LIBDIR)/$(DICT_CXX)
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(TARGET)Dict_rdict.pcm $(LIBDIR)/$(TARGET)Dict* $(OBJDIR)/*.o *~ core src/*~ $(INCDIR)/*~
