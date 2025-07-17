#!/bin/sh 

# 1. Ensure pacman dirs exist
mkdir -p /etc/pacman.d /var/lib/pacman /var/cache/pacman/pkg

# 2. Create a minimal pacman.conf
tee /etc/pacman.conf > /dev/null <<EOF
[options]
Architecture = auto
SigLevel = Required DatabaseOptional
LocalFileSigLevel = Optional
CheckSpace

[core]
Server = https://mirror.rackspace.com/archlinux/\$repo/os/\$arch

[extra]
Server = https://mirror.rackspace.com/archlinux/\$repo/os/\$arch

[community]
Server = https://mirror.rackspace.com/archlinux/\$repo/os/\$arch
EOF

# 3. Initialize and populate keyring (force reinstall in case of damage)
pacman-key --init
pacman -Syy
pacman-key --populate archlinux || true
pacman -Sy --noconfirm archlinux-keyring || true

# 4. Sync the pacman database
pacman -Syy --noconfirm

# 5. Optional: install test packages
pacman -S --noconfirm git base-devel
