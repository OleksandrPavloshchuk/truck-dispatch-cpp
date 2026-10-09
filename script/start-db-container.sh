
#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

ENV_FILE="$PROJECT_DIR/.env.dev"
COMPOSE_FILE="$PROJECT_DIR/docker/docker-compose.yaml"

if [[ ! -f "$ENV_FILE" ]]; then
    echo "Environment file not found: $ENV_FILE" >&2
    exit 1
fi

docker compose \
    --env-file "$ENV_FILE" \
    -f "$COMPOSE_FILE" \
    up -d
