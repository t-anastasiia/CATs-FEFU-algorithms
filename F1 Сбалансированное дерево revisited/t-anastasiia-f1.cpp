//
// Created by Анастасия Талмазан on 2024-06-17.
//
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
    int height;
};

// Вычисление высоты узла
int getHeight(TreeNode *node) {
    return (node == nullptr ? -1 : node->height);
}

// Правый поворот
TreeNode *rightRotate(TreeNode *&node) {
    if (node->left != nullptr) {
        TreeNode *leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        leftChild->height = max(getHeight(leftChild->left), node->height) + 1;
        return leftChild;
    }
    return node;
}

// Левый поворот
TreeNode *leftRotate(TreeNode *&node) {
    if (node->right != nullptr) {
        TreeNode *rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        rightChild->height = max(getHeight(rightChild->right), node->height) + 1;
        return rightChild;
    }
    return node;
}

// Левый-правый поворот
TreeNode *leftRightRotate(TreeNode *&node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

// Правый-левый поворот
TreeNode *rightLeftRotate(TreeNode *&node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

TreeNode *insertNode(int value, TreeNode *node) {
    if (node == nullptr) {
        node = new TreeNode{value, nullptr, nullptr, 0};
    } else if (value < node->value) {
        node->left = insertNode(value, node->left);
        if (getHeight(node->left) - getHeight(node->right) == 2) {
            if (value < node->left->value) {
                node = rightRotate(node);
            } else {
                node = rightLeftRotate(node);
            }
        }
    } else if (value > node->value) {
        node->right = insertNode(value, node->right);
        if (getHeight(node->right) - getHeight(node->left) == 2) {
            if (value > node->right->value) {
                node = leftRotate(node);
            } else {
                node = leftRightRotate(node);
            }
        }
    }

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

TreeNode *findMinimum(TreeNode *node) {
    if (node == nullptr) return nullptr;
    else if (node->left == nullptr) return node;
    else return findMinimum(node->left);
}

TreeNode *removeNode(int value, TreeNode *node) {
    if (node == nullptr) return nullptr;

    if (value < node->value) {
        node->left = removeNode(value, node->left);
    } else if (value > node->value) {
        node->right = removeNode(value, node->right);
    } else if (node->left != nullptr && node->right != nullptr) {
        TreeNode *minNode = findMinimum(node->right);
        node->value = minNode->value;
        node->right = removeNode(node->value, node->right);
    } else {
        TreeNode *oldNode = node;
        node = (node->left != nullptr) ? node->left : node->right;
        delete oldNode;
    }

    if (node == nullptr) return node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Rebalancing the tree
    if (getHeight(node->left) - getHeight(node->right) == 2) {
        if (getHeight(node->left->left) - getHeight(node->left->right) >= 0) {
            node = rightRotate(node);
        } else {
            node = rightLeftRotate(node);
        }
    } else if (getHeight(node->right) - getHeight(node->left) == 2) {
        if (getHeight(node->right->right) - getHeight(node->right->left) >= 0) {
            node = leftRotate(node);
        } else {
            node = leftRightRotate(node);
        }
    }

    return node;
}

void displayInOrder(TreeNode *node) {
    if (node != nullptr) {
        displayInOrder(node->left);
        output << node->value << " ";
        displayInOrder(node->right);
    }
}

int main() {
    TreeNode *root = nullptr;
    int element;
    while (input >> element) {
        if (element > 0) {
            root = insertNode(element, root);
        } else if (element < 0) {
            root = removeNode(-element, root);
        } else if (element == 0) {
            displayInOrder(root);
            break;
        }
    }

    return 0;
}
