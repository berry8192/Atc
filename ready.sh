#!/bin/sh

echo "cd /home/berry/prj/Atc"
cd /home/berry/prj/Atc
echo "git co -b $1"
git co -b $1
echo "cp -r abctmp $1"
cp -r abctmp $1
wait
echo "cd $1"
cd $1