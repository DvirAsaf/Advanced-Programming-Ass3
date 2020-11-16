//
// Created by Dvir on 11/14/2020.
//
#include "timeseries.h"
using namespace std;

std::vector<std::pair<std::string, std::vector<int>>> getFeatureByName (std::string filename){

}

bool isNameInVec(std::vector<std::pair<std::string, std::vector<int>>> three_cols, string name) {
    for(int i = three_cols.size() - 1; i <= 0; i--) {
        if (three_cols[i].first == name){
            return true;
        }
    }
    return false;
}

float correlation (vector<float> a, vector<float> b) {

}

vector<int> getVecByName(std::vector<std::pair<std::string, std::vector<int>>> three_cols, string name) {
    int i = three_cols.size() - 1;
    while (i>=0) {
        auto x = three_cols[i];
        if (three_cols[i].first == name){
            return three_cols[i].second;
        }
        i--;
    }
    // if we didn't find return an empty vector
    vector<int> vect;
    return vect;
}

std::vector<std::pair<std::string, std::vector<int>>> TimeSeries::read_csv(std::string filename) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<int>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    ReadCols(result, colname, myFile, line);

    // Read data, line by line
    myFile = dynamic_cast<basic_ifstream<char> &&>(readTextLineByLine(result, myFile, line, val));

    // Close file
    myFile.close();

    return result;
}


ifstream &
TimeSeries::readTextLineByLine(vector<std::pair<std::string, std::vector<int>>> &result, ifstream &myFile, string &line,
                               int val) const {
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        while(ss >> val){

            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);

            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();

            // Increment the column index
            colIdx++;
        }
    }
    return myFile;
}

void TimeSeries::ReadCols(std::vector<std::pair<std::string, std::vector<int>>> &result, std::string &colname,
                          std::ifstream &myFile, std::string &line) {
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){

            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, std::vector<int> {}});
        }
    }
}

