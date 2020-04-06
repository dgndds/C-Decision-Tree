#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionTreeNode.h"
#include <string>

using namespace std;
//template< class int>;

class DecisionTree
{
    public:
        void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
        void train(const string fileName, const int numSamples, const int numFeatures);
        int predict(const bool* data);
        double test(const bool** data, const int* labels, const int numSamples);
        double test(const string fileName, const int numSamples);
        void print();
        int getFeatureCount();
    private:
        DecisionTreeNode* root;
        DecisionTreeNode* leftChild;
        DecisionTreeNode* rightChild;
        int sampleNum = 0;
        int featureNum = 0;
        int featureTypeCount = 0;
        void preorder(DecisionTreeNode* root,const int tabCount);
        DecisionTreeNode* split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedSamples,DecisionTreeNode* node, const int counter,bool usedLabelsArr[]);

};

#endif // DECISIONTREE_H


