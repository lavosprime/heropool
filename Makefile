CXXFLAGS = -g -o0 -Wall -Werror -Wpedantic -fno-exceptions -std=c++11
LDFLAGS = -lsqlite3
PROJ = heropool

OBJS = Main.o HeroesByAlilas.o

HEADERS = HeroData.h

all: $(PROJ)

$(PROJ): $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $< $(OBJS) $(LDFLAGS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

HeroesByAlias.cc: makeheromap.py
	python makeheromap.py > $<

clean:
	-rm -f *.o $(PROJ) HeroesByAlias.cc
