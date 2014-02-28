BUILD_DIR = build/
SRC_DIR = ./

CC    ?= gcc
CXX   ?= g++
 
EXE = rectangle_splitter4
 
CDEBUG = -g -Wall 
CXXDEBUG = -g -Wall

INCLUDE = -I$(BUILD_DIR) -I$(SRC_DIR)
 
CSTD = -std=c99
CXXSTD = -std=c++11
 
CFLAGS = -O0  $(CDEBUG) $(CSTD)  $(INCLUDE)
CXXFLAGS = -O0  $(CXXDEBUG) $(CXXSTD) $(INCLUDE)
 
 
CPPOBJ = main  

FILES = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(CPPOBJ)))
OBJS  = $(addprefix $(BUILD_DIR), $(addsuffix .o, $(CPPOBJ)))

 
.PHONY: all
all: rectangle_splitter4
 
rectangle_splitter4: $(FILES) 
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)$(EXE) $(OBJS) $(LIBS)
 
$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
