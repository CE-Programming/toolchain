#!/bin/bash

# Default toolchain docs (should be latest release!)
export default_version=v14.2

# Maps target directory name to branch
declare -A versions_map=(
	[v14.2]=v14.2
	[v14.1]=v14.1
	[v14.0]=v14.0
	[v13.0]=v13.0
	[v12.1]=v12.1-docs
	[v12.0]=v12.0
	[v11.2]=v11.2-docs
	[v11.1]=v11.1-docs
	[v11.0]=v11.0-docs
	[v10.2]=v10.2-docs
	[v10.1]=v10.1-docs
	[v10.0]=v10.0-docs
	[v9.2]=v9.2-docs
	[v9.1]=v9.1
	[v9.0]=v9.0
	[nightly]=master
)

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

# Pointers to other versions in the output documentation
export versions="${!versions_map[@]}"

# Also build the latest version at the root (which shouldn't be listed
# in the list of versions since it duplicates the chosen one).
versions_map[.]="${versions_map[$default_version]}"

for target_dir in "${!versions_map[@]}"
do
	branch_name="${versions_map[$target_dir]}"
	git checkout "${branch_name}"
	for format in html
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

