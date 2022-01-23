#!/bin/bash

build_documentation () {
  export current_version
  cp -f /tmp/conf.py conf.py

  echo "Building documentation for ${current_version}..."

  if [ -f 'templates/versions.html' ]; then
    cp -f /tmp/versions.html templates/versions.html
    sphinx-build . $1
    git checkout -- templates/versions.html
  else
    mkdir -p templates
    cp -f /tmp/versions.html templates/versions.html
    sphinx-build . $1
    rm -rf templates
  fi
  git checkout -- conf.py
}

cp -f conf.py /tmp/conf.py
cp -f templates/versions.html /tmp/versions.html

export versions="master v9.2 v9.1 v9.0"

# build default
current_version="v9.2"
git checkout v9.2-docs
build_documentation build/html

# build v9.2
current_version="v9.2"
git checkout v9.2-docs
build_documentation build/html/${current_version}

# build v9.1
current_version="v9.1"
git checkout v9.1
build_documentation build/html/${current_version}

# build v9.0
current_version="v9.0"
git checkout v9.0
build_documentation build/html/${current_version}

# build master
current_version="master"
git checkout master
build_documentation build/html/${current_version}

