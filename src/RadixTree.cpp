#include "RadixTree.hpp"

void RadixTree::insert(const std::string &key, int value)
{
    RadixNode *node = root;
    for (char c : key)
    {
        if (!node->children[c])
        {
            node->children[c] = new RadixNode;
        }
        node = node->children[c];
    }
    node->value = value;
}

std::optional<int> RadixTree::find(const std::string &key)
{
    RadixNode *node = root;
    for (char c : key)
    {
        if (!node->children.count(c))
            return std::nullopt;
        node = node->children[c];
    }
    return node->value;
}

bool RadixTree::increment(const std::string &key)
{
    RadixNode *node = root;
    for (char c : key)
    {
        if (!node->children.count(c))
            return false;
        node = node->children[c];
    }
    if (node->value.has_value())
    {
        node->value = node->value.value() + 1;
        return true;
    }
    return false;
}