#!/bin/bash

if [ ! -d venv ];then
  python3 -m venv venv
  source venv/bin/activate
  pip3 install -r requirements.txt
fi

source venv/bin/activate

export default_version='v10.0'
export versions='v10.0 v9.2 v9.1 v9.0 nightly'
export current_version=$default_version

sphinx-build -b html . build/html

