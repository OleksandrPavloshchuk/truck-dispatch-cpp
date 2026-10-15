# Stage 1: build Drogon

FROM debian:bookworm AS drogon-builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    libjsoncpp-dev \
    uuid-dev \
    libpq-dev \
    ca-certificates \
    catch2 \
    && rm -rf /var/lib/apt/lists/*

# Install CMake 4 for the application
ARG CMAKE_VERSION=4.5.0-rc1

ADD https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.sh \
    /tmp/cmake-install.sh

RUN mkdir -p /opt/cmake \
    && chmod +x /tmp/cmake-install.sh \
    && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake \
    && rm /tmp/cmake-install.sh

# Build Drogon with Debian's CMake
WORKDIR /src

COPY drogon/ /src/drogon/

RUN /usr/bin/cmake --version \
    && /usr/bin/cmake -S /src/drogon -B /tmp/drogon-build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/drogon \
        -DBUILD_CTL=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_ORM=ON \
        -DBUILD_POSTGRESQL=ON \
        -DBUILD_MYSQL=OFF \
        -DBUILD_SQLITE=OFF \
        -DBUILD_REDIS=OFF \
        -DBUILD_YAML_CONFIG=OFF \
        -DBUILD_BROTLI=OFF \
        -DBUILD_TESTING=OFF \
    && /usr/bin/cmake --build /tmp/drogon-build --parallel \
    && /usr/bin/cmake --install /tmp/drogon-build

# Switch to CMake 4
ENV PATH="/opt/cmake/bin:${PATH}"

# Stage 2: build the application

FROM drogon-builder AS truck-dispatch-builder

COPY truck-dispatch/ /src/truck-dispatch/

WORKDIR /src/truck-dispatch/script

RUN cmake --version

# Allow older dependency configs to work with CMake 4
RUN ./configw \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
    -DTrantor_DIR=/opt/drogon/lib/cmake/Trantor \
    -DBUILD_TESTING=OFF

RUN ./buildw

# Stage 3: build thin image


FROM debian:bookworm-slim AS runtime

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        libssl3 \
        libjsoncpp25 \
        libuuid1 \
        libpq5 \
        zlib1g \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=truck-dispatch-builder \
    /src/truck-dispatch/build/truck-dispatch \
    /app/truck-dispatch

EXPOSE 3080

ENTRYPOINT ["/app/truck-dispatch"]



