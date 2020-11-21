//
// Created by Dvir on 11/20/2020.
//
#include "anomaly_detection_util.h"
#include <iostream>
#include <vector>
//#include "AnomalyDetector.h"
#include "TimeSeries.h"
#include "SimpleAnomalyDetector.h"
//#include "SimpleAnomalyDetector.h"
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
using namespace std;

int main() {
    TimeSeries ts("trainFile1.csv");
    auto map = ts.allData;

    for( auto x: map){
        cout<< x.first<<endl;
        cout<< x.second[0]<<endl;
    }
    for( auto x: ts.getVectorByName("A")){
        cout<< x<<endl;
    }
//    SimpleAnomalyDetector ad;
//    ad.learnNormal(ts);
//    int size_of_vectors = ts.allData.size();
    int vectors_size = ts.allData.begin()->second.size();
    float help = 0.0;
    float* vector_ptr_1;
    float* vector_ptr_2;
    string vec_1_name;
    string vec_2_name;
    for (auto col_1 = ts.allData.begin(); col_1 != ts.allData.end(); col_1++) {
        for( auto col_2 = std::next(col_1); col_2 != ts.allData.end(); col_2++){
            if(col_1->first == col_2->first){
                continue;
            }
            float* vector_ptr_A = col_1->second.data();
            float* vector_ptr_B = col_2->second.data();
            float pearsonResult = abs(pearson(vector_ptr_A,vector_ptr_B,vectors_size));
            if(pearsonResult > help && pearsonResult > 0.9) {
                vector_ptr_1 = vector_ptr_A;
                vector_ptr_2 = vector_ptr_B;
                vec_1_name = col_1->first;
                vec_2_name = col_2->first;
                help = pearsonResult;
            }
        }
    }

    vector<float> vectors_array;

        //for statement to print values using array
        size_t i = 0;
        for( ; i < vectors_size; ++i ){
            printf("%f\n", vector_ptr_1[i]);
        }
    i = 0;
    for( ; i < vectors_size; ++i ){
        printf("%f\n", vector_ptr_2[i]);
    }

    float* vector_1;
    float* vector_2;
//    float pearsonResult = 0.0;
    for(auto col_1 : ts.allData) {
        for(auto col_2 : ts.allData) {
            if(col_1.first == col_2.first){
                continue;
            }
            float* vector_ptr_A = col_1.second.data();
            float* vector_ptr_B = col_2.second.data();
            float pearsonResult = pearson(vector_ptr_A,vector_ptr_B,vectors_size);
            if(pearsonResult > help && pearsonResult > 0.9) {
                float* vector_ptr_1 = vector_ptr_A;
                float* vector_ptr_2 = vector_ptr_B;
                help = pearsonResult;
            }

        }
    }
//    for(unsigned int i = ts.allData.size() - 1; i >= 0; i--) {
//
//        vector<float> vector_A = ts.allData.begin()->second;
//
//        vector_1 = vector_A.data();
//        //i am down the value of i once.
//        vector<float> vector_B = ts.allData.begin()->second;
////        vectors_array[--i] = ts.allData.begin()->second;
//        vector_2 = vector_B.data();
//        float pearsonResult = pearson(vector_1,vector_2,vectors_size);
//        if(pearsonResult > help && pearsonResult > 0.9) {
//            help = pearsonResult;
//        }
//        cout<<pearsonResult<<endl;
//    }
    return 0;
}