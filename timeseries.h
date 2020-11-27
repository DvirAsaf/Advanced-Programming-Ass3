#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringStream
#include "anomaly_detection_util.h"
using namespace std;

class TimeSeries {
private:
//    map<string , vector<float>> allData;
public:
    map<string , vector<float>> allData;
    explicit TimeSeries(const char* CSVfileName)
    {
        this->allData = ConvertToMap(read_csv(CSVfileName));
    }
    vector<pair<string, vector<float>>> read_csv(string filename)const;
    void ReadCols(vector<pair<string, vector<float>>> &result, string &colname, ifstream &myFile,string &line)const;

    ifstream &
    readTextLineByLine(vector<pair<string, vector<float>>> &result, ifstream &myFile, string &line,
                       float val) const;
//    vector<float> getVecByName(vector<pair<string, vector<float>>> cols, string name);
//    bool isNameInVec(vector<pair<string, vector<float>>> cols, string name);
//    vector<pair<string, vector<float>>>getAllData() const;
    map<string , vector<float>> ConvertToMap(vector<pair<string, vector<float>>> three_cols)const;
    bool isVectorNameInMap(string name)const;

    vector<float> getVectorByName(string name) const;
};
#endif /* TIMESERIES_H_ */
