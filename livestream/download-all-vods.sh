#!/bin/bash

function twitch_download () {
	# This should represent the path to the binary:
	# https://github.com/lay295/TwitchDownloader
	/home/username/folder/TwitchDownloaderCLI "$@"
}

function setVideoDate() {
	twitch_download info  --id "$1" --format raw | grep createdAt | jq -r '.data.video.createdAt' | tr ':' '-'
}

# note the use of file descriptor 10 such that 
# the loop is seperate from the body.
while read -u 10 id; do
	echo "downloading $id..."
	videoDate="$(setVideoDate $id)"
	# Note that it's better to have the temp path on an SSD for better read/writes.
	# I have my output dir on a hard disk, for more storage.
	twitch_download videodownload --id "$id" --output "./vods/$id-$videoDate.mp4" --quality 720p --collision Exit --temp-path /home/username/Videos || echo "Error downloading $id. Skipping..."
	echo "done $id"
done 10<ids.txt




