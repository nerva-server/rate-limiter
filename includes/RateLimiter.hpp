#include <nerva/IHandler.hpp>

#include "RadixTree.hpp"

class RateLimiter : public IHandler {
    public:
        RadixTree ips;

        struct config {
            int windowMs = 15 * 60 * 1000; // 15 Minutes
            int limit = 100;
        };

        void Handle(Http::Request &req, Http::Response &res, std::function<void()> next) override;
};