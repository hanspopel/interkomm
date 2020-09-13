# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# please run main build.sh script in root folder - do not call directly!


#echo "#######      Clean was called from $PWD"

if [ "$CLEAN_ALL_TA" == "TRUE" ]  || [ "$BUILD_ALL_TA" == "TRUE" ]|| [ "$BUILD_IOS_TA" == "TRUE" ] || [ "$BUILD_ANDROID_TA" == "TRUE" ]  || [ "$BUILD_OSX_TA" == "TRUE" ] 
	then
		:
	else
		echo "#######      ERROR | clean.sh line 11: Please do not call this script directly. To build, please call build.sh in root TA folder." 
		exit 1
fi




for arg in "$@"
do
    if [ "$arg" == "-all" ]
    then

        # clean and create build & products directories if required
        echo "#######      Cleaning all Targets (OSX, iOS, Android).."
		rm -r -f products/ios
		rm -r -f products/osx
		rm -r -f products/android
		#mkdir products


		rm -r -f build/osx
		rm -r -f build/ios
		rm -r -f build/android

		rm source/app/cmake/android/gradle/local.properties
		rm -r -f source/app/cmake/android/gradle/app/.externalNativeBuild

		rm source/app/cmake/ios/exportOptions.plist


    elif [ "$arg" == "-osx" ]
    then
        echo "#######      Cleaning OSX Targets (Server, App).."
		rm -r -f products/osx
		rm -r -f build/osx
		#mkdir products/osx


    elif [ "$arg" == "-ios" ]
    then
        echo "#######      Cleaning iOS Target.."
		rm -r -f products/ios
		rm -r -f build/ios
		#mkdir products/ios

		rm source/app/cmake/ios/exportOptions.plist

    elif [ "$arg" == "-android" ]
    then
        echo "#######      Cleaning Android Target.."
		
		rm -r -f products/android
		rm -r -f build/android
		#mkdir products/android

		rm source/app/cmake/android/gradle/local.properties
		rm -r -f source/app/cmake/android/gradle/app/.externalNativeBuild

    fi
done






