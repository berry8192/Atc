#!/bin/sh

echo "git co -b $1" && echo "cp -r abctmp $1" && cp -r abctmp $1 && echo "cd $1"