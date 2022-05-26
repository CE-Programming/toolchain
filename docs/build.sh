#!/bin/bash

build_documentation () {
  export current_version
  export versions

  cp -f /tmp/conf.py conf.py
  local format="${2:-html}"

  echo "Building documentation for ${current_version}..."

  if [ -f 'templates/versions.html' ]; then
    cp -f /tmp/versions.html templates/versions.html
    sphinx-build -b "$format" . $1
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

# Maps target directory name to branch
declare -A versions_map=(
	[v10.0]=v10.0-docs
	[v9.2]=v9.2-docs
	[v9.1]=v9.1
	[v9.0]=v9.0
	[master]=master
)

# Pointers to other versions in the output documentation
export versions="${!versions_map[@]}"

# Also build the latest version at the root (which shouldn't be listed
# in the list of versions since it duplicates the chosen one).
default_version=v10.0
versions_map[.]="${versions_map[$default_version]}"

for target_dir in "${!versions_map[@]}"
do
	branch_name="${versions_map[$target_dir]}"
	git checkout "${branch_name}"
	for format in html singlehtml
	do
		if [ "${target_dir}" = "." ]; then
			current_version="${default_version}"
		else
			current_version="${target_dir}"
		fi
		build_documentation "build/${format}/${target_dir}" "${format}" &
	done
	# Each format is run in parallel, but we need to wait for completion before
	# checking out the next branch.
	wait
done

