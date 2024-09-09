# Redis-Like Key-Value Store

## Overview

This project is a high-performance key-value store inspired by Redis, developed using modern C++14. It leverages Boost.Asio for asynchronous I/O and multithreading to efficiently manage client connections and server operations. The implementation emphasizes scalability and concurrency, and includes features for data persistence and logging.

## Features

- **Asynchronous I/O**: Utilizes Boost.Asio to handle multiple simultaneous client connections with non-blocking operations.
- **Multithreading**: Employs a multithreaded architecture to separate client connection management from server console command handling, including a dedicated logger thread.
- **Core Commands**: Implements essential Redis commands including `get`, `set`, `del`, `exists`, and more.
- **List Operations**: Supports list operations including `lpush`, `lpop`, `rpush`, `rpop`, `get-range <key> <start> <end>`, `get-size <key>`, and `get-list <key>`.
- **Time-to-Live (TTL)**: Provides TTL functionality to manage the expiration of keys in seconds.
- **Append-Only File (AOF) Persistence**: Supports AOF persistence, with logs stored in the working directory to ensure data durability.
- **Error Handling**: Includes comprehensive error handling mechanisms to ensure stability and reliability.

## Getting Started

### Prerequisites

- **C++14 Compiler**: Ensure your development environment supports C++14.
- **Boost.Asio**: This project relies on Boost.Asio, installed via [vcpkg](https://github.com/microsoft/vcpkg).

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/atharvaa12/Redis-like-KV-Store.git
   cd redis-like-kv-store
   ```

2. **Build the Project**

   For Visual Studio users, open the provided solution file (`.sln`) and build the project. For other environments, adjust the build process accordingly.

### Usage

1. **Start the Server**

   Execute the compiled binary to start the server on port 1234:


2. **Connect to the Server**

   Use a Telnet client or a TCP client to connect to port 1234:

   ```bash
   telnet localhost 1234
   ```

3. **Issue Commands**

   Example commands to interact with the server:

   ```text
   set mykey "Hello, World!"
   get mykey
   del mykey
   ```

   To set a key with a TTL (in seconds):

   ```text
   set mykey "value" 3600
   ```

   List operations:

   ```text
   lpush mylist "value1"
   rpush mylist "value2"
   lpop mylist
   rpop mylist
   get-range mylist 0 10
   get-size mylist
   get-list mylist
   ```

## Logging and Persistence

- **Append-Only File (AOF)**: The server logs commands to an AOF file stored in the working directory. This ensures data persistence and recovery in case of failures.
- **Logger Thread**: A dedicated logger thread handles logging operations to maintain server performance and stability.

## Contributing

Contributions are welcome. Please fork the repository and submit a pull request with your changes. Ensure that your contributions include relevant tests and adhere to the project's coding standards.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


