CXX ?= g++
CXXFLAGS := -c -g
LDFLAGS = 

AR ?= ar
SRCDIR = src
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

lib: $(SRCDIR)/libast.a

$(SRCDIR)/libast.a: $(OBJS)
	$(AR) -rc $@ $^

bin: testing_bin/test_bin

testing_bin/test_bin:  testing_bin/main.o $(SRCDIR)/libast.a
	$(CXX) $(LDFLAGS) -o $@ $^


%.o:%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<



clean:
	rm -f $(SRCDIR)/*.o $(SRCDIR)/*.a