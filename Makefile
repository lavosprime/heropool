CXXFLAGS = -g -O0 -Wall -Werror -Wpedantic -std=c++11
LDFLAGS = -lsqlite3
PROJ = heropool

OBJS = Main.o HeroData.o Database.o

HEADERS = HeroData.h Database.h

GENERATED = HeroesByAlias.inc insert.sql.inc

all: $(PROJ)

# The main program binary is linked together from libraries and object files.
$(PROJ): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# C++ source files are compiled to object files normally.
%.o: %.cc $(HEADERS) $(GENERATED)
	$(CXX) $(CXXFLAGS) -c $<

# SQL source files are stripped of comments and blank lines and then hex-dumped
# as C array initializer lists to be #included in string definitions.
%.sql.inc: %.sql
	sed "/^--.*$$\|^$$/d" $< | xxd -i > $@

# Print hero data as a C++ initializer list to be #included in a map definition.
HeroesByAlias.inc: makeheromap.py HeroNames.json
	python $< > $@

# Remove all non-source files.
clean:
	-rm -f *.o *.inc $(PROJ)
