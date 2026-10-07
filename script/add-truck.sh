#!/usr/bin/env bash

set -x

source "$(dirname "$0")/env.sh" dev

JSON=$(printf '{"name":"%s","capacity":%f}' "$1" "$2")

curl -X POST \
  -H "Content-Type: application/json" \
  -d "$JSON" \
  "http://localhost:$HTTP_PORT/td/truck"
