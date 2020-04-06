#ifndef CALCULATE_H
#define CALCULATE_H


double calculateEntropy(const int* classCounts, const int numClasses);
double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
int* findFeatureFrequecy(const int* labels, const bool* usedSamples, const int numSamples, int& labelCount);

#endif // CALCULATE_H
