FROM ubuntu:22.04

# Install required C++ build tools, debugging tools, and VS Code Server requirements
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    gdb \
    valgrind \
    git \
    curl \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/taskforge