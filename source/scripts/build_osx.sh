# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# please run main build.sh script in root folder - do not call directly!


#echo "#######      OSX Build was called from $PWD"

if [ "$BUILD_OSX_TA" == TRUE ]
	then
		:
	else
		echo "#######      ERROR | build_osx.sh line 11: Please do not call this script directly. To build, please call build.sh in root TA folder. $BUILD_OSX" 
		exit 1
fi

### OSX

# build Server
echo "#######      Building Server for OSX.."
cmake --build . --target tAProServer --config Release -- -j 40

RESULT=$?

if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: Building Server for OSX"
	exit 1
else
	echo "#######      SUCCESS: Built Server for OSX"
fi


# build test - app for osx
echo "#######      Building App for OSX.."
cmake --build . --target touchAblePro_osx --config Release -- -j 40

RESULT=$?

if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: Building App for OSX"
	exit 1
else
	echo "#######      SUCCESS: Built App for OSX"
fi

# deploy plugin & controlpanel to /products/osx
echo "#######      Deploying built targets to /products.."
cmake --build . --target install --config Release

RESULT=$?

if [ "$RESULT" != "0" ]
then
	echo "#######      ERROR: deploying built products to /products"
	exit 1
else
	echo "#######      SUCCESS: Deployed OSX products"
fi


