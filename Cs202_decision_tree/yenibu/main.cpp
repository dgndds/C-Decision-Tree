#include <stdio.h>
#include <iostream>
#include "Calculate.h"
#include "DecisionTreeNode.h"
#include "DecisionTree.h"
#include <string>

using namespace std;

int main( int argc, const char* argv[] )
{
//    int arr[3] = {32,0,7};
//
//	cout << calculateEntropy(arr,3) << endl;

//	DecisionTreeNode* root = new DecisionTreeNode(5);
//
//	cout << root->getItem() << endl;
//
//	root->setLeftChildPtr(new DecisionTreeNode(10));
//	root->setRightChildPtr(new DecisionTreeNode(15));
//
//    DecisionTreeNode* curr = root->getLeftChildPtr();
//    cout << curr->getItem() << endl;
//
//    curr->setLeftChildPtr(new DecisionTreeNode(20));
//    curr->setRightChildPtr(new DecisionTreeNode(25));
////
////    cout << root->getRightChildPtr()->getLeftChildPtr()->getItem() << endl;
//
//   const bool** data = new const bool*[5];
////
//   for(int i = 0; i < 5; ++i)
//        data[i] = new  bool[5]{true,false,true,false,true};
////
////
////    //const bool data1[5][5]{{false,false,false,true,false},{true,false,false,true,true},{false,false,true,true,false},{false,true,false,false,false},{false,false,true,true,false}};
////     //0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,1,1,0,0,1};
////
//   const int labels[5] = {1,2,1,3,2};
    DecisionTree tree;
//    tree.train(data, labels, 5,5);
////
//
//
////        //Free each sub-array
////    for(int i = 0; i < 5; ++i) {
////        delete[] data[i];
////    }
////    //Free the array of pointers
////    delete[] data;
////delete[] labels;
    const string fileName = "E:\\Cs 202 hws\\C-Decision-Tree\\Cs202_decision_tree\\src\\train_data.txt";

    tree.train(fileName, 498, 21);

   // cout << tree.getFeatureCount() << endl;
    tree.print();
//
    //const bool* predictArr = new const bool[21]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1};
    //cout << tree.predict(predictArr) << endl;
    const string fileName1 = "E:\\Cs 202 hws\\C-Decision-Tree\\Cs202_decision_tree\\src\\test_data.txt";

    double accuracy = tree.test(fileName1, 473);
    cout << endl << "accuracy: " << accuracy << endl;

	return 0;

}
