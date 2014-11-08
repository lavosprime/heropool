CXXFLAGS = -g -O0 -Wall -Werror -Wpedantic -std=c++11
LDFLAGS = -lsqlite3
PROJ = heropool

OBJS = Main.o HeroesByAlias.o

HEADERS = HeroData.h

all: $(PROJ)

$(PROJ): $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

HeroesByAlias.cc: makeheromap.py
	python $< > $@

clean:
	-rm -f *.o $(PROJ) HeroesByAlias.cc
