#!/usr/bin/env bash
set -e

YELLOW="\033[1;33m"
RED="\033[1;31m"
GREEN="\033[1;32m"
RESET="\033[0m"

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <part>"
    echo "Example: $0 part1"
    exit 1
fi

PART="$1"
MEM="build/$PART/main.mem"
DUMP="build/$PART/main.dump"

if [[ ! -f "$MEM" ]]; then
    echo -e "${RED}Error: $MEM not found. Run 'make $PART' first.${RESET}"
    exit 1
fi

echo -e "${YELLOW}==> Running $PART ...${RESET}"
echo "----------------------------------------"

stop_pc=""
# stop_pc_hex=$(grep '<write_tohost>:' "$DUMP" | awk '{print $1}' || true)
stop_pc_hex=$(grep '<write_tohost>:' "$DUMP" | cut -c 2-8 || true)


if [[ -n "$stop_pc_hex" ]]; then
    stop_pc=$(printf "%d" "0x$stop_pc_hex")
fi

if [[ -n "$stop_pc" ]]; then
    out=$(./obj_dir/VComputer "$MEM" "$stop_pc")
else
    out=$(./obj_dir/VComputer "$MEM")
fi

serial_out=$(echo "$out" | head -c -5)

if [[ -n "$serial_out" ]]; then
    echo -e "Serial output:"
    echo "$serial_out"
    echo ""
fi

echo "----------------------------------------"
echo -e "${GREEN}Done${RESET}"