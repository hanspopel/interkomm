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
# upload iOS app from /products/ios
echo "#######      Uploading iOS App.."
CURRENT_PATH=$PWD
XCODE_PATH="$(xcode-select -p)"
echo "XCode Path: $XCODE_PATH"
cd "$XCODE_PATH/../Applications/Application Loader.app/Contents/Frameworks/ITunesSoftwareService.framework/Support/"


if [ "$CODESIGN_TEAM_ID_TA" == "834XFBML77" ]
	then
		./altool --upload-app -f $CURRENT_PATH/../../products/ios/touchAblePro_ios.ipa -u cblomert@touch-able.com -p aqxj-iqlb-wnrh-edxa
		RESULT=$?
fi

#		./altool --upload-app -f $CURRENT_PATH/../../products/ios/TA_ios.ipa -u hanspopel@mail.ru -p oxma-mrik-euld-ouop


if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: uploading iOS Archive failed"
	exit 1
else
	echo "#######      SUCCESS: uploading iOS Archive"
fi


