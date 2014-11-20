# Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
# This program is free software provided under the terms of the MIT License.
#
# makeheromap.py: Generates a C++ source file that defines a map from hero
#     aliases/nicknames to "real" hero names. Uses data from HeroNames.json.

import json

def main():
    aliases = json.load(open("./HeroNames.json"));
    for heroname in aliases:
        print('  {"' + heroname + '", "' + heroname + '"},')
        for alias in aliases[heroname]:
            print('  {"' + alias + '", "' + heroname + '"},')

if __name__ == "__main__":
   main()

