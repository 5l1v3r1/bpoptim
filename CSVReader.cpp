
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>
#include <iostream>


#include "CSVReader/CSVReader.h"

CSVReader::CSVReader(std::string filename, std::string delim=";") :
			fileName(filename), delimeter(delim)
	{ return; }

//CSVReader::CSVReader (const CSVReader& orig) { }

CSVReader::~CSVReader () {return; }

std::vector<std::vector<std::string> > CSVReader::getData()
{
	std::ifstream file(fileName);
 
	std::vector<std::vector<std::string> > dataList;
 
	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
//                std::cout << vec.size () << std::endl;
		dataList.push_back(vec);
	}
	// Close the File
	file.close();
 
	return dataList;
}