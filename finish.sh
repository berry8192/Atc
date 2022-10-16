#!/bin/sh

echo "git add $1"
git add $1
echo "git commit -m $1"
git commit -m $1
echo "git push -u origin $1"
git push -u origin $1
echo "cd /home/berry/prj/Atc"
cd /home/berry/prj/Atc
sleep 1

echo "waiting PRmerge"
read tmp
echo "git co master"
git co master
echo "git pull"
git pull