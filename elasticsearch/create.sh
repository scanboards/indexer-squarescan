#!/bin/bash

# Elasticsearch credentials
USERNAME="elastic"
PASSWORD="changeme"

# Elasticsearch host
HOST="localhost:9200"

# Path to the mappings file
MAPPINGS_FILE="mappings.json"

# Check if the mappings file exists
if [ ! -f "$MAPPINGS_FILE" ]; then
    echo "Mappings file $MAPPINGS_FILE does not exist."
    exit 1
fi

# Load the mapping JSON from the mappings file
MAPPING_JSON=$(cat "$MAPPINGS_FILE")

# Starting year
START_YEAR=2023

# Number of years to process
YEARS=7

# Generate indices for each year and month
for (( YEAR=START_YEAR; YEAR<START_YEAR+YEARS; YEAR++ )); do
    for MONTH in {01..12}; do

        if (( MONTH >= 1 && MONTH <= 9 )); then
            FORMATTED_MONTH="0${MONTH}"
        else
            FORMATTED_MONTH="${MONTH}"
        fi

        INDEX_NAME="search-rsquared-${YEAR}-${FORMATTED_MONTH}"

        echo "Processing $INDEX_NAME..."
        curl -u "$USERNAME:$PASSWORD" -X PUT "$HOST/$INDEX_NAME" \
             -H 'Content-Type: application/json' \
             -d"$MAPPING_JSON"
    done
done