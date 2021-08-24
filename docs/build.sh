#!/bin/bash

build_documentation () {
   export current_version
   git checkout ${current_version}
   cp -f /tmp/conf.py.master conf.py
   mkdir -p templates
   cp -f /tmp/versions.html templates

   echo "Building documentation for ${current_version}..."

   if [ ! -e 'conf.py' ]; then
      continue
   fi

   sphinx-build . build/html/${current_version}

   git checkout -- conf.py templates/
}

current_version="v9.1"
export versions="master v9.1 v9.0"

cp -f conf.py /tmp/conf.py.master
cp -f templates/versions.html /tmp/versions.html

build_documentation
for current_version in ${versions}; do
  build_documentation
done
