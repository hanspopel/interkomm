# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# please run main build.sh script in root folder - do not call directly!


#echo "#######      Build ALL was called from $PWD"

if [ "$BUILD_ALL_TA" == "TRUE" ]
	then
		:
	else
		echo "#######      ERROR: Please do not call this script directly. To build, please call build.sh in root TA folder." 
		exit 1
fi




cd $ROOT_FOLDER_TA/build/osx

export BUILD_OSX_TA=TRUE
../../source/scripts/build_osx.sh
RESULT=$?

if [ "$RESULT" != "0" ]
	then
		exit 1
else
	:
fi
export BUILD_OSX_TA=FALSE






cd $ROOT_FOLDER_TA/build/osx
export BUILD_IOS_TA=TRUE
../../source/scripts/build_ios.sh
RESULT=$?

if [ "$RESULT" != "0" ]
	then
		exit 1
else
	:
fi
export BUILD_IOS_TA=FALSE






cd $ROOT_FOLDER_TA
export BUILD_ANDROID_TA=TRUE
./source/scripts/build_android.sh
RESULT=$?

if [ "$RESULT" != "0" ]
	then
		exit 1
else
	:
fi
export BUILD_ANDROID_TA=FALSE


