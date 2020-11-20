//
// Created by Dvir on 11/20/2020.
//

#include <iostream>
#include <vector>
//#include "AnomalyDetector.h"
#include "TimeSeries.h"
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

    return 0;
}