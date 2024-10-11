
/* ============ EDMAPPING ============ *
 * Author: J. McElwee                  *
 * Created: 11-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * This was written by L. Halic for    *
 * the 2023 testbeam. Due to linker    *
 * issues on an M1 mac, this had to be *
 * included within the build rather    * 
 * than being linked to.               *
 *                                     *
 * =================================== */


#ifndef EDMAPPING_HH
#define EDMAPPING_HH

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "TString.h"

// ----- Maps -----
std::map<std::vector<int>, std::vector<int>> MappingAnodeCord(TString fileName);
std::map<std::vector<int>, std::vector<int>> MappingCordAnode(TString fileName);

std::map<int, std::vector<int>> MappingDigiCord(TString fileName);


// ----- Output -----
void printMap(std::map<std::vector<int>, std::vector<int>> map);

#endif
