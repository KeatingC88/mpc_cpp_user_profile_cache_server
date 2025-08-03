FROM ubuntu:22.04

# Install required tools and libraries
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    libssl-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory for build
WORKDIR /app

# Copy entire project into container
COPY . .

# Move .env to where your binary will run from
COPY .env ./build/

# Build the project
RUN mkdir -p build \
 && cd build \
 && cmake .. \
 && make

# Set runtime working directory to match .env location
WORKDIR /app/build

# Run your built server (which now finds .env in CWD)
CMD ["./mpc_cpp_user_profile_cache_server"]
