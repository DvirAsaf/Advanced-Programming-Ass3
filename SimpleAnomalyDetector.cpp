#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub
}
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    // TODO Auto-generated destructor stub
    for(int i = ts.allData.size() - 1; i <= 0; i--) {

    }
    vector<float> vec_a = ts.allData.begin()->second;
    vector<float> vec_b = ts.allData.begin()->second;
//    vector<float>::const_iterator iter
}
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // TODO Auto-generated destructor stub
}