#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub


}
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    // TODO Auto-generated destructor stub
    //size of how much values in each vector.
    int vectors_size = ts.allData.begin()->second.size();
    float help = 0.0;
    float *vector_ptr_1;
    float *vector_ptr_2;
    string vec_1_name;
    string vec_2_name;
    for (auto col_1 = ts.allData.begin(); col_1 != ts.allData.end(); col_1++) {
        for (auto col_2 = std::next(col_1); col_2 != ts.allData.end(); col_2++) {
            if (col_1->first == col_2->first) {
                continue;
            }
            float *vector_ptr_A = col_1->second.data();
            float *vector_ptr_B = col_2->second.data();
            float pearsonResult = abs(pearson(vector_ptr_A, vector_ptr_B, vectors_size));
            if (pearsonResult > help && pearsonResult > 0.9) {
                //save the ptr's of the best correlation.
                vector_ptr_1 = vector_ptr_A;
                vector_ptr_2 = vector_ptr_B;
                //save the name of the best correlation ptr's.
                vec_1_name = col_1->first;
                vec_2_name = col_2->first;
                //TODO: remove the lina below, its only for febaging.
                help = pearsonResult;
            }
        }
    }
        //make array of points with the best correlation in the map.
        Point* ps[vectors_size];
        for(int i = 0; i < vectors_size; i++) {
            ps[i] = new Point(vector_ptr_1[i], vector_ptr_2[i]);
        }
        //make a line from the array of best correlation points.
        Line l = linear_reg(ps, vectors_size);

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
}