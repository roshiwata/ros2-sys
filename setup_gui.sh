#!/bin/bash

# X11 GUI setup script for Docker
echo "Setting up X11 GUI support for Docker..."

# Create X11 authentication file
XAUTH=/tmp/.docker.xauth
if [ ! -f $XAUTH ]; then
    xauth_list=$(xauth nlist $DISPLAY 2>/dev/null | sed -e 's/^..../ffff/')
    if [ ! -z "$xauth_list" ]; then
        echo $xauth_list | xauth -f $XAUTH nmerge -
    else
        touch $XAUTH
    fi
    chmod a+r $XAUTH
fi

# Allow X11 forwarding
xhost +local:docker

# Set display variable if not set
if [ -z "$DISPLAY" ]; then
    export DISPLAY=:0
fi

echo "X11 setup completed!"
echo "DISPLAY: $DISPLAY"
echo "XAUTH: $XAUTH"

# Test X11 connection
echo "Testing X11 connection..."
if command -v xeyes &> /dev/null; then
    timeout 2 xeyes &
    sleep 1
    pkill xeyes
    echo "X11 test completed"
else
    echo "xeyes not found, installing x11-apps..."
    sudo apt-get update && sudo apt-get install -y x11-apps
fi
