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
cd /etc/yum.repos.d/ && sudo wget https://download.opensuse.org/repositories/home:cleishm/CentOS_7/home:cleishm.repo
sudo yum install libneo4j-client

printf "Finished installing dependencies"
