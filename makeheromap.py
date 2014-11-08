# Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
# This program is free software provided under the terms of the MIT License.
#
# makeheromap.py: Generates a C++ source file that defines a map from hero
#     aliases/nicknames to "real" hero names.

def main():
    aliases = get_aliases()
    print("""\
#include "HeroData.h"

#include <cassert>
#include <map>
#include <string>

static const std::map<std::string, std::string> heroesByAlias = {""");
    for heroname in aliases:
        print('  {"' + heroname + '", "' + heroname + '"},')
        for alias in aliases[heroname]:
            print('  {"' + alias + '", "' + heroname + '"},')
    print("""\
};

const bool HeroExistsForAlias(const std::string& alias) {
  return heroesByAlias.count(alias) == 1;
}

const std::string& GetHeroByAlias(const std::string& alias) {
  assert(HeroExistsForAlias(alias);
  return heroesByAlias[alias];
}""");

def get_aliases():
    return {
        'abaddon': [
        ],
        'abyssalunderlord': [
        ],
        'alchemist': [
            'alch',
        ],
        'ancientapparition': [
            'aa',
        ],
        'antimage': [
            'am',
            'anti',
        ],
        'arcwarden': [
        ],
        'axe': [
        ],
        'bane': [
        ],
        'batrider': [
            'bat',
        ],
        'beastmaster': [
        ],
        'bloodseeker': [
            'blood',
            'bloodcyka',
        ],
        'bountyhunter': [
            'bounty',
        ],
        'brewmaster': [
            'brew',
            'panda',
        ],
        'bristleback': [
            'bristle',
        ],
        'broodmother': [
            'brood',
            'bm',
        ],
        'centaurwarrunner': [
            'centaur',
            'cent',
        ],
        'chaosknight': [
            'ck',
        ],
        'chen': [
        ],
        'clinkz': [
        ],
        'clockwerk': [
            'clock',
        ],
        'crystalmaiden': [
            'cm',
        ],
        'darkseer': [
        ],
        'dazzle': [
        ],
        'deathprophet': [
            'dp',
            'krob',
            'krobelus',
        ],
        'disruptor': [
        ],
        'doom': [
            'lucifer',
            'doombringer',
        ],
        'dragonknight': [
            'dk',
            'davion',
        ],
        'drowranger': [
            'drow',
            'traxex',
        ],
        'earthspirit': [
            'kaolin',
        ],
        'earthshaker': [
            'shaker',
        ],
        'eldertitan': [
            'et',
        ],
        'emberspirit': [
            'xin',
            'ember',
        ],
        'enchantress': [
            'ench',
        ],
        'enigma': [
        ],
        'facelessvoid': [
            'faceless',
            'void',
            'darkterror',
        ],
        'goblintechies': [
            'techies',
        ],
        'gyrocopter': [
            'gyro',
        ],
        'huskar': [
            'husk',
        ],
        'invoker': [
            'voker',
            'carl',
        ],
        'io': [
            'wisp',
        ],
        'jakiro': [
            'jak',
            'thd',
        ],
        'juggernaut': [
            'jugg',
            'jugger',
            'yurnero',
        ],
        'keeperofthelight': [
            'kotl',
            'ezalor',
        ],
        'kunkka': [
        ],
        'legioncommander': [
            'legion',
            'lc',
        ],
        'leshrac': [
            'lesh',
        ],
        'lich': [
        ],
        'lifestealer': [
            'naix',
        ],
        'lina': [
        ],
        'lion': [
        ],
        'lonedruid': [
            'ld',
            'sylla',
            'syllabear',
        ],
        'luna': [
        ],
        'lycan': [
            'lycanthrope',
        ],
        'magnus': [
            'mag',
        ],
        'medusa': [
            'dusa',
        ],
        'meepo': [
        ],
        'mirana': [
            'potm',
        ],
        'morphling': [
            'morph',
        ],
        'nagasiren': [
            'naga',
        ],
        'naturesprophet': [
            'prophet',
            'np',
            'furion',
        ],
        'necrophos': [
            'necrolyte',
            'necro',
        ],
        'nightstalker': [
            'ns',
        ],
        'nyxassassin': [
            'nyx',
        ],
        'ogremagi': [
            'ogre',
        ],
        'omniknight': [
            'omni',
        ],
        'oracle': [
        ],
        'outworlddevourer': [
            'od',
        ],
        'phantomassassin': [
            'pa',
            'mortred',
        ],
        'phantomlancer': [
            'pl',
            'cancer',
        ],
        'phoenix': [
        ],
        'puck': [
        ],
        'pudge': [
            'butcher',
        ],
        'pugna': [
        ],
        'queenofpain': [
            'qop',
            'akasha',
        ],
        'razor': [
        ],
        'riki': [
            'rikimaru',
            'sa',
        ],
        'rubick': [
        ],
        'sandking': [
            'sk',
        ],
        'shadowdemon': [
            'sd',
        ],
        'shadowfiend': [
            'sf',
            'nevermore',
        ],
        'shadowshaman': [
            'shaman',
            'rhasta',
        ],
        'silencer': [
        ],
        'skywrathmage': [
            'skywrath',
            'sm',
            'swm',
            'dragonus',
            'drag',
        ],
        'slardar': [
        ],
        'slark': [
        ],
        'sniper': [
        ],
        'spectre': [
            'spec',
        ],
        'spiritbreaker': [
            'sb',
            'spacecow',
        ],
        'stormspirit': [
            'raijin',
            'storm',
        ],
        'sven': [
        ],
        'templarassassin': [
            'ta',
            'lanaya',
        ],
        'terrorblade': [
            'tb',
        ],
        'tidehunter': [
            'tide',
        ],
        'timbersaw': [
            'timber',
        ],
        'tinker': [
        ],
        'tiny': [
            'tony',
        ],
        'treantprotector': [
            'treant',
        ],
        'trollwarlord': [
            'troll',
        ],
        'tusk': [
        ],
        'undying': [
            'dirge',
        ],
        'ursa': [
        ],
        'vengefulspirit': [
            'venge',
        ],
        'venomancer': [
            'veno',
        ],
        'viper': [
        ],
        'visage': [
        ],
        'warlock': [
        ],
        'weaver': [
        ],
        'windranger': [
            'windrunner',
            'wr',
            'wind',
        ],
        'winterwyvern': [
            'wyvern',
            'ww',
        ],
        'witchdoctor': [
            'wd',
        ],
        'wraithking': [
            'wk',
            'skeletonking',
            'leoric',
        ],
        'zeus': [
        ]
    }

if __name__ == "__main__":
   main()

