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
yum -y install build-essential libtool pkg-config autoconf automake cmake make git wget gcc gcc-c++ epel-release openssl openssl-devel
yum repolist

#Determine if we need the neo4j-client library
printf "Building libneo4j"
wget https://github.com/cleishm/libneo4j-client/releases/download/v2.2.0/libneo4j-client-2.2.0.tar.gz
tar -xvzf libneo4j-client-2.2.0.tar.gz
cd libneo4j-client-2.2.0 && ./configure --disable-tools && make && make install
#cd /etc/yum.repos.d/ && sudo wget https://download.opensuse.org/repositories/home:cleishm/CentOS_7/home:cleishm.repo
#sudo yum -y install libneo4j-client libneo4j-client-devel

printf "Finished installing dependencies"
