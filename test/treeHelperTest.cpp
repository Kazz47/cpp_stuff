#include "utils/treeHelper.h"
#include "utils/node.h"

#include <gtest/gtest.h>

using namespace std;

TEST(treeHelperIsBinaryTest, canCheckSingleNodeTree) {
    Node<int> root(10);

    EXPECT_TRUE(isBinaryTree(root));
}

TEST(treeHelperIsBinaryTest, throwIfChildrenAreNull) {
    Node<int> root(10, 2);

    EXPECT_THROW(isBinaryTree(root), std::invalid_argument);
}

TEST(treeHelperIsBinaryTest, canCheckSmallTree) {
    Node<int> root(10, 2);
    Node<int> leftChild(5);
    Node<int> rightChild(15);

    root.children()[0] = &leftChild;
    root.children()[1] = &rightChild;

    EXPECT_TRUE(isBinaryTree(root));
}

TEST(treeHelperIsBinaryTest, falseForUnsortedTree) {
    Node<int> root(10, 2);
    Node<int> leftChild(15);
    Node<int> rightChild(5);

    root.children()[0] = &leftChild;
    root.children()[1] = &rightChild;

    EXPECT_FALSE(isBinaryTree(root));
}

TEST(treeHelperIsBinaryTest, falseForTreeWithBadStructure) {
    Node<int> root(10, 2);
    Node<int> leftChild(5, 3); // Three children
    Node<int> rightChild(15);

    root.children()[0] = &leftChild;
    root.children()[1] = &rightChild;

    EXPECT_FALSE(isBinaryTree(root));
}

TEST(treeHelperIsBinaryTest, falseForIncorrectSize) {
    Node<int> root(10, 3);
    Node<int> leftChild(5);
    Node<int> centerChild(10);
    Node<int> rightChild(15);

    root.children()[0] = &leftChild;
    root.children()[1] = &centerChild;
    root.children()[2] = &rightChild;

    EXPECT_FALSE(isBinaryTree(root));
}
