#pragma once

#include <vector>

template <typename T, size_t N = 0>
class Node {
public:
    typedef std::vector<Node<T>*> Nodes;

    explicit Node(const T& val)
        : mValue(val),
          mChildNodes(N, nullptr),
          mParent(nullptr) {}

    T value() const { return mValue; }
    T& value() { return mValue; }

    Nodes children() const { return mChildNodes; }
    Nodes& children() { return mChildNodes; }
    Node<T>* parent() const { return mParent; }
    Node<T>*& parent() { return mParent; }

protected:
    T mValue;
    Nodes mChildNodes;
    Node<T>* mParent;
};
