#include "DecisionTree.h"
#include "Calculate.h"
#include <iostream>
#include <fstream>

using namespace std;

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures){
    //DecisionTreeNode* curr = root;
    //int* featureStatus = new int[numFeatures];
    int chosenFeatureIndex = 0;


    bool usedSamplesArr[numSamples];

    for(int i = 0; i < numSamples; i++){
        usedSamplesArr[i] = true;
    }

    double maxInfoGain = 0;

    for(int i = 0; i < numFeatures; i++){
        double infoGain = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamplesArr,i);

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenFeatureIndex = i;
        }
    }

    root = new DecisionTreeNode(chosenFeatureIndex);
    //usedLabels[chosenFeatureIndex] = true;
//    int rootItem = root ->getItem();
  //  int currItem = curr ->getItem();
bool* usedLabels = new bool[numSamples];

for(int i = 0; i < numSamples; i++){
        if(data[i][chosenFeatureIndex] == 0){
            usedLabels[i] = true;
        }else{
            usedLabels[i] = false;
        }
    }

    int counter = 1;
root->setLeftChildPtr(split(data, labels,numSamples, numFeatures,usedLabels,root,counter));

for(int i = 0; i < numSamples; i++){
        //cout << i << "deki sayı " << data[i][4] << endl;

        if(data[i][chosenFeatureIndex] == 0){
            usedLabels[i] = true;
        }else{
            usedLabels[i] = false;
        }
}

root->setRightChildPtr(split(data, labels,numSamples, numFeatures,usedLabels,root,counter));
}

DecisionTreeNode* DecisionTree::split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedLabels,DecisionTreeNode* node,int& counter){
    double maxInfoGain = 0;
    double infoGain = 0;
    int chosenIndex = 0;

    if(counter == numFeatures){
        return NULL;
    }

    for(int i = 0; i < numSamples; i++){
        if(usedLabels[i]){
            infoGain = calculateInformationGain(data, labels, numSamples,numFeatures,usedLabels,i);
        }

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenIndex = i;
        }
    }

    if(maxInfoGain == 1){
        DecisionTreeNode* newNode = new DecisionTreeNode(labels[chosenIndex]);
        return newNode;
    }

    DecisionTreeNode* newNode = new DecisionTreeNode(chosenIndex);
    counter++;

    bool* recursiveUsedLabels = new bool[numFeatures];

    for(int i = 0; i < numFeatures; i++){
        if(usedLabels[i] && data[i][chosenIndex] == 1){
            recursiveUsedLabels[i] = true;
        }else{
            recursiveUsedLabels[i] = false;
        }
    }

    newNode->setLeftChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedLabels,newNode, counter));

        for(int i = 0; i < numFeatures; i++){
            if(usedLabels[i] && data[i][chosenIndex] == 0){
                recursiveUsedLabels[i] = true;
            }else{
                recursiveUsedLabels[i] = false;
            }
        }

    newNode->setRightChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedLabels,newNode,counter));
    return newNode;
}

void DecisionTree::print(){
//    DecisionTreeNode* curr = root;
//
//    while(curr != NULL ){
//        cout << curr->getItem() << endl;
//        curr = curr->getLeftChildPtr();
//    }
//
//    print();
//
//    curr = root;
//
//    while(curr != NULL ){
//        cout << curr->getItem() << endl;
//        curr = curr->getRightChildPtr();
//    }
//    print();
    preorder(root);
}

void DecisionTree::preorder(DecisionTreeNode* node) {

   if (node != NULL) {
      cout<<node->getItem()<<endl;
      preorder(node->getLeftChildPtr());
      preorder(node->getRightChildPtr());
   }
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures){

    ifstream infileReader;

    infileReader.open("E:\\Cs 202 hws\\C-Decision-Tree\\Cs202_decision_tree\\src\\train_data.txt"); //""
    cout << infileReader.is_open()<< endl;
    int condition;

    const bool** data = new const bool* [numSamples];

    for(int i = 0; i < numSamples; i++){
        bool* line = new bool[numFeatures];
        int counter = 0;
        bool loop = true;

        while(infileReader >> condition && loop){
            //cout<< condition << endl;
            line[counter] = condition;
            counter++;

            if(counter == numFeatures)
                loop = false;
        }
        //infileReader >> condition;
        //loop = true;
        data[i] = line;
    }


    for(int i = 0; i < numSamples; i++){
        for(int j = 0; j < numFeatures; j++){
            cout << data[i][j];
        }
        cout << endl;
    }
}
