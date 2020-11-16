#ifndef TIMESERIES_H_
#define TIMESERIES_H_
using namespace std;
#include <vector>
#include <string>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

class TimeSeries {
private:
    vector<pair<string, vector<int>>> allData;
public:
    TimeSeries(const char* CSVfileName){
        allData = read_csv(CSVfileName);
    }
    std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename);
    void ReadCols(std::vector<std::pair<std::string, std::vector<int>>> &result, std::string &colname, std::ifstream &myFile,
                  std::string &line);

    ifstream &
    readTextLineByLine(vector<std::pair<std::string, std::vector<int>>> &result, ifstream &myFile, string &line,
                       int val) const;
};
#endif /* TIMESERIES_H_ */
