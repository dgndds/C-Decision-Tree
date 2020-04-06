#include "Calculate.h"
#include <cmath>
#include <iostream>

using namespace std;

double calculateEntropy(const int* classCounts, const int numClasses){
    double result = 0.0;
    int sum = 0;

    for(int i = 0; i < numClasses; i++){
       sum += classCounts[i];
    }

    for(int i = 0; i < numClasses; i++){
        if(sum > 0){
            double div = (double)classCounts[i]/(double)sum;
            if(div > 0)
                result += (div)*(log2(div));
        }

    }

    result = (-1) * result;

    return result;

}

double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId){
    int labelCount = 0;
    int* labelTypes = findFeatureFrequecy(labels,usedSamples,numSamples,labelCount);

    cout << labelCount << endl;
    for(int i = 0; i < labelCount; i++){
        cout << labelTypes[i] << endl;
    }

    cout << "---------------------------------------------------" << endl;
//    int parentArr[3] = {0,0,0};
//    int leftArr[3] = {0,0,0};
//    int rightArr[3] = {0,0,0};
    int parentArr[labelCount] = {0};
    int leftArr[labelCount] = {0};
    int rightArr[labelCount] = {0};

     int observationCount = 0;

    // Calculate label counts of each used label for parent root
//    for(int i = 0; i < numSamples; i++){
//        if(usedSamples[i]){
//            observationCount++;
//            if(labels[i] == 1){
//                parentArr[0] = parentArr[0] + 1;
//            }else if(labels[i] == 2){
//                parentArr[1] = parentArr[1] + 1;
//            }else{
//                parentArr[2] = parentArr[2] + 1;
//            }
//
//        }
//    }

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
//                    if(labels[i] == 1){
//                        leftArr[0] = leftArr[0] + 1;
//                    }else if(labels[i] == 2){
//                        leftArr[1] = leftArr[1] + 1;
//                    }else{
//                        leftArr[2] = leftArr[2] + 1;
//                    }
                    for(int j = 0; j < labelCount; j++){
                        //for(int j = 0; j < numSamples ; j++){
                            if(labels[i] == labelTypes[j]){
                                leftArr[j]++;
                                break;
                            }
                        //}
                    }


                }else{
//                    if(labels[i] == 1){
//                        rightArr[0] = rightArr[0] + 1;
//                    }else if(labels[i] == 2){
//                        rightArr[1] = rightArr[1] + 1;
//                    }else{
//                        rightArr[2] = rightArr[2] + 1;
//                    }
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

    double division = (double)leftSum/(double)observationCount;

    double result = entParent - (((double)leftSum/(double)observationCount)*entLeft + ((double)rightSum/(double)observationCount)*entRight);
    // Return calculated information gain
    return result;
}

int* findFeatureFrequecy(const int* labels, const bool* usedSamples, const int numSamples, int& labelCount){
    int featureTypeCount = 0;

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

    labelCount = featureTypeCount;

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

//    int* labelFreq = new int[featureTypeCount];

//    for(int i = 0; i < featureTypeCount; i++){
//        for(int j = 0; j < numSamples ; j++){
//            if(usedSamples[i] && (labels[j] == uniqueLabels[i]){
//                labelFreq[i]++;
//            }
//        }
//    }

    return uniqueLabels;
}
