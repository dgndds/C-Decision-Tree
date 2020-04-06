#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H


class DecisionTreeNode
{
    public:
        DecisionTreeNode();
        DecisionTreeNode( const int& anItem);
        DecisionTreeNode( const int& anItem, DecisionTreeNode* leftPtr,DecisionTreeNode* rightPtr);
        void setItem( const int& anItem);
        int getItem() const;
        bool isLeaf() const;
        void setLeaf(const bool newLeaf);
        DecisionTreeNode* getLeftChildPtr() const;
        DecisionTreeNode* getRightChildPtr() const;
        void setLeftChildPtr(DecisionTreeNode* leftPtr);
        void setRightChildPtr(DecisionTreeNode* rightPtr);

    private:
        int item; // Data portion
        bool leaf; // leaf or not
        DecisionTreeNode* leftChildPtr; // Pointer to left child
        DecisionTreeNode* rightChildPtr; // Pointer to right child

};

#endif // DECISIONTREENODE_H
