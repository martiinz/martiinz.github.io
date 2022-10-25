---
title: "Bash script Template"
excerpt: ""
tags:
  - linux
  - bash
categories:
  - linux
---

A little copy paste example for new script

```bash
#!/bin/bash

OPTIND=1         # Reset getopts

PLATFORM="x86"
CLEAN_ONLY=""

# read commandline options
while getopts "ha:c" opt; do
    case "$opt" in
    a)  PLATFORM="$OPTARG"
        ;;
    c)  CLEAN_ONLY="clean"
        ;;
    *)
        echo "script description"
        echo "example call: ./$(basename $0) -a x86 -p -r 1.1.5"
        echo "    -a archidecture is one of [amd64|x86]"
        echo "    -c clean, will remove build folder for given archidecture"
        echo "    -h show help"
        exit 1
        ;;
   esac
done

main(){
    if [[ "$CLEAN_ONLY" == "" ]]; then
        build $PLATFORM
    else
        clean
    fi
}

clean(){
    echo "-- *** clean ***"
}

# fucntion with parameter
build(){
    echo "-- *** build for platform $1 ***"
}

# run main function
main "$@"
```
