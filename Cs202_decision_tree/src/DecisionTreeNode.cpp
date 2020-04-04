#include "DecisionTreeNode.h"
#include <iostream>

DecisionTreeNode::DecisionTreeNode(){
    item = 0;
    leaf = false;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}

DecisionTreeNode::DecisionTreeNode( const int& anItem){
    item = anItem;
    leaf = false;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}

DecisionTreeNode::DecisionTreeNode( const int& anItem, DecisionTreeNode* leftPtr,DecisionTreeNode* rightPtr){
    item = anItem;
    leaf = false;
    leftChildPtr = leftPtr;
    rightChildPtr = rightPtr;
}

void DecisionTreeNode::setItem( const int& anItem){
    item = anItem;
}

int DecisionTreeNode::getItem() const{
    return item;
}

bool DecisionTreeNode::isLeaf() const{
    return leaf;
}

void DecisionTreeNode::setLeaf(const bool newLeaf) {
    leaf = newLeaf;
}

DecisionTreeNode* DecisionTreeNode::getLeftChildPtr() const{
    if(leftChildPtr != NULL){
        return leftChildPtr;
    }else{
        return NULL;
    }

}

DecisionTreeNode* DecisionTreeNode::getRightChildPtr() const{
    if(rightChildPtr != NULL){
        return rightChildPtr;
    }else{
        return NULL;
    }
}
void DecisionTreeNode::setLeftChildPtr(DecisionTreeNode* leftPtr){
    leftChildPtr = leftPtr;
}

void DecisionTreeNode::setRightChildPtr(DecisionTreeNode* rightPtr){
    rightChildPtr = rightPtr;
}
