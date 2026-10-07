#!/usr/bin/env bash

set -x

source "$(dirname "$0")/env.sh" dev

JSON=$(printf '{"name":"%s","weight":%f}' "$1" "$2")

curl -X POST \
  -H "Content-Type: application/json" \
  -d $JSON \
  "http://localhost:$HTTP_PORT/td/shipment"
