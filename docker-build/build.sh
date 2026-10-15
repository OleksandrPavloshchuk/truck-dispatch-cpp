#!/usr/bin/env bash

set -x

docker build --progress=plain -t truck-dispatch:dev .
