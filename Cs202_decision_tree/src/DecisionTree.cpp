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
    bool usedLabelsArr[numFeatures];

    for(int i = 0; i < numSamples; i++){
        usedSamplesArr[i] = true;
    }

    for(int i = 0; i < numFeatures; i++){
        usedLabelsArr[i] = false;
    }

    double maxInfoGain = 0;

    for(int i = 0; i < numFeatures; i++){
        double infoGain = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamplesArr,i);

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenFeatureIndex = i;
        }
    }

    root = new DecisionTreeNode(chosenFeatureIndex + 1);
    usedLabelsArr[chosenFeatureIndex] = true;
    //usedLabels[chosenFeatureIndex] = true;
//    int rootItem = root ->getItem();
  //  int currItem = curr ->getItem();
  //---------------------------------------------------------------------------------------
  //bura
   // bool* usedLabels = new bool[numSamples];

    for(int i = 0; i < numSamples; i++){
            if(data[i][chosenFeatureIndex] == 0){
                usedSamplesArr[i] = true;
            }else{
                usedSamplesArr[i] = false;
            }
        }

    int counter = 1;
    root->setLeftChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));

    for(int i = 0; i < numSamples; i++){
        //cout << i << "deki sayı " << data[i][4] << endl;

        if(data[i][chosenFeatureIndex] == 1){
            usedSamplesArr[i] = true;
        }else{
            usedSamplesArr[i] = false;
        }
    }

    root->setRightChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));
}

DecisionTreeNode* DecisionTree::split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedSamplesArr,DecisionTreeNode* node,int& counter, bool usedLabelsArr[]){
    double maxInfoGain = 0;
    double infoGain = 0;
    int chosenIndex = 0;

    if(counter == numFeatures){
        return NULL;
    }

    for(int i = 0; i < numFeatures; i++){
        if(!usedLabelsArr[i]){
            infoGain = calculateInformationGain(data, labels, numSamples,numFeatures,usedSamplesArr,i);
        }

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenIndex = i;
        }
    }

    if(maxInfoGain == 0){
        DecisionTreeNode* newNode = new DecisionTreeNode(labels[chosenIndex]+40);
        //usedLabelsArr[chosenIndex] = true;
        return newNode;
    }

    DecisionTreeNode* newNode = new DecisionTreeNode(chosenIndex);
    counter++;

    bool* recursiveUsedSamples = new bool[numSamples];

    for(int i = 0; i < numSamples; i++){
        if(usedSamplesArr[i] && data[i][chosenIndex] == 0){
            recursiveUsedSamples[i] = true;
        }else{
            recursiveUsedSamples[i] = false;
        }
    }

    newNode->setLeftChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedSamples,newNode, counter, usedLabelsArr));

        for(int i = 0; i < numSamples; i++){
            if(usedSamplesArr[i] && data[i][chosenIndex] == 1){
                recursiveUsedSamples[i] = true;
            }else{
                recursiveUsedSamples[i] = false;
            }
        }

    newNode->setRightChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedSamples,newNode,counter,usedLabelsArr));
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

    ifstream dataReader;
    ifstream labelReader;

    dataReader.open("E:\\Cs 202 hws\\C-Decision-Tree\\Cs202_decision_tree\\src\\train_data.txt"); //""
   // cout << dataReader.is_open()<< endl;
    int condition;

    const bool** data = new const bool* [numSamples];

    int counter = 0;
    for(int i = 0; i < numSamples; i++){
        bool* line = new bool[numFeatures];

        bool loop = true;

    while((dataReader >> condition) && loop){
            //cout<< condition << endl;
            line[counter] = condition;
            counter++;

            if(counter == numFeatures)
                loop = false;
        }
        //infileReader >> condition;
        //loop = true;
        counter = 0;
        data[i] = line;
    }

    labelReader.open("E:\\Cs 202 hws\\C-Decision-Tree\\Cs202_decision_tree\\src\\train_data.txt");

    int* labels = new int[numSamples];

    counter = 1;

    while(labelReader >> condition){
        if(counter % 22 == 0)
            labels[(counter / 22) - 1 ] = condition;
        counter++;
    }


//    for(int i = 0; i < numSamples; i++){
//            //out << labels[i] << endl;
//        for(int j = 0; j < numFeatures; j++){
//            cout << data[i][j];
//        }
//        cout << endl;
//    }
//
//    cout <<"----------------------------------------------- "<<endl;
//    for(int i = 0; i < numSamples; i++){
//            cout << labels[i] << endl;
//    }

    train(data, labels, numSamples,numFeatures);
}
