#!/bin/bash

build_documentation () {
   export current_version
   git checkout ${current_version}
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

current_version="v9.2"
export versions="master v9.2 v9.1 v9.0"

cp -f conf.py /tmp/conf.py
cp -f templates/versions.html /tmp/versions.html

build_documentation build/html
for current_version in ${versions}; do
  build_documentation build/html/${current_version}
done
