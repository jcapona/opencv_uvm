CXX=g++ -std=c++11
# Includes, cflags
INCLUDES=`pkg-config opencv --cflags`
CXXOPTS=-Wall -g -O2
CXXFLAGS=$(CXXOPTS) $(INCLUDES)
# Libs flags
LDLIBS=`pkg-config opencv --libs`
# Binaries
TARGETS=split threshold hist histGray mask hist_filter_2d

all:$(TARGETS)

clean:
	rm -f $(TARGETS)

default:
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

