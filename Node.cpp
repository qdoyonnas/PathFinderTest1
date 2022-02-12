#include <vector>
using namespace std;

#include "Node.hpp"

void NodeList::insert(Node* before_node, Node* new_node)
{
    if (size == 0) {
        begin = new_node;
        end = new_node;
    }
    else {
        Node* temp_prev = nullptr;
        if (before_node != nullptr) { 
            temp_prev = before_node->previous_node;
            before_node->previous_node = new_node;
        }
        if (temp_prev != nullptr) {
            temp_prev->next_node = new_node;
        }
        else {
            begin = new_node;
        }

        new_node->next_node = before_node;
        new_node->previous_node = temp_prev;
    }

    size++;
}
void NodeList::erase(Node* node)
{
    Node* temp_next = node->next_node;
    Node* temp_prev = node->previous_node;
    if (temp_next != nullptr) {
        temp_next->previous_node = temp_prev;
    }
    else {
        end = temp_prev;
    }
    if (temp_prev != nullptr) {
        temp_prev->next_node = temp_next;
    }
    else {
        begin = temp_next;
    }

    size--;
}
void NodeList::pop_front()
{
    if (begin != nullptr) {
        begin = begin->next_node;
        if (begin != nullptr) {
            begin->previous_node = nullptr;
        }
        else {
            end = nullptr;
        }
    }

    size--;
}
void NodeList::push_front(Node* node)
{
    Node* temp_begin = begin;
    begin = node;
    node->next_node = temp_begin;
    if (temp_begin != nullptr) {
        temp_begin->previous_node = node;
    }
    else {
        end = node;
    }

    size++;
}
void NodeList::push_back(Node* node)
{
    Node* temp_end = end;
    end = node;
    node->previous_node = temp_end;
    if (temp_end != nullptr) {
        temp_end->next_node = node;
    }
    else {
        begin = node;
    }

    size++;
}

Node::Node() {}
Node::Node(pair<int, int> position, Node* p_parent)
{
    this->position = position;
    this->p_parent = p_parent;
}