#ifndef TIMESERIES_H_
#define TIMESERIES_H_
using namespace std;
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

class TimeSeries {
private:
//    map<string , vector<float>> allData;
public:
    map<string , vector<float>> allData;

    explicit TimeSeries(const char* CSVfileName)
    {
        this->allData = ConvertToMap(read_csv(CSVfileName));
    }
    std::vector<std::pair<std::string, std::vector<float>>> read_csv(string filename);
    void ReadCols(vector<pair<string, vector<float>>> &result, std::string &colname, ifstream &myFile,
                  std::string &line);

    ifstream &
    readTextLineByLine(vector<pair<string, vector<float>>> &result, ifstream &myFile, string &line,
                       float val) const;
    vector<float> getVecByName(vector<pair<string, vector<float>>> cols, string name);
    bool isNameInVec(vector<pair<string, vector<float>>> cols, string name);
    vector<pair<string, vector<float>>>getAllData() const;
    map<string , vector<float>> ConvertToMap(std::vector<std::pair<std::string, std::vector<float>>> three_cols);
};
#endif /* TIMESERIES_H_ */
