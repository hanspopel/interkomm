# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# please run main build.sh script in root folder - do not call directly!


#echo "#######      OSX Build was called from $PWD"

if [ "$BUILD_PROJECTS_STUDIOMUX" == TRUE ]
	then
		:
	else
		echo "#######      ERROR | build_projects.sh line 11: Please do not call this script directly. To build, please call build.sh in root TA folder. $BUILD_OSX" 
		exit 1
fi

#DEPLOY=ON

#if [ "$USERNAME" == "pascalkaap" ] || [ "$USERNAME" == "cblomert" ] || [ "$USERNAME" == "christianblomert" ] || [ "$USERNAME" == "pascal" ] 
#    echo "#######      Activating direct deployment to LV1" 2>&1 | tee -a $ROOT_FOLDER_TA/build.log
#    #DEPLOY=OFF 
#fi



cmake -DDEPLOY:BOOL=$DEPLOY -DTEAMID:STRING=$CODESIGN_TEAM_ID_TA -DBUNDLEID:STRING=$CODESIGN_BUNDLE_ID_TA -DBUILD_NUMBER:STRING=$BUILD_NUMBER -DVERSION:STRING=$VERSION ../../source/plugins/cmake/osx -GXcode -B"../../build/plugins"



# create XCode project structures with XCode Generator
# set CODESIGN_TEAM_ID_TA in build.cfg
# set CODESIGN_BUNDLE_ID_TA in build.cfg
echo "#######      Configuring XCode Projects with TeamID: $CODESIGN_TEAM_ID_STUDIOMUX BundleID: $CODESIGN_BUNDLE_ID_STUDIOMUXå"
cmake -DDEPLOY:BOOL=$DEPLOY -DTEAMID:STRING=$CODESIGN_TEAM_ID_STUDIOMUX -DBUNDLEID:STRING=$CODESIGN_BUNDLE_ID_STUDIOMUX -DBUILD_NUMBER:STRING=$BUILD_NUMBER -DVERSION:STRING=$VERSION ../../source -GXcode 

RESULT=$?


if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: creating XCode projects failed"
	exit 1
else
	echo "#######      SUCCESS: created XCode projects"
fi

