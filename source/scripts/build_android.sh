# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# please run main build.sh script in root folder - do not call directly!


#echo "#######      Android Build was called from $PWD"

if [ "$BUILD_ANDROID_TA" == "TRUE" ]
	then
		:
	else
		echo "#######      ERROR | build_android.sh line 11: Please do not call this script directly. To build, please call build.sh in root TA folder." 
		exit 1
fi




if [ -d "$ANDROID_SDK_TA" ]
	then
		:
else
	echo "#######      ERROR: Can't find Android SDK. Please set ANDROID_SDK_TA variable to the SDKs path in 'build.sh'"
	exit 1
fi





# configure build scripts
# armeabi-v7a
NDK_BUNDLE=$ANDROID_SDK_TA/ndk-bundle




# creating local.properties with local SDK & NDK paths - please configure above
echo "#######      Setting Android SDK/NDK Paths"
echo "ndk.dir=$NDK_BUNDLE
sdk.dir=$ANDROID_SDK_TA" >> source/app/cmake/android/gradle/local.properties




# move to gradle folder
cd source/app/cmake/android/gradle

# assemble Release .apk (with all configured platforms)
echo "#######      Configuring & Assembling Android Sources.."
./gradlew assembleRelease -PbuildDir=$PWD/../../../../../build/android/app/build/

RESULT=$?

if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: Android Build failed"
	exit 1
else
	echo "#######      SUCCESS: Built Android.apk"
fi

# move back to main TA folder
cd ../../../../../



# deploy .apk to products/android
echo "#######      Deploying Android.apk to /products.."
mkdir products/android
cp build/android/app/build/outputs/apk/release/app-release.apk products/android/
mv products/android/app-release.apk products/android/TA_android.apk


