#include <string>
#include <optional>
#include <unordered_map>

class RadixTree
{
public:
    struct RadixNode
    {
        std::unordered_map<char, RadixNode *> children;
        std::optional<int> value = std::nullopt;
    };

    RadixTree() : root(new RadixNode) {}

    void insert(const std::string &key, int value);

    std::optional<int> find(const std::string &key);

    bool increment(const std::string &key);

private:
    RadixNode *root;
};
