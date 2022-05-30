#!/bin/sh
while IFS= read -r line; do
    set -- $line
    if [ $# -eq 4 ] && [ "$1x$4" = @x@ ]; then
        find "$3" -name '*.src' -printf "`printf %s "$line" | cut -d@ -f1`$2 \"../lib/$3/%f\"\n" | sort
    else
        echo "$line"
    fi
done < "$1"
