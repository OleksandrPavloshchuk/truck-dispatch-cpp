#!/usr/bin/env bash

# parameter is a profile: dev | test | prod

ENV_FILE="$(dirname "${BASH_SOURCE[0]}")/../.env.$1"

if [[ ! -f "$ENV_FILE" ]]; then
    echo "Missing environment file: $ENV_FILE" >&2
    exit 1
fi

set -a
source "$ENV_FILE"
set +a
