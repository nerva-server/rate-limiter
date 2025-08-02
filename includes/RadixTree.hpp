#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <utility>
#include <algorithm>

class RadixTree
{
public:
    struct RadixNode
    {
        std::unordered_map<char, RadixNode *> children;
        std::vector<std::pair<std::chrono::system_clock::time_point, int>> timed_values;
    };

    RadixTree() : root(new RadixNode) {}

    void insert(const std::string &key, int value)
    {
        insert(key, value, std::chrono::system_clock::now());
    }

    void insert(const std::string &key, int value, std::chrono::system_clock::time_point timestamp)
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
        node->timed_values.emplace_back(timestamp, value);
    }

    std::optional<int> find(const std::string &key)
    {
        auto values = find_within_window(key, std::chrono::hours(24 * 365 * 10));
        return values.empty() ? std::nullopt : std::optional<int>(values.back().second);
    }

    std::vector<std::pair<std::chrono::system_clock::time_point, int>>
    find_within_window(const std::string &key, std::chrono::milliseconds window)
    {
        auto now = std::chrono::system_clock::now();
        auto all_values = find_before(key, now);
        std::vector<std::pair<std::chrono::system_clock::time_point, int>> result;

        std::copy_if(all_values.begin(), all_values.end(), std::back_inserter(result),
                     [=](const auto &pair)
                     {
                         return pair.first >= (now - window);
                     });

        return result;
    }

    std::vector<std::pair<std::chrono::system_clock::time_point, int>>
    find_before(const std::string &key, std::chrono::system_clock::time_point cutoff)
    {
        RadixNode *node = root;
        for (char c : key)
        {
            if (!node->children.count(c))
                return {};
            node = node->children[c];
        }

        std::vector<std::pair<std::chrono::system_clock::time_point, int>> result;
        for (const auto &[timestamp, value] : node->timed_values)
        {
            if (timestamp <= cutoff)
            {
                result.emplace_back(timestamp, value);
            }
        }
        return result;
    }

    bool increment(const std::string &key)
    {
        RadixNode *node = root;
        for (char c : key)
        {
            if (!node->children.count(c))
                return false;
            node = node->children[c];
        }

        if (!node->timed_values.empty())
        {
            auto &last = node->timed_values.back();
            last.second++;
            return true;
        }
        return false;
    }

private:
    RadixNode *root;
};