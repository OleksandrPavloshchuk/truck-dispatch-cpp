# Truck Dispatch Task

## Technologies and frameworks

* C++
* [Drogon](https://github.com/drogonframework/drogon)
* REST API
* PostgreSQL

## Database setup

### Configuration

Create `.env.dev` in the project root. Use `.env.example` as a template and set local credentials.

Available profiles:

* `.env.dev` — local development
* `.env.prod` — production

Do not commit `.env.dev` or other files containing secrets.

### Start the database container

```shell
./script/start-db-container.sh
```

### Initialize the database

Run this after starting PostgreSQL, when creating the schema for the first time or intentionally rebuilding it:

```shell
./script/init-db.sh
```

**Note:** The initialization script drops and recreates application tables and the `td_app` role. Do not run it if you need to preserve existing data.

### Connect to the database

```shell
psql --host=localhost --port=15432 --username=td_admin --dbname=trucksdispatch
```

### Stop the database container

From the project root:

```shell
docker compose --env-file .env.dev -f docker/compose.yaml down
```

### Stop the container and delete database data

**Warning:** This removes the PostgreSQL volume and permanently deletes its stored data.

```shell
docker compose --env-file .env.dev -f docker/compose.yaml down -v
```

## Configuration

### Environment variables

| Variable            | Description                                            |
| ------------------- | ------------------------------------------------------ |
| `HTTP_PORT`         | HTTP server port                                       |
| `DB_HOST`           | Database host used by the application                  |
| `DB_PORT`           | Database port used by the application                  |
| `DB_DATABASE`       | Database name                                          |
| `DB_USER`           | Application database user                              |
| `DB_ADMIN`          | Database administrator user                            |
| `DB_PASSWORD`       | Application database user's password                   |
| `POSTGRES_PORT`     | Host port mapped to PostgreSQL's container port `5432` |
| `POSTGRES_USER`     | Initial PostgreSQL administrator role                  |
| `POSTGRES_PASSWORD` | Initial administrator password                         |
| `POSTGRES_DB`       | Database created during first initialization           |

`POSTGRES_USER`, `POSTGRES_PASSWORD`, and `POSTGRES_DB` are used by the PostgreSQL image when initializing an empty data directory. Changing these values does not automatically modify roles, passwords, or databases in an existing PostgreSQL volume.

