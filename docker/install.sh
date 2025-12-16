#!/bin/sh

set -e

# Constants
ID='io.github.mfdgaming.Ninecraft'
NAME='ninecraft'

# Paths
DATA_ROOT="${HOME}/.local/share"
APK_ROOT="$(pwd)"
SRC_ROOT="$(realpath "$(dirname "$0")")"
. "${SRC_ROOT}/common.sh"

# Arguments
ARCH="$1"
validate_arch

# Generate Launcher Script
info 'Creating Launcher...'
BIN_DIR="${HOME}/.local/bin"
mkdir -p "${BIN_DIR}"
SHORT_BIN_PATH="${BIN_DIR}/${NAME}"
LONG_BIN_PATH="${SHORT_BIN_PATH}-${ARCH}"
cat > "${LONG_BIN_PATH}" <<EOF
#!/bin/sh
set -e
exec "${SRC_ROOT}/run.sh" "${ARCH}"
EOF
chmod +x "${LONG_BIN_PATH}"
ln -sf "${LONG_BIN_PATH}" "${SHORT_BIN_PATH}"

# Copy Icon
ICON_SRC="${APK_ROOT}/res/drawable/iconx.png"
if [ ! -f "${ICON_SRC}" ]; then
    info 'Skipping Desktop Entry'
    exit 0
fi
info 'Copying Icon...'
ICON_DIR="${DATA_ROOT}/icons/hicolor/512x512/apps"
mkdir -p "${ICON_DIR}"
ICON_DST="${ICON_DIR}/${ID}.png"
cp "${ICON_SRC}" "${ICON_DST}"

# Generate Desktop Entry
info 'Creating Desktop Entry...'
APPS_DIR="${DATA_ROOT}/applications"
mkdir -p "${APPS_DIR}"
cat > "${APPS_DIR}/${ID}.desktop" <<EOF
[Desktop Entry]
Name=Ninecraft
Comment=An MCPE Launcher
Icon=${ICON_DST}
Path=${APK_ROOT}
Exec=${LONG_BIN_PATH}
Type=Application
Categories=Game;
Terminal=false
StartupNotify=false
StartupWMClass=ninecraft
EOF
update-desktop-database "${APPS_DIR}"
