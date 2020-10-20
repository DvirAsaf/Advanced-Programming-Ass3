#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

float average(float* x, int size) {
    int i = 0;
    float v = 0;
    while (i != size) {
        v = v + x[i];
        i++;
    }
    return v / size;
}

float bla2(float* x, int size) {
    int i = 0;
    float v = 0;
    float f = 0;
    while (i != size) {
        f = x[i] * x[i];
        v = v + f;
        i++;
    }
    return v / size;
}

float var(float* x, int size){
    float z = bla2(x, size);
    float w = average(x, size);
    w = w * w;
    return z - w;
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
    k = k + j;
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

int main() {
    float x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float y[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    float avg = pearson(x, y, 10);
    cout << avg << endl;
    return 0;

}
