#include "application.hpp"


template <>
auto BinaryTree<int>::view(int item) -> std::string {
    return std::to_string(item);
}

template <>
auto BinaryTree<int>::value(BinaryTree<int>::Node* node) -> int {
    if (node) {
        return node->data;
    } else {
        return 0;
    }
}
