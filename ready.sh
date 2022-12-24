#!/bin/sh

git co -b $1 && cp -r abctmp $1 && cd $1