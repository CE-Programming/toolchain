#!/bin/sh
while IFS= read -r line; do
    set -- $line
    if [ $# -eq 4 ] && [ $1x$4 = @x@ ]; then
        indent=`printf %s "$line" | cut -d@ -f1`
        find $3 \! -iname crt\* -iname \*.src | LC_ALL=C sort | while IFS= read -r file; do
            printf %s\\n "$indent$2 \"../lib/$3/`basename "$file"`\""
        done
    else
        printf %s\\n "$line"
    fi
done < "$1"
