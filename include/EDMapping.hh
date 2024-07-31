
#ifndef EDMAPPING_HH
#define EDMAPPING_HH

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "TString.h"

std::map<std::vector<int>, std::vector<int>> MappingAnodeCord(TString fileName);

std::map<std::vector<int>, std::vector<int>> MappingCordAnode(TString fileName);

std::map<int, std::vector<int>> MappingDigiCord(TString fileName);

void printMap(std::map<std::vector<int>, std::vector<int>> map);


#endif
