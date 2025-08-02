#include <nerva/IHandler.hpp>

#include "RadixTree.hpp"

class RateLimiter : public IHandler {
    public:
        RadixTree ips;

        void Handle(Http::Request &req, Http::Response &res, std::function<void()> next) override;
};