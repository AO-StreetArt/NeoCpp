#!/bin/bash
set -e
#This script will attempt to build AOSSL dependencies

#Based on CentOS 7

printf "Creating Dependency Folder"
PRE=./downloads
mkdir $PRE

printf "Calling yum update"

#Update the Server
yum -y update

#Build the dependencies and place them in the correct places

printf "Addressing pre-build requirements"

#Ensure that specific build requirements are satisfied
yum -y install build-essential libtool pkg-config autoconf automake cmake make git wget gcc gcc-c++ epel-release
yum repolist

#Determine if we need the neo4j-client library
printf "Building libneo4j"

mkdir $PRE/neo
wget https://github.com/cleishm/libneo4j-client/releases/download/v2.1.3/libneo4j-client-2.1.3.tar.gz -P ./$PRE
tar -zxvf $PRE/libneo4j-client-2.1.3.tar.gz -C $PRE/neo
cd $PRE/neo/libneo4j-client-2.1.3 && ./configure --disable-tools --without-tls && make clean check && make install

printf "Finished installing dependencies"
