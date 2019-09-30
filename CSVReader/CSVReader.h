
#ifndef CSVREADER_H
#define CSVREADER_H

class CSVReader {

    std::string fileName;
    std::string delimeter;
 
public:
    CSVReader(std::string, std::string);

    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string> > getData();
        
    //CSVReader(const CSVReader& orig);
    virtual ~CSVReader();
};

#endif /* CSVREADER_H */