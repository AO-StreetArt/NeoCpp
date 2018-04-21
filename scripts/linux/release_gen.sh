#!/bin/bash
#This script will generate release bundles for NeoCpp

if [ "$#" -ne 3 ]; then
    echo "The correct usage of this script is './release_gen.sh release-name release-version release-type'"
    echo "release_version should be in the format: major.minor-revision"
    echo "release-type can be: 'deb', 'deb-zip', or 'rhel-zip'"
    exit 64
fi

RELEASE_NAME=$1
RELEASE_VERSION=$2
RELEASE_TYPE=$3

printf "Generating NeoCpp Release: $RELEASE_NAME - $RELEASE_VERSION - $RELEASE_TYPE\n"

HOME_FOLDER=../..
RELEASE_FOLDER_NAME=$RELEASE_NAME\_$RELEASE_VERSION
RELEASE_FOLDER=$HOME_FOLDER/../$RELEASE_FOLDER_NAME

#Generate the release folder & subfolders
printf "Generating Release Folder\n"
mkdir -p $RELEASE_FOLDER/usr/local/include

printf "Copying library into release folders\n"
cp -r $HOME_FOLDER/neocpp/ $RELEASE_FOLDER/usr/local/include/

if [ "$3" = "deb" ]; then
    mkdir $RELEASE_FOLDER/DEBIAN
    cp $HOME_FOLDER/scripts/linux/deb/control $RELEASE_FOLDER/DEBIAN/
    dpkg-deb --build $RELEASE_FOLDER

    printf "Script finished, release folders can be found at $RELEASE_FOLDER, deb file at $HOME_FOLDER/$RELEASE_FOLDER_NAME.deb\n"
else
    #We are generating tarballs and zips rather than .deb files
    #Determine our dependency script location
    if [ "$3" = "deb-zip" ]; then
        DEPS_SCRIPT_LOC=$HOME_FOLDER/linux/deb
    fi
    if [ "$3" = "rhel-zip" ]; then
        DEPS_SCRIPT_LOC=$HOME_FOLDER/linux/rhel
    fi

    mkdir $RELEASE_FOLDER/licenses
    mkdir -p $RELEASE_FOLDER/deps

    #Copy the dependency licenses into the licenses folder
    printf "Copying Licenses\n"
    cp $HOME_FOLDER/licenses/*.txt $RELEASE_FOLDER/licenses
    cp $HOME_FOLDER/LICENSE.txt $RELEASE_FOLDER

    #Copy the correct dependency script into the release subfolder 'deps'
    printf "Copying Dependencies script into release folders\n"
    cp $HOME_FOLDER/scripts/$DEPS_SCRIPT_LOC/build_deps.sh $RELEASE_FOLDER/deps

    #Documentation
    cp -r $HOME_FOLDER/docs $RELEASE_FOLDER

    #Copy the easy install script into the release folder
    cp $HOME_FOLDER/scripts/linux/easy_install.sh $RELEASE_FOLDER

    #Generate the Release tar files
    printf "Generate Release Tar Files\n"
    tar -czvf $RELEASE_FOLDER_NAME.tar.gz $RELEASE_FOLDER
    tar -cjvf $RELEASE_FOLDER_NAME.tar.bz2 $RELEASE_FOLDER
    zip -r $RELEASE_FOLDER_NAME.zip $RELEASE_FOLDER

    #Move the tar files outside the main git repository
    mv *.tar.* $HOME_FOLDER/../
    mv *.zip $HOME_FOLDER/../

    printf "Script finished, release folders can be found at $RELEASE_FOLDER, tar files at $HOME_FOLDER/../\n"
fi

exit 0
