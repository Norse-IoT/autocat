#!/bin/bash

# using https://pypi.org/project/twitch-dl/
# (pipx install twitch-dl)

TWITCH_CHANNEL_NAME=norsecoderadio

twitch-dl videos "$TWITCH_CHANNEL_NAME" --all | grep https | sed 's/videos\// /' | awk '{print $2}' > ids.txt

