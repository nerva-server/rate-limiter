#include "RateLimiter.hpp"
#include <iostream>
#include <chrono>

void RateLimiter::Handle(Http::Request &req, Http::Response &res, std::function<void()> next)
{
    try
    {
        auto now = std::chrono::system_clock::now();
        auto recentRequests = ips.find_within_window(req.ip, std::chrono::milliseconds(Config.windowMs));

        size_t requestCount = recentRequests.size();

        ips.insert(req.ip, 1, now);

        if (requestCount >= Config.limit)
        {
            res << 429 << "Too Many Requests";
            return;
        }

        next();
    }
    catch (const std::exception &e)
    {
        std::cerr << "RateLimiter error: " << e.what() << '\n';
        next();
    }
}