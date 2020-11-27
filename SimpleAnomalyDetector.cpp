/**
 * SimpleAnomalyDetector.h
 *
 * @author : Dvir Asaf 313531113.
 */
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub


}
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    // TODO Auto-generated destructor stub
    map<string, vector<float>> time = ts.allData;
    //size of how much values in each vector.
    int vectors_size = time.begin()->second.size();
    Point* ps[vectors_size];
    float *vector_ptr_1;
    float *vector_ptr_2;
    bool correlationHigher = false;
    for (auto col_1 = time.begin(); col_1 != time.end(); col_1++) {
        struct correlatedFeatures ct;
        ct.corrlation = 0.0;
        ct.threshold = 0.0;
        for (auto col_2 = next(col_1); col_2 != time.end(); col_2++) {
            if (col_1->first == col_2->first) {
                continue;
            }
            float* vector_ptr_A = col_1->second.data();
            float* vector_ptr_B = col_2->second.data();
            float pearsonResult = abs(pearson(vector_ptr_A, vector_ptr_B, vectors_size));
            if (pearsonResult > ct.corrlation && pearsonResult > 0.9) {
                //save the ptr of the best correlation.
                vector_ptr_1 = vector_ptr_A;
                vector_ptr_2 = vector_ptr_B;
                //save the name of the best correlation ptr.
                ct.feature1 = col_1->first;
                ct.feature2 = col_2->first;
                ct.corrlation = pearsonResult;
                correlationHigher = true;
            }
        }
        if (correlationHigher) {
        //make array of points with the best correlation in the map.
        for(int i = 0; i < vectors_size ; i++) {
            ps[i] = new Point(vector_ptr_1[i], vector_ptr_2[i]);
        }
        //make a line from the array of best correlation points.
        ct.lin_reg = linear_reg(ps, vectors_size);
        for (int j = 0; j < vectors_size ; j++) {
            float helpThreshold = dev(*ps[j], ct.lin_reg);
            if (ct.threshold < helpThreshold) {
                ct.threshold = helpThreshold;
            }
        }
        ct.threshold = ct.threshold * 1.1;
        cf.push_back(ct);
            correlationHigher = false;
    }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // TODO Auto-generated destructor stub
    vector<AnomalyReport> vector_Anomaly_Report;
    string description;
    long timeStep;
    map<string, vector<float>> map = ts.allData;
    int vector_size = ts.allData.begin()->second.size();
    for (int k = 0; k < (vector_size - 1); k++) {
        for (auto x = cf.begin(); x != cf.end(); x++){
          Point p(ts.getVectorByName(cf.data()->feature1).at(k),
            ts.getVectorByName(cf.data()->feature2).at(k));
          if (dev(p,cf.data()->lin_reg) > cf.data()->threshold){
              description = cf.data()->feature1 + "-" + cf.data()->feature2;
              timeStep = k + 1;
              AnomalyReport c = { description, timeStep};
              vector_Anomaly_Report.push_back(c);
          }
        }
    }
    return vector_Anomaly_Report;
}













////    int size_of_vectors = ts.allData.begin()->first.size();
//    int vectors_size = ts.allData.begin()->second.size();
////    vector<float>[size_of_vectors] vectors_array;
//    float* vector_1;
//    float* vector_2;
//    float pearsonResult;
//    float help = 0.0;
//    for(unsigned int i = ts.allData.size() - 1; i <= 0; i--) {
//        vector<float> vector_A = ts.allData.begin()->second;
//        vector_1 = vector_A.data();
//        //i am down the value of i once.
//        vector<float> vector_B = ts.allData.begin()->second;
////        vectors_array[--i] = ts.allData.begin()->second;
//        vector_2 = vector_B.data();
//        pearsonResult = abs(pearson(vector_1,vector_2,vectors_size));
//        if(pearsonResult > help) {
//            help = pearsonResult;
//        }
//    }