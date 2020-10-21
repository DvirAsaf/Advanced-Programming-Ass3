/**
 * anomaly_detection_util.cpp
 *
 * @author : Dvir Asaf 313531113.
 */

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
    return ((float) v / size);
}

float squareAverage(float* x, int size) {
    int i = 0;
    float v = 0;
    float f = 0;
    while (i != size) {
        f = x[i] * x[i];
        v += f;
        i++;
    }
    return ((float) v / size);
}

float var(float* x, int size){
    float sqrAvg = squareAverage(x, size);
    float uAvg = average(x, size);
    return ((float) sqrAvg - (uAvg * uAvg));
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float xAvg = average(x, size);
    float yAvg = average(y, size);
    int i = 0;
    float j = 0;
    while (i != size){
        j += ((x[i] - xAvg) * (y[i] - yAvg));
        i++;
    }
    return ((float) j / size);
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float avg = cov(x, y, size);
    float rootX = var(x, size);
    rootX = sqrtf(rootX);
    float rootY = var(y, size);
    rootY = sqrtf(rootY);
    float root = rootX * rootY;
    return ((float) avg / root);
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size){
    //insert value to the right float
    float* x = new float [size];
    float* y = new float [size];
    int i = 0;
    //continue until we end to the last place in the array
    while (i != size){
        x[i] = points[i] -> x;
        y[i] = points[i] -> y;
        i++;
    }
    //the average of X and Y
    float avgX = average(x, size);
    float avgY = average(y, size);
    //the equation is : a = cov(x,y) / var(x)
    float a = (cov(x, y, size) / var(x, size));
    //the equation is : b = avgY - a*avgX
    float b = avgY - (a * avgX);
    //the equation is : Y = a * X +b
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    //the equation is : F(x) -- Y = a * X + b -> a * X + b - f(x) -- Y
    return std::abs((l.a * p.x + l.b) - p.y);
}