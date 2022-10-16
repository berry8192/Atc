#!/bin/sh

echo "cd /home/berry/prj/Atc"
cd /home/berry/prj/Atc
sleep 1
echo "git co -b $1"
git co -b $1
echo "cp -r abctmp $1"
cp -r abctmp $1
sleep 1
echo "cd $1"
cd $1