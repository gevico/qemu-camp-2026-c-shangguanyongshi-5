#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
MYBASH="${REPO_ROOT}/exercises/20_mybash/bin/mybash"
CMD_FILE="${SCRIPT_DIR}/mybash_cmd.sh"
exec "${MYBASH}" "${CMD_FILE}"
