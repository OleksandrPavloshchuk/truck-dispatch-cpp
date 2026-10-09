#!/usr/bin/env bash

set -euo pipefail

#set -x

source "$(dirname "$0")/env.sh" dev

: "${DB_HOST:?DB_HOST is not set}"
: "${DB_PORT:?DB_PORT is not set}"
: "${DB_DATABASE:?DB_DATABASE is not set}"
: "${DB_USER:?DB_USER is not set}"
: "${DB_ADMIN:?DB_ADMIN is not set}"
: "${DB_PASSWORD:?DB_PASSWORD is not set}"

psql \
  -h "$DB_HOST" \
  -p "$DB_PORT" \
  -U "$DB_ADMIN" \
  -d "$DB_DATABASE" \
  -v app_user="$DB_USER" \
  -v app_password="$DB_PASSWORD" \
  -f "$(dirname "$0")/../sql/init.sql"
