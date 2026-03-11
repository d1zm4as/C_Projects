#!/bin/bash

usage() {
    >&2 echo "Usage: $0 <project>"
}

pname="$1"
pdir="./$pname"
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
tdir="$script_dir/templates"

if [ -z "$pname" ]; then
    usage
    exit 1
elif [ ! -d "$tdir" ]; then
    >&2 echo "Unable to find template dir: $tdir"
    exit 2
elif [ -d "$pdir" ]; then
    >&2 echo "Project dir already exists: $pdir"
    exit 3
fi

cur="$PWD"
cd "$tdir" || exit 2

echo "Please select a template"

select x in *; do
    template="$x"
    break
done

if [ -z "$template" ]; then
    >&2 echo "No template selected."
    exit 4
fi

mkdir -p "$pdir"
cp -R "$tdir/$template"/. "$pdir"/

# Replace placeholder names in files and contents
find "$pdir" -depth -name "*PROJECTNAME*" | while read -r path; do
    new_path="${path//PROJECTNAME/$pname}"
    if [ "$new_path" != "$path" ]; then
        mv "$path" "$new_path"
    fi
done

if command -v perl >/dev/null 2>&1; then
    perl -pi -e "s/PROJECTNAME/$pname/g" "$pdir"/* "$pdir"/**/* 2>/dev/null
else
    find "$pdir" -type f -print0 | xargs -0 sed -i "s/PROJECTNAME/$pname/g"
fi

cd "$cur" || exit 0
