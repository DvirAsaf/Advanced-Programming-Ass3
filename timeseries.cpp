//
// Created by Dvir on 11/14/2020.
//
#include "timeseries.h"
using namespace std;

vector<pair<string, vector<float>>> TimeSeries::read_csv(string filename) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>
    // Create a vector of <string, int vector> pairs to store the result
    vector<pair<string, vector<float>>> result;
    // Create an input filestream
    ifstream myFile(filename);
    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");
    // Helper vars
    string line, colname;
    float val = 0;
    // Read the column names
    ReadCols(result, colname, myFile, line);
    // Read data, line by line
    myFile = dynamic_cast<basic_ifstream<char> &&>(readTextLineByLine(result, myFile, line, val));
    // Close file
    myFile.close();
    return result;
}

ifstream &
TimeSeries::readTextLineByLine(vector<pair<string, vector<float>>> &result, ifstream &myFile, string &line,
                               float val) const {
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

void TimeSeries::ReadCols(vector<pair<string, vector<float>>> &result, string &colname, ifstream &myFile, string &line) {
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);
        // Create a stringstream from line
        stringstream ss(line);
        // Extract each column name
        while(getline(ss, colname, ',')){
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<float> {}});
        }
    }
}

//vector<pair<string, vector<float>>> TimeSeries::getAllData() const{
//    return this->allData;
//}

//vector<float> TimeSeries::getVecByName(vector<pair<string, vector<float>>> cols, string name){
//    while(isNameInVec(cols, name)) {
//        int i = cols.size() - 1;
//        while (i >= 0) {
//            auto x = cols[i];
//            if (cols[i].first == name) {
//                return cols[i].second;
//            }
//            i--;
//        }
//    }
//    // if we didn't find return an empty vector
//    return {};
//    }
//}

//bool TimeSeries::isNameInVec(vector<pair<string, vector<float>>> cols, string name) {
//    for(int i = cols.size() - 1; i <= 0; i--) {
//        if (cols[i].first == name){
//            return true;
//        }
//    }
//    return false;
//}

map<string , vector<float>> TimeSeries::ConvertToMap(vector<pair<string, vector<float>>> three_cols){
    map<string , vector<float>> map;
    for (auto  &x : three_cols){
        string col_name = x.first;
        auto vec = x.second;
        map.insert({col_name, vec});
    }
    return map;
}

bool TimeSeries::isVectorNameInMap(string name) const{
    map<string, vector<float>>::iterator it;
    auto x = this->allData.find(name);
    if (it == this->allData.end()) {
        return false;
    }
    return true;
}

vector<float> TimeSeries::getVectorByName(string name) const{
    if (isVectorNameInMap(name)) {
        auto x = this->allData.find(name);
        return x->second;
    }
    return {};
}
