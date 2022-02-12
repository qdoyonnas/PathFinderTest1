#pragma once

struct Node {
    Node* p_parent = nullptr; // previous node in path

    // Linked list functionality
    Node* next_node = nullptr;
    Node* previous_node = nullptr;

    pair<int, int> position;
    int distanceToStart = 0;
    int distanceToTarget = 0;
    int value = 0;

    Node();
    Node(pair<int, int> position, Node* p_parent);
};

/// <summary>
/// Rudimentary linked list using path finding nodes.
/// Allows nodes removing themselves from the open list without searching.
/// </summary>
class NodeList {
public:
    Node* begin = nullptr;
    Node* end = nullptr;
    int size = 0;

    void insert(Node* before_node, Node* new_node);
    void erase(Node* node);
    void pop_front();
    void push_front(Node* node);
    void push_back(Node* node);
};
