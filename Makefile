CXX ?= g++
CXXFLAGS := -Isrc/ -MMD -c -g 
LDFLAGS = 

AR ?= ar
SRCDIR = src
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
DEP = $(OBJS:%.o=%.d)

lib: $(SRCDIR)/libast.a

$(SRCDIR)/libast.a: $(OBJS)
	$(AR) -rc $@ $^

bin: testing_bin/test_bin

testing_bin/test_bin:  testing_bin/main.o $(SRCDIR)/libast.a
	$(CXX) $(LDFLAGS) -o $@ $^


-include $(DEP)


%.o:%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


run: testing_bin/test_bin
	./$<

clean:
	rm -f $(SRCDIR)/*.o $(SRCDIR)/*.a testing_bin/*.o