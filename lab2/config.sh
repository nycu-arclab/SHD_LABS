#!/bin/bash

# Debug settings
DEBUG_HOST=localhost
DEBUG_PORT=5050

# Get target binary from part name
get_target() {
    echo "build/$1"
}