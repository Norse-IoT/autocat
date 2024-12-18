#! /bin/bash
# https://gist.githubusercontent.com/olasd/9841772/raw/12c78a9426af9102e7c3fe40652c96f3c793aa9d/stream_to_youtube.sh
#
# Diffusion youtube avec ffmpeg
# THIS DOESN'T WORK FOR SOME REASON

VBR="2500k"
FPS="30"
QUAL="medium"
YOUTUBE_URL="rtmp://a.rtmp.youtube.com/live2"

SOURCE="/dev/video0"

if [[ -z "$KEY" ]]; then
    echo "Must provide KEY in environment" 1>&2
    exit 1
fi

ffmpeg \
    -i "$SOURCE" \
    -vcodec  -pix_fmt yuv420p -preset $QUAL -r $FPS -g $(($FPS * 2)) -b:v $VBR \
    -acodec libmp3lame -ar 44100 -threads 6 -b:a 712000 -bufsize 512k \
    -f flv "$YOUTUBE_URL/$KEY"
