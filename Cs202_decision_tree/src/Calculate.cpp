#include "Calculate.h"
#include <cmath>
#include <iostream>

using namespace std;

double calculateEntropy(const int* classCounts, const int numClasses){
    double result = 0.0;
    int sum = 0;

    // Find total number of classes
    for(int i = 0; i < numClasses; i++){
       sum += classCounts[i];
    }

    // Find entrophy of the classes
    for(int i = 0; i < numClasses; i++){
        if(sum > 0){
            double div = (double)classCounts[i]/(double)sum;
            if(div > 0)
                result += (div)*(log2(div));
        }
    }

    // Return the negative of the calculated result
    result = (-1) * result;
    return result;

}

double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId){
    //Initialize values and arrays
    int labelCount = 0;
    int* labelTypes = findFeatureFrequecy(labels,usedSamples,numSamples,labelCount);
    int parentArr[labelCount];
    int leftArr[labelCount];
    int rightArr[labelCount];

    for(int i = 0; i < labelCount; i++){
            parentArr[i] = 0;
            leftArr[i] = 0;
            rightArr[i] = 0;
    }

    int observationCount = 0;

    // Find class numbers of the parrent node and number of total observations
    for(int i = 0; i < numSamples; i++){
        for(int j = 0; j < labelCount; j++){
            if(usedSamples[i] && (labels[i] == labelTypes[j])){
                observationCount++;
                parentArr[j]++;
            }
        }
    }


    // Calculate label counts of each used label for child roots
    for(int i = 0; i < numSamples; i++){
        if(usedSamples[i]){
            if(data[i][featureId] == 0 ){
                for(int j = 0; j < labelCount; j++){
                    if(labels[i] == labelTypes[j]){
                        leftArr[j]++;
                        break;
                    }
                }
        }else{
            for(int j = 0; j < labelCount; j++){
                if(labels[i] == labelTypes[j]){
                    rightArr[j]++;
                    break;
                }
            }
          }
        }
    }

    // Calculate sum of left node subset
    int leftSum = 0;

    for(int i = 0; i < 3; i++){
        leftSum += leftArr[i];
    }
    // Calculate sum of right node subset
    int rightSum = 0;

    for(int i = 0; i < 3; i++){
        rightSum += rightArr[i];
    }

    // Calculate entropy of each used label for parent and child roots
    double entParent = calculateEntropy(parentArr,labelCount);
    double entLeft = calculateEntropy(leftArr,labelCount);
    double entRight = calculateEntropy(rightArr,labelCount);

    // Take the weighted average of entrophies of child nodes and apply the information gain formula
    double result = entParent - (((double)leftSum/(double)observationCount)*entLeft + ((double)rightSum/(double)observationCount)*entRight);

    // Return calculated information gain
    return result;
}

int* findFeatureFrequecy(const int* labels, const bool* usedSamples, const int numSamples, int& labelCount){
    int featureTypeCount = 0;

    // Find number of features defined in the array
    for(int i = 0; i < numSamples; i++){
        int j = 0;
        for(j = 0; j < i; j++){
            if(labels[i] == labels[j]){
                break;
            }
        }

        if(i == j){
            featureTypeCount++;
        }
    }

    // Pass by reference to caller function
    labelCount = featureTypeCount;

    // Find each unique feature
    int* uniqueLabels = new int[featureTypeCount];
    int uniqueIndex = 0;

    for(int i = 0; i < numSamples; i++){
        int j = 0;
        for(j = 0; j < i; j++){
            if(labels[i] == labels[j]){
                break;
            }
        }

        if(i == j){
            uniqueLabels[uniqueIndex] = labels[i];
            uniqueIndex++;
        }

        if(uniqueIndex == featureTypeCount){
            break;
        }
    }

    // Return array of unique features
    return uniqueLabels;
}
