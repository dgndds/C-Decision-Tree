#include "Calculate.h"
#include <cmath>

using namespace std;

double calculateEntropy(const int* classCounts, const int numClasses){
    double result = 0.0;
    int sum = 0;

    for(int i = 0; i < numClasses; i++){
       sum += classCounts[i];
    }

    for(int i = 0; i < numClasses; i++){
        double div = (double)classCounts[i]/(double)sum;
        if(div > 0){
            result += (div)*(log2(div));
        }

    }

    result = (-1) * result;

    return result;
}
