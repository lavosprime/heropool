CXXFLAGS = -g -O0 -Wall -Werror -Wpedantic -std=c++11
LDFLAGS = -lsqlite3
PROJ = heropool

OBJS = Main.o HeroData.o

HEADERS = HeroData.h

GENERATED = HeroesByAlias.inc

all: $(PROJ)

$(PROJ): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cc $(HEADERS) $(GENERATED)
	$(CXX) $(CXXFLAGS) -c $<

HeroesByAlias.inc: makeheromap.py
	python $< > $@

clean:
	-rm -f *.o $(PROJ) $(GENERATED)
