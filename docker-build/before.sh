#!/usr/bin/env bash

set -Eeuo pipefail
set -x

DROGON_PATH="$HOME/personal/c++/libs/drogon"
DROGON_BUILD_DIR="drogon-build"
DROGON_INSTALL_DIR="drogon-install"

TRUCK_DISPATH_PATH="$HOME/personal/c++/truck-dispatch-cpp"

mkdir -p drogon
rsync -a --exclude='.git' "$DROGON_PATH/" drogon/

mkdir -p truck-dispatch
rsync -a \
	--exclude='.git' \
	--exclude='docker-build' \
	--exclude='build' \
	--exclude='build-test' \
	"$TRUCK_DISPATH_PATH/" truck-dispatch/

