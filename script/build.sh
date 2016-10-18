#!/bin/bash

CMAKE_BUILD_TYPE=Debug
COVERAGE=0
CMAKE_ARGS=""

while [ -n "$*" ]
do
  case "$1" in
    -debug)
      CMAKE_ARGS+=" -DCMAKE_BUILD_TYPE=DEBUG"
      ;;
    -release)
      CMAKE_ARGS+=" -DCMAKE_BUILD_TYPE=RELEASE"
      ;;
    -coverage_debug)
      CMAKE_ARGS+=" -DCMAKE_BUILD_TYPE=COVERAGE_DEBUG"
      ;;
    -coverage_release)
      CMAKE_ARGS+=" -DCMAKE_BUILD_TYPE=COVERAGE_RELEASE"
      ;;
    -help|*)
      echo "help ... TODO ...."
      exit 1
      ;;
    esac
  shift;
done

cur_dir=$(pwd)
script_dir=$(cd `dirname $0`; pwd)
cd $script_dir
cd ../
project_path=$(pwd)
cd $cur_dir
cmake -H$project_path/src -B$project_path/build ${CMAKE_ARGS}

