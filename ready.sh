#!/bin/sh

git co -b $1 && cp -r abctmp $1
sleep 1
cd $1 && cp A.cc B.cc && cp A.cc C.cc && cp A.cc D.cc && cp A.cc E.cc && cp A.cc F.cc && cp A.cc G.cc