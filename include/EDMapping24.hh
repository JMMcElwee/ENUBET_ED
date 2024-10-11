/* ============ EDMAPPING ============ *
 * Author: J. McElwee                  *
 * Created: 11-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * This was written by L. Halic for    *
 * the 2024 testbeam. Due to linker    *
 * issues on an M1 mac, this had to be *
 * included within the build rather    * 
 * than being linked to.               *
 *                                     *
 * =================================== */
 
#ifndef EDMAPPING24_HH
#define EDMAPPING24_HH

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>

#include "TString.h"

#define LOG_ERROR "\033[31;1m[ERROR]\033[0m "

/*
  This mapping script reads 2 files as input, a text file which maps 
  IC boards to Concentrators (i.e. IC-Concentrator.txt)
  and a text file which maps IC boards to Janus board number (i.e. IC-Janus.txt).                         
                                                                                                        
  Main object is a struct "MapObj" which is returned by "CreateMap" function.
  Once you have this object you can access both "AnodeCoord" (Board and anode
  to Coordinates) and "CoordAnode" (Coordinates to board and anode).

  Please see "ReadMapExample.cc" for how to use this. 

  Author: Leon Halić                                                                                      
*/


// 
inline bool checkFileExistance (const std::string& name) {
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
}

// ----- Format -----
// Data format for reading in the IC-Concentrator.txt                                                   
struct dataFormat{
        int IC = -999;
        std::string Concentratore;
        std::string A;
        std::string R;
        std::string Phi;
        std::string Z;
        int YearOfMapping = -999;
};

struct MapObj
{
        // Maps that will be returned to the user                                                       
        std::map<std::vector<int>, std::vector<int>> AnodeCoord;
        std::map<std::vector<int>, std::vector<int>> CoordAnode;
};


// ----- Create Map -----
// Reads the  file and fills the maps                                                                   
MapObj CreateMap(TString ICConcFile, TString ICJanusFile);

#endif