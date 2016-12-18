#pragma once

#include "node.h"
#include "stringIt.h"

template <typename T>
bool isBinaryTree(const Node<T>& node) {
    if (node.children().empty()) return true;
    if (node.children().size() != 2) return false;

    bool isBinary = true;
    const Node<T>* leftChild = node.children()[0];
    if (leftChild == nullptr) {
        throw std::invalid_argument(StringIt()
            << "Left child of " << &node << " with value " << node.value() << " is NULL.");
    } else if (leftChild->value() >= node.value()) {
        return false;
    } else {
        isBinary &= isBinaryTree(*leftChild);
    }

    const Node<T>* rightChild = node.children()[1];
    if (rightChild == nullptr) {
        throw std::invalid_argument(StringIt()
            << "Right child of " << &node << " with value " << node.value() << " is NULL.");
    } else if (rightChild->value() < node.value()) {
        return false;
    } else {
        isBinary &= isBinaryTree(*rightChild);
    }

    return isBinary;
}
