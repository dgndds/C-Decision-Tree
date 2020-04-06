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

    root = new DecisionTreeNode(chosenFeatureIndex);
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

    counter = 1;
    root->setRightChildPtr(split(data, labels,numSamples, numFeatures,usedSamplesArr,root,counter,usedLabelsArr));
}

DecisionTreeNode* DecisionTree::split(const bool** data, const int* labels, const int numSamples, const int numFeatures,const bool* usedSamplesArr,DecisionTreeNode* node,const int counter, bool usedLabelsArr[]){
    double maxInfoGain = 0;
    double infoGain = 0;
    int chosenIndex = 0;
    int oldCounter = counter;
    //counter++;

//    if(counter > numFeatures){
//        return NULL;
//    }

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
        infoGain = 0;
    }

    if(maxInfoGain == 0 || counter > numFeatures){

    int labelCount = 0;
    int* uniqeLabels = findFeatureFrequecy(labels, usedSamplesArr, numSamples,labelCount);
    int countLabelsArr[labelCount];

    for(int i = 0; i < labelCount; i++){
        countLabelsArr[i] = 0;
    }
    // Calculate label counts of each used label for parent root
//    for(int i = 0; i < numSamples; i++){
//        if(usedSamplesArr[i]){
//            if(labels[i] == 1){
//                countLabelsArr[0] = countLabelsArr[0] + 1;
//            }else if(labels[i] == 2){
//                countLabelsArr[1] = countLabelsArr[1] + 1;
//            }else{
//                countLabelsArr[2] = countLabelsArr[2] + 1;
//            }
//
//        }
//    }

    for(int i = 0; i < numSamples; i++){
            for(int j = 0; j < labelCount ; j++){
                if(usedSamplesArr[i] && (labels[i] == uniqeLabels[j])){
                    countLabelsArr[j]++;
                }
            }
    }

    int maxLabel = 0;
    int maxValue = 0;

    for(int i = 0; i < labelCount; i++){
        if(countLabelsArr[i] >= maxValue){
           maxValue =  countLabelsArr[i];
           maxLabel = i ;//+ 1;
        }
    }

        DecisionTreeNode* newNode = new DecisionTreeNode(uniqeLabels[maxLabel]);
        newNode->setLeaf(true);
        //usedLabelsArr[chosenIndex] = true;
        //if(counter > numFeatures){
           // counter--;
       // }

        return newNode;
    }

    //if(maxInfoGain == 0){
        //usedLabelsArr[chosenIndex] = true;
        //return NULL;
    //}

    DecisionTreeNode* newNode = new DecisionTreeNode(chosenIndex);
    usedLabelsArr[chosenIndex] = true;
    oldCounter++;

    bool* recursiveUsedSamples = new bool[numSamples];

    for(int i = 0; i < numSamples; i++){
        if(usedSamplesArr[i] && data[i][chosenIndex] == 0){
            recursiveUsedSamples[i] = true;
        }else{
            recursiveUsedSamples[i] = false;
        }
    }

    newNode->setLeftChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedSamples,newNode, oldCounter, usedLabelsArr));

        for(int i = 0; i < numSamples; i++){
            if(usedSamplesArr[i] && data[i][chosenIndex] == 1){
                recursiveUsedSamples[i] = true;
            }else{
                recursiveUsedSamples[i] = false;
            }
        }

    newNode->setRightChildPtr(split(data,labels,numSamples,numFeatures,recursiveUsedSamples,newNode,oldCounter,usedLabelsArr));

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
    preorder(root,0);
}

void DecisionTree::preorder(DecisionTreeNode* node,const int tabCount) {
    int oldTabCount = tabCount;



   if (node != NULL) {
        if(!node->isLeaf()){
             cout<< node->getItem()<<endl;
             //cout << "\t";
             oldTabCount++;
             for(int i = 0; i < oldTabCount; i++){
                cout << "\t";
            }

        }else{
             cout<< "class = " << node->getItem()<<endl;
             //cout << "\t";
             //oldTabCount--;

             for(int i = 0; i < oldTabCount; i++){
                cout << "\t";
            }

        }




    preorder(node->getLeftChildPtr(),oldTabCount);
        //cout << "\t";

      preorder(node->getRightChildPtr(),oldTabCount);
oldTabCount++;

   }
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures){
    featureNum = numFeatures;
    sampleNum = numSamples;

    ifstream dataReader;
    ifstream labelReader;

    dataReader.open(fileName.c_str()); //""
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

    labelReader.open(fileName.c_str());

    int* labels = new int[numSamples];

    counter = 1;

    while(labelReader >> condition){
        if(counter % (numFeatures + 1) == 0)
            labels[(counter / (numFeatures + 1)) - 1 ] = condition;
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

    train(data, labels, numSamples,numFeatures);
}

int DecisionTree::predict(const bool* data){
    DecisionTreeNode* curr = root;

    while(!(curr->isLeaf())){
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

    for(int i = 0; i < numSamples; i++){
        if(predict(data[i]) == labels[i]){
            correct++;
        }
    }

    return (double)correct/(double)numSamples;
}

int DecisionTree::getFeatureCount(){ ////////////////----------------------- !!!!!!!!!! DELETE FROM HERE AND HEADER !!!!!!!!!! -----------------------////////////////
    return featureNum;
}

double DecisionTree::test(const string fileName, const int numSamples){
    ifstream dataReader;
    ifstream labelReader;

    dataReader.open(fileName.c_str()); //""
   // cout << dataReader.is_open()<< endl;
    int condition;

    const bool** data = new const bool* [numSamples];

    int counter = 0;
    for(int i = 0; i < numSamples; i++){
        bool* line = new bool[featureNum];

        bool loop = true;

    while((dataReader >> condition) && loop){
            //cout<< condition << endl;
            line[counter] = condition;
            counter++;

            if(counter == featureNum)
                loop = false;
        }
        //infileReader >> condition;
        //loop = true;
        counter = 0;
        data[i] = line;
    }

    labelReader.open(fileName.c_str());

    int* labels = new int[numSamples];

    counter = 1;

    while(labelReader >> condition){
        if(counter % (featureNum + 1) == 0)
            labels[(counter / (featureNum + 1)) - 1 ] = condition;
        counter++;
    }


//    for(int i = 0; i < numSamples; i++){
//            out << labels[i] << endl;
//        for(int j = 0; j < 21; j++){
//            cout << data[i][j];
//        }
//        cout << endl;
//    }
//
//    cout <<"----------------------------------------------- "<<endl;
//    for(int i = 0; i < numSamples; i++){
//            cout << labels[i] << endl;
//    }

    return test(data,labels,numSamples);
}
