#!/usr/bin/env bash

set -x

JSON=$(printf '{"name":"%s","weight":%f}' "$1" "$2")

curl -X POST \
  -H "Content-Type: application/json" \
  -d $JSON \
  http://localhost:3080/td/shipment
