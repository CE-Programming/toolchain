#!/bin/bash

set -o errexit

# Pull requests and commits to other branches shouldn't try to deploy, just build to verify
if [ "$TRAVIS_PULL_REQUEST" != "false" -o "$TRAVIS_BRANCH" != "master" ]; then
    echo -e "Skipping doc deploy; just doing a build.\n"
    exit 0
fi

rev=$(git rev-parse --short HEAD)

cd doxygen/html

git init
git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

git remote add upstream "https://$GH_TOKEN@github.com/CE-Programming/toolchain.git"
git fetch upstream && git reset upstream/gh-pages

touch .

git add -A .
git commit -m "rebuild pages at ${rev}"
git push -q upstream HEAD:gh-pages
