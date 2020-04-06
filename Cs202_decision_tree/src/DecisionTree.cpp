#include "DecisionTree.h"
#include "Calculate.h"
#include <iostream>
#include <fstream>

using namespace std;

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures){
    int chosenFeatureIndex = 0;

    bool usedSamplesArr[numSamples];
    bool usedLabelsArr[numFeatures];

    // Define all samples will be used for finding root
    for(int i = 0; i < numSamples; i++){
        usedSamplesArr[i] = true;
    }

    // Define all features are not yet used
    for(int i = 0; i < numFeatures; i++){
        usedLabelsArr[i] = false;
    }

    double maxInfoGain = 0;

    // Find the feature with max information
    for(int i = 0; i < numFeatures; i++){
        double infoGain = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamplesArr,i);

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenFeatureIndex = i;
        }
    }

    // Set root node to feature with max information gain and report this feature is used
    root = new DecisionTreeNode(chosenFeatureIndex);
    usedLabelsArr[chosenFeatureIndex] = true;

    // Define which samples will be used for deciding left child (0 means left node 1 means right node)
    for(int i = 0; i < numSamples; i++){
            if(data[i][chosenFeatureIndex] == 0){
                usedSamplesArr[i] = true;
            }else{
                usedSamplesArr[i] = false;
            }
        }

    int counter = 1;

    // Set left child node of the root which is also a subtree
    root->setLeftChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));

    // Define which samples will be used for deciding left child (0 means left node 1 means right node)
    for(int i = 0; i < numSamples; i++){
        if(data[i][chosenFeatureIndex] == 1){
            usedSamplesArr[i] = true;
        }else{
            usedSamplesArr[i] = false;
        }
    }

    // Reset usedLabelsArr for right child
    for(int i = 0; i < numFeatures; i++){
        usedLabelsArr[i] = false;
    }

    usedLabelsArr[chosenFeatureIndex] = true;
    counter = 1;

    // Set left child node of the root which is also a subtree
    root->setRightChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));
}

DecisionTreeNode* DecisionTree::split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedSamplesArr,DecisionTreeNode* node,const int counter, bool usedLabelsArr[]){
    //Initialize local variables
    double maxInfoGain = 0;
    double infoGain = 0;
    int chosenIndex = 0;
    int oldCounter = counter;

    // Find feature with max information gain using labels not used by ancestors of the node
    for(int i = 0; i < numFeatures; i++){
        if(!usedLabelsArr[i]){
            infoGain = calculateInformationGain(data, labels, numSamples,numFeatures,usedSamplesArr,i);
        }

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenIndex = i;
        }
        infoGain = 0;
    }

    // If information gain is zero or number of features is exceeded, then create a leaf node
    if(maxInfoGain == 0 || counter > numFeatures){

    // Initialize variables and arrays
    int labelCount = 0;

    // Get each class label used in data set along with number of them (for given data set it is {1,2,3} and 3)
    int* uniqeLabels = findFeatureFrequecy(labels, usedSamplesArr, numSamples,labelCount);
    int countLabelsArr[labelCount];

    for(int i = 0; i < labelCount; i++){
        countLabelsArr[i] = 0;
    }

    //Count each label
    for(int i = 0; i < numSamples; i++){
            for(int j = 0; j < labelCount ; j++){
                if(usedSamplesArr[i] && (labels[i] == uniqeLabels[j])){
                    countLabelsArr[j]++;
                }
            }
    }

    int maxLabel = 0;
    int maxValue = 0;

    // Find the class label with greatest count
    for(int i = 0; i < labelCount; i++){
        if(countLabelsArr[i] >= maxValue){
           maxValue =  countLabelsArr[i];
           maxLabel = i ;
        }
    }

    // Make a leaf node with most repeated class label and return it
    DecisionTreeNode* newNode = new DecisionTreeNode(uniqeLabels[maxLabel]);
    newNode->setLeaf(true);
    return newNode;
    }

    // Make node with greatest information gain a decision node
    DecisionTreeNode* newNode = new DecisionTreeNode(chosenIndex);
    usedLabelsArr[chosenIndex] = true;
    oldCounter++;

    // Redefining which labels are going to be used to decide child node
    bool* recursiveUsedSamples = new bool[numSamples];

    for(int i = 0; i < numSamples; i++){
        if(usedSamplesArr[i] && data[i][chosenIndex] == 0){
            recursiveUsedSamples[i] = true;
        }else{
            recursiveUsedSamples[i] = false;
        }
    }

    // Set child of newly created node by using recursion
    newNode->setLeftChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedSamples,newNode, oldCounter, usedLabelsArr));

    // Redefining which labels are going to be used to decide child node
    for(int i = 0; i < numSamples; i++){
        if(usedSamplesArr[i] && data[i][chosenIndex] == 1){
            recursiveUsedSamples[i] = true;
        }else{
            recursiveUsedSamples[i] = false;
        }
    }

    // Set child of newly created node by using recursion
    newNode->setRightChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedSamples,newNode,oldCounter,usedLabelsArr));

    // Return the created node
    return newNode;
}

void DecisionTree::print(){
    preorder(root,0);
}

void DecisionTree::preorder(DecisionTreeNode* node,const int tabCount) {
    int oldTabCount = tabCount;

    if (node != NULL) {
        // Check if current node is leaf
        if(!node->isLeaf()){
            // Print the node
            cout<< node->getItem()<<endl;
            oldTabCount++;

            // Print desired amount of tabs
            for(int i = 0; i < oldTabCount; i++){
                cout << "\t";
            }
        }else{
            // Print the leaf node
            cout<< "class = " << node->getItem()<<endl;

            // Print desired amount of tabs
            for(int i = 0; i < oldTabCount; i++){
                cout << "\t";
            }
        }

    // Print left subtree
    preorder(node->getLeftChildPtr(),oldTabCount);

    // Print right subtree
    preorder(node->getRightChildPtr(),oldTabCount);

    oldTabCount++;

   }
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures){
    // Keep number of features and samples to use later
    featureNum = numFeatures;
    sampleNum = numSamples;

    ifstream dataReader;
    ifstream labelReader;

    dataReader.open(fileName.c_str());
    int condition;

    const bool** data = new const bool* [numSamples];

    // Read samples
    int counter = 0;
    for(int i = 0; i < numSamples; i++){
        bool* line = new bool[numFeatures];

        bool loop = true;

    while((dataReader >> condition) && loop){
            line[counter] = condition;
            counter++;

            if(counter == numFeatures)
                loop = false;
        }

        counter = 0;
        data[i] = line;
    }

    labelReader.open(fileName.c_str());

    int* labels = new int[numSamples];
    counter = 1;

    // Read labels
    while(labelReader >> condition){
        if(counter % (numFeatures + 1) == 0)
            labels[(counter / (numFeatures + 1)) - 1 ] = condition;
        counter++;
    }

    // Find how many different features there are in labels and store it
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

    // Call actual train data
    train(data, labels, numSamples,numFeatures);
}

int DecisionTree::predict(const bool* data){
    DecisionTreeNode* curr = root;

    // Start from root, continue until node is leaf
    while(!(curr->isLeaf())){
        //Decide which child node and iterate
        if(data[curr->getItem()] == 0){
            curr = curr->getLeftChildPtr();
        }else{
            curr = curr->getRightChildPtr();
        }
    }

    return curr->getItem();
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples){
    int correct = 0;

    // Iterate through each sample and evaluate the guess
    for(int i = 0; i < numSamples; i++){
        if(predict(data[i]) == labels[i]){
            correct++;
        }
    }

    // Return the ratio
    return (double)correct/(double)numSamples;
}

double DecisionTree::test(const string fileName, const int numSamples){
    ifstream dataReader;
    ifstream labelReader;

    dataReader.open(fileName.c_str());
    int condition;

    const bool** data = new const bool* [numSamples];

    // Read data
    int counter = 0;
    for(int i = 0; i < numSamples; i++){
        bool* line = new bool[featureNum];

        bool loop = true;

    while((dataReader >> condition) && loop){
            line[counter] = condition;
            counter++;

            if(counter == featureNum)
                loop = false;
        }

        counter = 0;
        data[i] = line;
    }

    labelReader.open(fileName.c_str());

    int* labels = new int[numSamples];

    counter = 1;

    //read labels
    while(labelReader >> condition){
        if(counter % (featureNum + 1) == 0)
            labels[(counter / (featureNum + 1)) - 1 ] = condition;
        counter++;
    }

    // Test the given input and return the result
    return test(data,labels,numSamples);
}
