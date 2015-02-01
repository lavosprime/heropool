CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -pedantic -pedantic-errors \
	-Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Weffc++ \
	-Wfloat-equal -Wformat=2 -Wlogical-op -Wmissing-declarations \
	-Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
	-Wsign-conversion -Wsign-promo -Wshadow -Wstrict-null-sentinel \
	-Wstrict-overflow=5 -Wswitch-default -Wundef -Wuseless-cast \
	-Wzero-as-null-pointer-constant \
	-Wno-error=effc++ -Wno-error=unused-parameter
LDFLAGS = -lsqlite3
RELEASEFLAGS = -O3 -s -DNDEBUG
DEBUGFLAGS = -g -Og
VALIDATEFLAGS = -g -Og -Wsuggest-final-types -Wsuggest-final-methods -Wunused-macros -fsanitize=address,undefined -fno-omit-frame-pointer

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
