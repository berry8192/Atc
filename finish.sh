#!/bin/sh

git add $1 && git commit -m $1 && git push -u origin $1
echo "waiting PRmerge"
read tmp
git co main && git pull