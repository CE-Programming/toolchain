#!/bin/bash

set -o errexit

rev=$(git rev-parse --short HEAD)

cd doxygen/html

git init
git config user.name "travis"
git config user.email "travis"

git remote add upstream "https://$GH_TOKEN@github.com/CE-Programming/toolchain.git"
git fetch upstream && git reset upstream/gh-pages

touch .

git add -A .
git commit -m "rebuild pages at ${rev}"
git push -q upstream HEAD:gh-pages
