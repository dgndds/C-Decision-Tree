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
        DecisionTreeNode* split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedLabels,DecisionTreeNode* node, int& counter);
        void train(const string fileName, const int numSamples, const int numFeatures);
//        int predict(const bool*);
//        double test(const bool**, const int*, const int);
//        double test(const string, const int);
        void print();
    private:
        DecisionTreeNode* root;
        DecisionTreeNode* leftChild;
        DecisionTreeNode* rightChild;
        void preorder(DecisionTreeNode* root);

};

#endif // DECISIONTREE_H


