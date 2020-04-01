#ifndef CALCULATE_H
#define CALCULATE_H


double calculateEntropy(const int* classCounts, const int numClasses);
double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);

#endif // CALCULATE_H
