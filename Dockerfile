FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    libboost-system-dev \
    libboost-thread-dev \
    libboost-program-options-dev \
    libboost-chrono-dev \
    libboost-filesystem-dev \
    libboost-regex-dev \
    libboost-iostreams-dev \
    libboost-date-time-dev \
    libboost-test-dev \
    libboost-all-dev \
    pkg-config \
    wget \
    curl

# Create app directory
WORKDIR /app

# Copy source code
COPY . .

# Build the project
RUN mkdir -p build && cd build && \
    cmake .. && \
    make

# Expose the server port
EXPOSE 8080

# Command to run
CMD ["./build/mpc_cpp_user_profile_cache_server"]
