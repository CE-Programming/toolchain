#!/bin/bash

read -t 20 -p "Warning!! This will force-checkout branches! Press ENTER to cancel now."

current_version="v9.1"
versions="master v9.1 v9.0"

export versions
export current_version

git checkout -f ${current_version}
git clean -fxd

sphinx-build . build/html

for current_version in ${versions}; do
 
   export current_version
   git checkout -f ${current_version}
   git clean -fxd

   echo "Building documentation for ${current_version}..."

   if [ ! -e 'conf.py' ]; then
      continue
   fi

   sphinx-build . build/html/${current_version}

done
