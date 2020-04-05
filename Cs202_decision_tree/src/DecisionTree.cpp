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
    //cout << "before: " << counter << endl;
    root->setLeftChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));
    //cout << "After: " << counter << endl;
    for(int i = 0; i < numSamples; i++){
        //cout << i << "deki sayı " << data[i][4] << endl;

        if(data[i][chosenFeatureIndex] == 1){
            usedSamplesArr[i] = true;
        }else{
            usedSamplesArr[i] = false;
        }
    }

    for(int i = 0; i < numFeatures; i++){
        usedLabelsArr[i] = false;
    }

    usedLabelsArr[chosenFeatureIndex] = true;

    root->setRightChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));
}

DecisionTreeNode* DecisionTree::split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedSamplesArr,DecisionTreeNode* node,int& counter, bool usedLabelsArr[]){
    double maxInfoGain = 0;
    double infoGain = 0;
    int chosenIndex = 0;
    //counter++;

    if(counter == numFeatures){
        return NULL;
    }

    for(int i = 0; i < numFeatures; i++){
        if(!usedLabelsArr[i]){
            infoGain = calculateInformationGain(data, labels, numSamples,numFeatures,usedSamplesArr,i);
        }

//        if(infoGain == 0 && !usedLabelsArr[i]){
//            chosenIndex = i;
//            break;
//        }

        if(infoGain >= maxInfoGain){
            maxInfoGain = infoGain;
            chosenIndex = i;
        }
    }

    if(maxInfoGain == 0){
    int countLabelsArr[3] = {0,0,0};

    // Calculate label counts of each used label for parent root
    for(int i = 0; i < numSamples; i++){
        if(usedSamplesArr[i]){
            if(labels[i] == 1){
                countLabelsArr[0] = countLabelsArr[0] + 1;
            }else if(labels[i] == 2){
                countLabelsArr[1] = countLabelsArr[1] + 1;
            }else{
                countLabelsArr[2] = countLabelsArr[2] + 1;
            }

        }
    }

    int maxLabel = 0;
    int maxValue = 0;

    for(int i = 0; i < 3; i++){
        if(countLabelsArr[i] >= maxValue){
           maxValue =  countLabelsArr[i];
           maxLabel = i + 1;
        }
    }

        DecisionTreeNode* newNode = new DecisionTreeNode(maxLabel + 40);
        newNode->setLeaf(true);
        //usedLabelsArr[chosenIndex] = true;
        return newNode;
    }

    //if(maxInfoGain == 0){
        //usedLabelsArr[chosenIndex] = true;
        //return NULL;
    //}

    DecisionTreeNode* newNode = new DecisionTreeNode(chosenIndex + 1);
    usedLabelsArr[chosenIndex] = true;
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
    preorder(root,"Root: ");
}

void DecisionTree::preorder(DecisionTreeNode* node,string dir) {

   if (node != NULL) {
      cout<< dir << node->getItem()<<endl;
      preorder(node->getLeftChildPtr(),"Left: ");
      preorder(node->getRightChildPtr(),"Right: ");
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

int DecisionTree::predict(const bool* data){
    DecisionTreeNode* curr = root;

    while(!(curr->isLeaf())){
        if(data[curr->getItem() - 1] == 0){
            curr = curr->getLeftChildPtr();
        }else{
            curr = curr->getRightChildPtr();
        }
    }

    return curr->getItem();
}
