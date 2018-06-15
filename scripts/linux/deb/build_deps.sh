#!/bin/bash
set -e
#This script will attempt to build neocpp dependencies
# The gcc-make build toolchain should be pre-installed

#Based on Ubuntu 16.04 LTS

printf "apt-get setup\n"
apt-get -y update

#Install the basic tools we need
apt-get install -y apt-utils debconf-utils iputils-ping wget curl mc htop ssh software-properties-common

#Add libneo4j repository
printf "Building libneo4j"
wget https://github.com/cleishm/libneo4j-client/releases/download/v2.2.0/libneo4j-client-2.2.0.tar.gz
tar -xvzf libneo4j-client-2.2.0.tar.gz
cd libneo4j-client-2.2.0 && ./configure --disable-tools && make && make install

printf "Installing apt-get dependencies"
apt-get -y -q install build-essential libtool pkg-config automake cmake libssl-dev openssl
printf "Finished installing dependencies"
