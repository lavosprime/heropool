CXXFLAGS = -g -O0 -Wall -Werror -Wpedantic -std=c++11
LDFLAGS = -lsqlite3
PROG = heropool

OBJS = Main.o HeroData.o Database.o Command.o

HEADERS = HeroData.h Database.h Command.h

GENERATED = HeroesByAlias.inc insert.sql.inc

all: $(PROG)

# The main program binary is linked together from libraries and object files.
$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Object files depend on generated include files.
$(OBJS): $(GENERATED)

# C++ source files are compiled to object files normally.
%.o: %.cc $(HEADERS)
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
	-rm -f *.o *.inc $(PROG)
