#!/bin/sh

# only supported on unix systems

if [[ $EUID -ne 0 ]]; then
    echo "This script must be ran as root (sudo ...)"
    exit 1
fi

sudo cp sh/pytocpp /usr/local/bin/pytocpp
sudo chmod +x /usr/local/bin/pytocpp
export PATH="/usr/local/bin":$PATH

exit 1