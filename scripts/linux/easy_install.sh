#!/bin/bash
#This script will install the pre-packaged release of AOSSL

if [ "$#" -ne 1 ]; then
  printf "Attempting to install dependencies"

  #Install the dependencies
  printf "This will install multiple libraries to your system.  This may pull development versions."
  printf "You may find the source code for this application, and the licenses for all dependencies at https://github.com/AO-StreetArt/NeoCpp"
  printf "Do you wish to continue? [y/n]:"
  read deps_confirm
  if [deps_confirm = 'y']; then
    #Install the dependencies
    cd ./deps && sudo ./build_deps.sh

    printf "Attempting to install core library"

    # Install the library
    cd ../ && sudo cp -r usr/local/include/neocpp /usr/local/include/

    printf "Finished installing NeoCpp"
  fi

else
  OPT=$1
  if [ $OPT = "-r" ]
  then
    printf "Attempting to uninstall core library"
    sudo rm -r /usr/local/include/neocpp/
    printf "Finished uninstalling NeoCpp"
  fi
fi
