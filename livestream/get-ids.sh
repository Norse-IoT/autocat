#!/bin/bash

TWITCH_CHANNEL_NAME=norsecoderadio

twitch-dl videos "$TWITCH_CHANNEL_NAME" --all | grep https | sed 's/videos\// /' | awk '{print $2}' > ids.txt

