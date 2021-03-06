heropool
========

A tool for keeping track of friends' Dota 2 hero pools.

Depends on the Boost libraries. Boost is available as the package
`libboost-all-dev` in apt (on Debian-based Linux distributions such as Ubuntu);
search the Internet to find whether your package manager has an equivalent,
or see [the Boost website](http://www.boost.org/users/download/)
for information on using the libraries in other environments.

Depends on the SQLite library. SQLite is available as the package
`libsqlite3-dev` in apt (on Debian-based Linux distributions such as Ubuntu);
search the Internet to find whether your package manager has an equivalent,
or see [the SQLite website](http://sqlite.org/quickstart.html)
for information on using the library in other environments.

Dota is a trademark of Valve Corporation. This non-commercial project is not
affiliated with Valve.

Usage
=====

Getting the program
-------------------

Install the `libboost-all-dev` and `libsqlite3-dev` packages or the equivalents
for your development environment. Ensure you also have `git`, `make`, `python`,
and a C++ compiler (such as `g++`, which in apt is available as part of the
package `build-essential`) installed. Open a terminal in the directory where you
want `heropool` installed, and run:

    git clone https://github.com/lavosprime/heropool.git
    cd heropool
    make

This should compile `heropool`, after which it is ready to use. If the program
does not build on your machine, please
[report the issue](https://github.com/lavosprime/heropool/issues) so I can help
you solve it.

Running the program
-------------------

From the directory where `heropool` was compiled:

- `./heropool`: start in interactive mode to process many commands
- `./heropool <command>`: execute the single given `command`

Commands
--------

- `help`, `--help`, `-h`: show the available commands
- `quit`: quit from interactive mode
- `heroes`: list all heroes
- `heroes <player>`: list the heroes that the given `player` plays
- `players`: list all players currently tracked
- `players <hero>`: list the players who play the given `hero`
- `add <player> <hero>`:  record that the given `player` plays the given `hero`
- `addplayers <hero>`: record several players who play the given `hero` on
  separate lines until a blank line occurs
- `addheroes <player>`: record several heroes that the given `player` plays on
  separate lines until a blank line occurs

Details
=======

`heropool` will create and use a file called `heropool.db` in the directory
where it is run. This is where the hero/player data is stored persistently, so
make sure to always run `heropool` from the same directory and do not try to
modify `heropool.db` yourself, or your data will be lost. `heropool` will
attempt to check whether it was run from its own directory and warn you if it
has not, but this check can probably be fooled. `heropool` may behave
unpredictably if `heropool.db` is corrupted.

Player names must use only letters, numbers, and underscores. Hero names use
only letters; there are no spaces, hyphens, apostrophes, or other special
characters. `heropool` understands several alternate names for many heroes; for
example, for example, you may type "dp" instead of "deathprophet" or "veno"
instead of "venomancer". The complete list of hero names and alternate names is
part of `HeroNames.json`. Hero names and player names are case-insensitive, but
`heropool` will always show them as all-lowercase.

TODO
====

- clean up directory structure
- command parsing
- database operations
