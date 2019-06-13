#!/usr/bin/sh

# Commit to git repository
rm vgcore.*
rm *.txt
git add .
git commit -m "$(date)"
git push
