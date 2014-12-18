CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -Weffc++ -Wno-error=effc++ -Wno-error=unused-parameter -std=c++11
LDFLAGS = -lsqlite3
RELEASEFLAGS = -O3 -s -DNDEBUG
DEBUGFLAGS = -g -Og
VALIDATEFLAGS = -g -Og -Wunused-macros -Wundef -fsanitize=address -fno-omit-frame-pointer

PROG = heropool
OBJS = main.o herodata.o database.o command.o
HEADERS = herodata.h database.h command.h
GENERATED = HeroesByAlias.inc insert.sql.inc
CPPLINT = http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py

.PHONY: default release debug validate lint lint-headers clean
default: debug

release: CXXFLAGS += $(RELEASEFLAGS)
release: RUNCPPLINT =
release: $(PROG)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: RUNCPPLINT = -python cpplint.py $<
debug: $(PROG) | cpplint.py

validate: CXXFLAGS += $(VALIDATEFLAGS)
validate: RUNCPPLINT = python cpplint.py $<
validate: lint-headers $(PROG) | cpplint.py

# The main program binary is linked together from libraries and object files.
$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Object files depend on generated include files.
$(OBJS): $(GENERATED)

# C++ source files are compiled to object files normally and are linted before
# compliation in some builds.
%.o: %.cc $(HEADERS)
	$(RUNCPPLINT)
	$(CXX) $(CXXFLAGS) -c $<

# SQL source files are stripped of comments and blank lines and then hex-dumped
# as C array initializer lists to be #included in string definitions.
%.sql.inc: %.sql
	sed "/^--.*$$\|^$$/d" $< | xxd -i > $@

# Print hero data as a C++ initializer list to be #included in a map definition.
HeroesByAlias.inc: makeheromap.py HeroNames.json
	python $< > $@

lint: | cpplint.py
	python cpplint.py *.h *.cc

lint-headers: $(HEADERS) | cpplint.py
	python cpplint.py $^

cpplint.py:
	wget --no-verbose --no-clobber $(CPPLINT)

# Remove all non-source files.
clean:
	-rm -f *.o *.inc $(PROG)
