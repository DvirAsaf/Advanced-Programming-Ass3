#include <iostream>
#include <cmath>
#include "anomaly_detection_util.h"

using std::cout;
using std::endl;

float average(float* x, int size) {
    int i = 0;
    float v = 0;
    while (i != size) {
        v += x[i];
        i++;
    }
    return v / size;
}

float squareAverage(float* x, int size) {
    int i = 0;
    float v = 0;
    float f = 0;
    while (i != size) {
        f = pow(x[i], 2);
        v += f;
        i++;
    }
    return v / size;
}

float var(float* x, int size){
    float sqrAvg = squareAverage(x, size);
    float avg = average(x, size);
    avg = pow(avg, 2);
    return sqrAvg - avg;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float covXAvg = average(x, size);
    float covYAvg = average(y, size);
    int i = 0;
    int j;
    float k = 0;
    while (i != size){
    j = (x[i] - covXAvg) * (x[i] - covYAvg);
    k += j;
    i++;
    }
    return k / size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float avg = cov(x, y, size);
    float rootX = average(x, size);
    rootX = sqrtf(rootX);
    float rootY = average(y, size);
    rootY = sqrtf(rootY);
    float root = rootX * rootY;
    return avg / root;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size){
    //insert value to the right float
    float* X = new float [size];
    float* Y = new float [size];
    int i = 0;
    //continue until we end to the last place in the array
    while (i != size){
        X[i] = points[i] -> x;
        Y[i] = points[i] -> y;
        i++;
    }
    //the average of X and Y
    float avgX = average(X, size);
    float avgY = average(Y, size);
    //the equation is : a = cov(x,y) / var(x)
    float a = (cov(X, Y, size) / var(X, size));
    //the equation is : b = avgY - a*avgX
    float b = avgY - (a * avgX);
    //the equation is : Y = a * X +b
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){

}

int main() {
    float x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float y[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    float avg = pearson(x, y, 10);
    cout << avg << endl;
    return 0;

}
