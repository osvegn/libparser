#!/bin/bash

# Install Criterion from submodules/Criterion

ld -lcriterion
res=$?
dnf=$(which dnf)
apt=$(which apt-get)
yum=$(which yum)

if [ $res -ne 0 ]; then
    echo "Criterion is not installed"
    if [ -n "$dnf" ]; then
        sudo dnf install -y gcovr meson
    elif [ -n "$apt" ]; then
        sudo apt-get install -y gcovr meson
    elif [ -n "$yum" ]; then
        sudo yum install -y gcovr meson
    else
        echo "Error: no package manager found"
        exit 1
    fi
    cd submodules/Criterion
    meson build
    ninja -C build
    sudo ninja -C build install
else
    echo "Criterion is already installed"
fi
