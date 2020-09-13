# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# please run main build.sh script in root folder - do not call directly!


#echo "#######      iOS Build was called from $PWD"

if [ "$BUILD_IOS_TA" == "TRUE" ]
	then
		:
	else
		echo "#######      ERROR | build_ios.sh line 11: Please do not call this script directly. To build, please call build.sh in root TA folder."
		exit 1
fi




if [ "$CODESIGN_TEAM_ID_TA" == "" ]
	then
		echo "#######      ERROR: Can't compile iOS App without valid Apple Developer Profile. Please set CODESIGN_TEAM_ID_TA in 'build.sh'"
		exit 1
fi
if [ "$CODESIGN_BUNDLE_ID_TA" == "" ]
	then
		echo "#######      ERROR: Can't compile iOS App without valid Bundle ID & matching Developer Profile. Please set CODESIGN_BUNDLE_ID_TA in 'build.sh'"
		exit 1
fi






### iOS

# the next steps require a valid developer identity on the build machine
# archive iOS app, move to /products/ios
echo "#######      Archiving iOS App.."
xcodebuild archive -project touchAblePro_all.xcodeproj -scheme "touchAblePro_ios" -configuration Release -archivePath $PWD/../../build/ios/TA.xcarchive -jobs 40 -allowProvisioningUpdates

RESULT=$?

if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: iOS creating Archive failed"
	exit 1
else
	echo "#######      SUCCESS: created iOS Archive"
fi


# specify the correct TeamID (as above) in TA/source/app/cmake/ios/exportOptions.plist
echo "#######      Specifying Team ID for Extraction of IPA.."
sed "s/TEAM_ID/${CODESIGN_TEAM_ID_TA}/g" ../../source/app/cmake/ios/exportOptions_in.plist > ../../source/app/cmake/ios/exportOptions.plist



# extract .ipa from archive and move to /products/ios
echo "#######      Extracting iOS App from Archive.."
xcodebuild -exportArchive -archivePath $PWD/../../build/ios/TA.xcarchive  -exportPath $PWD/../../build/ios  -exportOptionsPlist $PWD/../../source/app/cmake/ios/exportOptions.plist -allowProvisioningUpdates

RESULT=$?

if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: iOS extracting from Archive failed"
	exit 1
else
	echo "#######      SUCCESS: extracting from iOS Archive"
fi

mkdir ../../products/ios

echo "#######      Deploying iOS App to /products.."
cp -R $PWD/../../build/ios/touchAblePro_ios.ipa $PWD/../../products/ios/





