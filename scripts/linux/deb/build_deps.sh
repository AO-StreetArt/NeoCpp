#!/bin/bash
set -e
#This script will attempt to build neocpp dependencies

#Based on Ubuntu 16.04 LTS

printf "apt-get setup\n"
apt-get -y update

#Install the basic tools we need
apt-get install -y apt-utils debconf-utils iputils-ping wget curl mc htop ssh software-properties-common

#Add libneo4j repository
add-apt-repository ppa:cleishm/neo4j -y
apt-get -y -q update

printf "Installing apt-get dependencies"
apt-get -y -q install build-essential libtool pkg-config automake cmake libssl-dev openssl neo4j-client libneo4j-client-dev
printf "Finished installing dependencies"
