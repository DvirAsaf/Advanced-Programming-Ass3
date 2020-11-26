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
    struct correlatedFeatures ct;
    //size of how much values in each vector.
    int vectors_size = time.begin()->second.size();
    ct.corrlation = 0.0;
    float *vector_ptr_1;
    float *vector_ptr_2;
    for (auto col_1 = time.begin(); col_1 != time.end(); col_1++) {
        for (auto col_2 = next(col_1); col_2 != time.end(); col_2++) {
            if (col_1->first == col_2->first) {
                continue;
            }
            float* vector_ptr_A = col_1->second.data();
            float* vector_ptr_B = col_2->second.data();
            float pearsonResult = abs(pearson(vector_ptr_A, vector_ptr_B, vectors_size));
            if (pearsonResult > ct.corrlation && pearsonResult > 0.9) {
                //save the ptr's of the best correlation.
                vector_ptr_1 = vector_ptr_A;
                vector_ptr_2 = vector_ptr_B;
                //save the name of the best correlation ptr's.
                ct.feature1 = col_1->first;
                ct.feature2 = col_2->first;
                ct.corrlation = pearsonResult;
            }
            //make array of points with the best correlation in the map.
            Point* ps[vectors_size];
            for(int i = 0; i < vectors_size - 1; i++) {
                ps[i] = new Point(vector_ptr_1[i], vector_ptr_2[i]);
            }
            //make a line from the array of best correlation points.
            ct.lin_reg = linear_reg(ps, vectors_size);
            for (int j = 0; j <vectors_size - 1 ; j++) {
                float helpConst = 0.0;
                float helpThreshold = dev(*ps[j], ct.lin_reg);
                if(helpConst < helpThreshold) {
                    ct.threshold = helpThreshold;
                }
            }
        }
    }
    cf.push_back(ct);
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
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // TODO Auto-generated destructor stub
    vector<AnomalyReport> vector_Anomaly_Report;
    string description;
    long timeStep;
    map<string, vector<float>> map = ts.allData;
    int vector_size = ts.allData.begin()->second.size();
    for (int i = 0; i < vector_size; i++) {
        for (auto x = cf.begin(); x != cf.end(); x++){
//            if(col_1 == cf.data()->feature1 && col_2 == cf.data()->feature2)
          Point p(ts.getVectorByName(cf.data()->feature1).at(i),
            ts.getVectorByName(cf.data()->feature2).at(i));
          if (dev(p,cf.data()->lin_reg) > cf.data()->threshold){
              description = cf.data()->feature1+ "-" + cf.data()->feature2;
              timeStep = i + 1;
              AnomalyReport c = { description, timeStep};
              vector_Anomaly_Report.push_back(c);
          }
        }
//        return vector_Anomaly_Report(AnomalyReport(description, timeStep));
        return vector_Anomaly_Report;
    }
}
