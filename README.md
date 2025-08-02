# Rate Limiter for Nerva Server

This project is a Rate Limiter plugin developed for [Nerva Server](https://github.com/nerva-server). It protects your server against DDoS attacks and overload by limiting HTTP requests based on IP addresses.

## Features

- **IP-Based Rate Limiting**: Separate request count tracking for each IP address
- **Time Window**: Configurable time window (default: 15 minutes)
- **Request Limit**: Configurable request limit (default: 100 requests)
- **Radix Tree**: High-performance IP address storage and search
- **Automatic Cleanup**: Automatic cleanup of old records

## Installation

### Usage Within Nerva Server Project

1. Go to the root directory of your Nerva Server project
2. Create the `libs/` directory (if it doesn't exist):
   ```bash
   mkdir libs
   ```
3. Clone this project into the `libs/` directory:
   ```bash
   cd libs
   git clone https://github.com/nerva-server/rate-limiter
   ```

### Building

The project will be automatically built with Nerva Server's build system. For manual building:

```bash
make
```

## Usage

### Basic Usage

```cpp
#include <nerva/IHandler.hpp>
#include "RateLimiter.hpp"

// Create Rate Limiter instance
RateLimiter rateLimiter;

// Add as handler
server.Use("/*", rateLimiter);
```

### Configuration

You can customize the Rate Limiter's behavior using the `config` structure:

```cpp
RateLimiter rateLimiter;
rateLimiter.config.windowMs = 5 * 60 * 1000; // 5 minutes
rateLimiter.config.limit = 50; // 50 requests
```

### Default Settings

- **Time Window**: 15 minutes (15 * 60 * 1000 ms)
- **Request Limit**: 100 requests
- **HTTP Status Code**: 429 (Too Many Requests)

## How It Works

1. **Request Arrival**: When each HTTP request arrives, the Rate Limiter activates
2. **IP Check**: The request's IP address is searched in the Radix Tree
3. **Time Window**: Requests within the last 15 minutes are counted
4. **Limit Check**: If the request count exceeds the limit, a 429 error is returned
5. **Recording**: If the request is successful, the IP address and timestamp are recorded

## File Structure

```
RateLimiter/
├── includes/
│   ├── RateLimiter.hpp    # Main Rate Limiter class
│   └── RadixTree.hpp      # Radix Tree for IP address storage
├── src/
│   └── RateLimiter.cpp    # Rate Limiter implementation
├── Makefile               # Build configuration
└── README.md             # This file
```

## Requirements

- C++20 compatible compiler
- Nerva Server framework
- Clang++ or GCC

## Contributing

1. Fork this repository
2. Create a new branch (`git checkout -b feature/new-feature`)
3. Commit your changes (`git commit -am 'Added new feature'`)
4. Push your branch (`git push origin feature/new-feature`)
5. Create a Pull Request

## License

This project is distributed under the same license as Nerva Server.

## Support

You can use the [GitHub Issues](https://github.com/nerva-server/rate-limiter/issues) page for your problems. 