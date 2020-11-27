/**
 * SimpleAnomalyDetector.h
 *
 * @author : Dvir Asaf 313531113.
 */
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
public:
    //constructor
    SimpleAnomalyDetector();
    //destructor
    virtual ~SimpleAnomalyDetector();
    //check which columns have the best correlation update feature1,feature2 and corrlation, and create array of points
    // according to the columns vector, and update lin_reg.
    //according to the line and points array send them to dev and update the struct threshold.
    virtual void learnNormal(const TimeSeries& ts);
    //according to the values of the struct correlatedFeatures, create points are given in time series and check if the
    // threshold of each point is higher the the value of cf.threshold, if yes return anomaly report.
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
};
#endif /* SIMPLEANOMALYDETECTOR_H_ */
