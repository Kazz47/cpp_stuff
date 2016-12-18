#include "utils/node.h"

#include <gtest/gtest.h>

using namespace std;

TEST(nodeTest, canCreateNode) {
    const Node<int> node(10);
    EXPECT_TRUE(node.value() == 10);
    EXPECT_TRUE(node.children().empty());
}

TEST(nodeTest, canAddChild) {
    Node<int> node(10);
    Node<int> childNode(20);

    node.children().push_back(&childNode);

    EXPECT_EQ(&childNode, node.children().front());
}

TEST(nodeTest, canSetParent) {
    Node<int> node(20);
    Node<int> parentNode(10);

    node.parent() = &parentNode;

    EXPECT_EQ(&parentNode, node.parent());
}

TEST(nodeTest, canSetInitialChildSize) {
    const Node<int, 10> node(20);

    EXPECT_FALSE(node.children().empty());
    EXPECT_EQ(10, node.children().size());
}
