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
This mapping script reads 2 files as input, a text file which maps IC boards to Concentrators (i.e. IC-\
Concentrator.txt)                                                                                       
and a text file which maps IC boards to Janus board number (i.e. IC-Janus.txt).                         
                                                                                                        
Main object is a struct "MapObj" which is returned by "CreateMap" function. Once you have this object y\
ou can access both "AnodeCoord" (Board and anode to Coordinates) and "CoordAnode" (Coordinates to board\
 and anode).                                                                                            
                                                                                                        
Please see "ReadMapExample.cc" for how to use this.                                                    
                                                                                                        
Author: Leon Halić                                                                                      
*/

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


inline bool checkFileExistance (const std::string& name) {
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
}

// Reads the  file and fills the maps                                                                   
MapObj CreateMap(TString ICConcFile, TString ICJanusFile);

#endif