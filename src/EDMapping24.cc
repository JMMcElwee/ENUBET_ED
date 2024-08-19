#include "EDMapping24.hh"

MapObj CreateMap(TString ICConcFile, TString ICJanusFile)
{
	MapObj maps;

        if(!checkFileExistance(std::string(ICConcFile))){
                std::cout<<LOG_ERROR<<"IC-Concentrator Mapping text file does not exist! Exiting progra\
m."<<std::endl;
                exit(0);
        }

        if(!checkFileExistance(std::string(ICJanusFile))){
                std::cout<<LOG_ERROR<< "IC-Janus Mapping text file does not exist! Exiting program."<<s\
td::endl;
                exit(0);
        }

        std::ifstream ICConcInfile(ICConcFile);
        std::ifstream ICJanusInfile(ICJanusFile);

        // Skipping the first row in the txt file                                                       
        ICConcInfile.ignore(1000, '\n');
        ICJanusInfile.ignore(1000, '\n');

        dataFormat ICConcData;
        int IC = -1;
        int Janus = -1;

        std::map<int,int> ICJanusMap;

        // Reading the IC-Janus.txt                                                                     
        while(ICJanusInfile >> IC >> Janus){
                ICJanusMap[IC] = Janus;
        }

        // Reading the IC-Concentrator.txt                                                              
        while (ICConcInfile >> ICConcData.IC >> ICConcData.Concentratore >> ICConcData.A >> ICConcData.\
R >> ICConcData.Phi >> ICConcData.Z >> ICConcData.YearOfMapping){

                std::vector<int> coordinates;
                std::vector<int> boardNAnode;

                int i = -999;
                if (ICConcData.R == "-" || ICConcData.Phi == "-" || ICConcData.Z == "-")
                        continue;
                else if (ICConcData.R == "0d")
                        i = -1;
                else if (ICConcData.R == "0u")
                        i = 0;
                else
                        std::istringstream(ICConcData.R) >> i;

                coordinates.push_back(i+1);

                std::istringstream(ICConcData.Phi) >> i;

                coordinates.push_back(i);

                std::istringstream(ICConcData.Z) >> i;

                coordinates.push_back(i);

                i = ICJanusMap.at(ICConcData.IC);

                boardNAnode.push_back(i);

                std::istringstream(ICConcData.A) >> i;

                boardNAnode.push_back(i);

                maps.AnodeCoord[boardNAnode] = coordinates;
                maps.CoordAnode[coordinates] = boardNAnode;

                boardNAnode.clear();
                coordinates.clear();

        }

        ICConcInfile.close();
        ICJanusInfile.close();
        return maps;
}