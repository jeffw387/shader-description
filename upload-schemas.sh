#!/bin/bash
set -x

mkdir -p remote-dir
rm remote-dir/* -f
sshfs -p22 u96310048@access770913707.webspace-data.io:/schemas ./remote-dir
cp -f *.schema.json ./remote-dir
fusermount -u ./remote-dir