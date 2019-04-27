#!/bin/bash

set -ex

# Pull requests and commits to other branches shouldn't try to deploy, just build to verify
if [ "$TRAVIS_PULL_REQUEST" != "false" -o "$TRAVIS_BRANCH" != "master" ]; then
    echo -e "Skipping deploy actions; just doing a build.\n"
    exit 0
fi

# Only perform below actions on a tagged (release) commit
git describe --exact-match --tags HEAD || exit 0

rev=$(git rev-parse --short HEAD)

git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

# Deploy latest tested_funcs into wiki
cd ${TRAVIS_BUILD_DIR}/tools/funcs_tested
git clone --depth 1 https://github.com/CE-Programming/toolchain.wiki.git
cd toolchain.wiki
if ! cmp ../tested-functions-list.md ./Tested-functions-list.md >/dev/null 2>&1
then
    git remote add upstream "https://$GH_TOKEN@github.com/CE-Programming/toolchain.wiki.git"
    git fetch upstream && git reset upstream/master
    cp ../tested-functions-list.md ./Tested-functions-list.md
    git add ./Tested-functions-list.md
    git commit -m "update tested functions list"
    git push -q upstream HEAD:master
fi

# Deploy updated docs
cd ${TRAVIS_BUILD_DIR}/doxygen/html
git init
git remote add upstream "https://$GH_TOKEN@github.com/CE-Programming/toolchain.git"
git fetch upstream && git reset upstream/gh-pages
touch .
git add -A .
git commit -m "rebuild pages at ${rev}"
git push -q upstream HEAD:gh-pages

