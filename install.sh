#!/bin/bash

# only supported on unix systems

echo "Warning: Rerunning this script might produce duplicate lines in ~/.bashrc. Proceed? (Y/n): "
read proceed

if [ ! "$proceed" = "Y" ]; then
    exit 0
fi

if [[ $EUID -ne 0 ]]; then
    echo "This script must be ran as root (sudo ...)"
    exit 1
fi

sudo cp sh/pytocpp /usr/local/bin/pytocpp
sudo chmod +x /usr/local/bin/pytocpp
export PATH="/usr/local/bin":$PATH

if [ ! -e ~/.bashrc ]; then
    touch ~/.bashrc
fi

echo "export PYTOCPP_PATH=\"$PWD\"" >> ~/.bashrc

exit 1