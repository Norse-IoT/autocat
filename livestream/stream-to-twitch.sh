#!/bin/bash

KEY=live_XXXXXX

function startVLCForSomeReason() {
        ls
}

function realSignal() {
        ffmpeg -re -f v4l2 -i /dev/video0 -f v4l2 \
                -c:v libx264 -preset veryfast -b:v 6000k \
                -maxrate 6000k -bufsize 6000k -pix_fmt yuv420p \
                -g 50 -c:a aac -b:a 160k -ac 2 -ar 44100 \
                -f flv "rtmp://live-fra.twitch.tv/app/$KEY"
}

function testSignal() {
        ffmpeg -re \
                -f lavfi -i testsrc2=size=960x540 \
                -f lavfi -i aevalsrc="sin(0*2*PI*t)" \
                -vcodec libx264 \
                -r 30 -g 30 \
                -preset fast -vb 3000k -pix_fmt rgb24 \
                -pix_fmt yuv420p \
                -f flv "rtmp://live-fra.twitch.tv/app/$KEY"
}

realSignal


