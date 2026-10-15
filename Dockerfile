# syntax=docker/dockerfile:1

# ---------- Stage 1: build ----------
FROM debian:bookworm AS builder

RUN apt-get update && apt-get install -y --no-install-recommends 
    build-essential 
    cmake 
    ninja-build 
    pkg-config 
    libdrogon-dev 
    libpq-dev 
    ca-certificates 
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src/main/c++

COPY . .

RUN cmake -S . -B build 
    -G Ninja 
    -DCMAKE_BUILD_TYPE=Release 
    -DBUILD_TESTING=OFF

RUN cmake --build build --parallel
