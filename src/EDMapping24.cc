#include "EDMapping24.hh"

// Reads the files and fills the maps
MapObj CreateMap(TString ICConcFile, TString ICJanusFile){

	MapObj maps;

	if(!checkFileExistance(std::string(ICConcFile))){
		std::cout<<LOG_ERROR<<"IC-Concentrator Mapping text file does not exist! Exiting program."<<std::endl;
		exit(0);
	}

	if(!checkFileExistance(std::string(ICJanusFile))){
		std::cout<<LOG_ERROR<< "IC-Janus Mapping text file does not exist! Exiting program."<<std::endl;
		exit(0);
	}

	std::ifstream ICConcInfile(ICConcFile);
	std::ifstream ICJanusInfile(ICJanusFile);

	// Skipping the first row in the txt file
	ICConcInfile.ignore(1000, '\n');
	ICJanusInfile.ignore(1000, '\n');

	dataFormat ICConcData;
	std::string IC;
	std::string Janus;
	std::string IPAddress;
	std::string ChainID;

	std::map<int,int> ICJanusMap;

	// Reading the IC-Janus.txt
	while(ICJanusInfile >> IC >> Janus >> IPAddress >> ChainID){

		// Checks if the input is  a number as the IC boards not used are marked with and "X" or "/" or "-"
		if(!isdigit(*Janus.data())) continue;

		ICJanusMap[std::stoi(IC)] = std::stoi(Janus);
	}

	// Reading the IC-Concentrator.txt
	while (ICConcInfile >> ICConcData.IC >> ICConcData.Concentratore >> ICConcData.A >> ICConcData.R >> ICConcData.Phi >> ICConcData.Z >> ICConcData.YearOfMapping){

		std::vector<int> coordinates;
		std::vector<int> boardNAnode;

		if (ICJanusMap.find(ICConcData.IC) == ICJanusMap.end()) continue;

		if (ICConcData.R == "-" || ICConcData.Phi == "-" || ICConcData.Z == "-")
			continue;
		else if (ICConcData.R == "0d")
			coordinates.push_back(0);
		else if (ICConcData.R == "0u")
			coordinates.push_back(1);
		else
			coordinates.push_back(std::stoi(ICConcData.R)+1);

		coordinates.push_back(std::stoi(ICConcData.Phi));

		coordinates.push_back(std::stoi(ICConcData.Z));

		boardNAnode.push_back(ICJanusMap.at(ICConcData.IC));

		boardNAnode.push_back(std::stoi(ICConcData.A));

		maps.AnodeCoord[boardNAnode] = coordinates;
		maps.CoordAnode[coordinates] = boardNAnode;

		boardNAnode.clear();
		coordinates.clear();

	}

	ICConcInfile.close();
	ICJanusInfile.close();
	return maps;
}