#!/bin/bash
# Adrien 'Adriweb' Bertrand
# Tool to generate a list of things that are used/tested in the toolchain example codes.
# Dependencies: universal-ctags

set -e

# Grab current path
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Let's go back to the root of the toolchain
cd $DIR/../../

# All header files we want to extract prototypes from
files="src/fileioc/fileioc.h src/graphx/graphx.h src/keypadc/keypadc.h src/ce/tice.h src/ce/decompress.h src/ce/debug.h"

# The destination markdown file
outfile=$DIR/tested-functions-list.md

echo "## List of tested functions" > $outfile

for f in $files
do
    echo -e "\n### $f" >> $outfile
    echo -e "| Function | Tested ?    |" >> $outfile
    echo -e "| -------- | ----------- |" >> $outfile
    filectags=$(ctags -u --fields=n --c-kinds=p --output-format=json $f | sed -e 's/.*"name": "\(.*\)", "path.*/\1/g')
    for c in $filectags
    do
        grep -Rq --include \*.h --include \*.cpp --include \*.h --include \*.c "$c" ./examples && found="<span style='color:green'>✓</span>" || found="<span style='color:red'>✗</span>"
        echo "| \`$c\` | $found |" >> $outfile
    done
done

cat $outfile
