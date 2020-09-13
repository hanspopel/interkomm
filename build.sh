
# !!!!!!!!!               ! CAUTION !                !!!!!!!!! #
# run this script ONLY from main folder STUDIOMUX/.

# configure vars (These have to be configured for successful Android & iOS builds)

# RequestUUID = 787438d6-cffc-4f74-a825-5713c3bf606a

export ROOT_FOLDER_STUDIOMUX=$PWD

# remove and create build.log
LOGFILE_NAME=build_osx.log

POTENTIAL_LOG_NAME=$1
if [ "$POTENTIAL_LOG_NAME" == "-osx" ] || [ "$POTENTIAL_LOG_NAME" == "-ios" ] || [ "$POTENTIAL_LOG_NAME" == "-server" ] || [ "$POTENTIAL_LOG_NAME" == "-gen" ] || [ "$POTENTIAL_LOG_NAME" == "-iosupload" ] || [ "$POTENTIAL_LOG_NAME" == "-all" ] || [ "$POTENTIAL_LOG_NAME" == "-osxr" ] || [ "$POTENTIAL_LOG_NAME" == "-iosr" ] || [ "$POTENTIAL_LOG_NAME" == "-iosrupload" ] || [ "$POTENTIAL_LOG_NAME" == "-allr" ] || [ "$POTENTIAL_LOG_NAME" == "-clean" ]
then
    :
else
    LOGFILE_NAME=$POTENTIAL_LOG_NAME
fi



LOGFILE=$ROOT_FOLDER_STUDIOMUX/$LOGFILE_NAME
rm $LOGFILE
touch $LOGFILE



  echo "#######      Setting Codesign ID to Zerodebug Account" 2>&1 | tee -a $LOGFILE
    # iOS codesigning
    # set to Zerodebug Apple Developer Account Team-ID
    export CODESIGN_TEAM_ID_STUDIOMUX="834XFBML77"


    # set to the bundle identifier that has been set for the iOS app on Zerodebug iTunesConnect Account
    export CODESIGN_BUNDLE_ID_STUDIOMUX="com.zerodebug.studiomux"


read REV_NUMBER < build_number.txt

 RESULT=$?
    if [ "$RESULT" != "0" ]
    then
        #get mymon rev count
        REV_NUMBER_STUDIOMUX=$(expr $(git rev-list master --count))
        echo "REV NUMBER studiomux: $REV_NUMBER_STUDIOMUX" 2>&1 | tee -a $LOGFILE


        cd zdb
        #get zdb rev count
        REV_NUMBER_ZDB=$(expr $(git rev-list dev --count))

        echo "REV NUMBER ZDB: $REV_NUMBER_ZDB" 2>&1 | tee -a $LOGFILE
        cd ..

        # add up both revision numbers 
        REV_NUMBER=$(expr $REV_NUMBER_STUDIOMUX + $REV_NUMBER_ZDB)

    else
        :
    fi



export BUILD_NUMBER="$REV_NUMBER"
export VERSION="5.000"
export VERSION_INT="5000"



# Android
# set to local Android SDK directory
cd ~

cd $ROOT_FOLDER_STUDIOMUX







export BUILD_IOS_STUDIOMUX=FALSE
export BUILD_OSX_STUDIOMUX=FALSE
export BUILD_ALL_STUDIOMUX=FALSE
export CLEAN_ALL_STUDIOMUX=FALSE
export BUILD_PROJECTS_STUDIOMUX=FALSE




# Check current working directory
echo "#######      Checking Working directory.." 2>&1 | tee -a $LOGFILE


if [ -d zdb ]
then
    echo "#######      Success!" 2>&1 | tee -a $LOGFILE
else
    echo "#######      ERROR: zdb library not found - please download from git" 2>&1 | tee -a $LOGFILE
    exit
fi

if [ -d source ]
then
	:
else 
	echo "#######      ERROR: Can't find source files - please run this script only from ./touchable main folder";  2>&1 | tee -a $LOGFILE
	exit 
fi








CREATE_XCODE_PROJ=OFF
CREATE_BUILD_FOLDER=OFF


for arg in "$@"
do
    if [ "$arg" == "-update" ]
    then
    	# update sources
		echo "#######      Updating Sources.." 2>&1 | tee -a $LOGFILE
		git pull 2>&1 | tee -a $LOGFILE
        cd zdb  2>&1 | tee -a $LOGFILE
        git pull 2>&1 | tee -a $LOGFILE
        cd ..
    fi

    if [ "$arg" == "-clean" ]
    then
        export CLEAN_ALL_STUDIOMUX=TRUE
    	echo "#######      Cleaning up.." 2>&1 | tee -a $LOGFILE
    	./source/scripts/clean.sh -all 2>&1 | tee -a $LOGFILE
	fi

    if [ "$arg" == "-gen" ]
    then
        CREATE_XCODE_PROJ=ON
        CREATE_BUILD_FOLDER=ON
        export DEPLOY=OFF
    fi

    if [ "$arg" == "-osx" ] || [ "$arg" == "-ios" ] || [ "$arg" == "-iosupload" ] || [ "$arg" == "-all" ] || [ "$arg" == "-server" ]
    then
        mkdir products 2>&1 | tee -a $LOGFILE

        if [ "$arg" != "-android" ]
        then
            CREATE_XCODE_PROJ=ON
            export DEPLOY=ON
        fi

        CREATE_BUILD_FOLDER=ON
        export CLEAN_ALL_STDUIOMUX=TRUE
        ./source/scripts/clean.sh $arg 2>&1 | tee -a $LOGFILE
    fi

    if [ "$arg" == "-osxr" ] || [ "$arg" == "-iosr" ] || [ "$arg" == "-allr" ] || [ "$arg" == "-androidr" ]
    then
        mkdir products 2>&1 | tee -a $LOGFILE
        CREATE_XCODE_PROJ=ON
        export DEPLOY=ON
        CREATE_BUILD_FOLDER=ON
    fi


done






if [ "$CREATE_BUILD_FOLDER" == "ON" ]
    then
        echo "#######      Creating build directory.." 2>&1 | tee -a $LOGFILE
        mkdir build 2>&1 | tee -a $LOGFILE
fi


if [ "$CREATE_XCODE_PROJ" == "ON" ]
    then
        export BUILD_PROJECTS_STUDIOMUX=TRUE
        echo "#######      Generating XCode Projects.." 2>&1 | tee -a $LOGFILE
        mkdir build/osx 2>&1 | tee -a $LOGFILE

        cd $ROOT_FOLDER_STUDIOMUX/build/osx
        ../../source/scripts/build_projects.sh 2>&1 | tee -a $LOGFILE ; test ${PIPESTATUS[0]} -eq 0


        RESULT=$?
        if [ "$RESULT" != "0" ]
        then
            echo "#######      ERROR: Creating XCode Projects failed, exiting (1)"
            exit 1
        else
            :
        fi

fi


for arg in "$@"
do
	cd $ROOT_FOLDER_STUDIOMUX
    RESULT="0"
    if [ "$arg" == "-all" ] || [ "$arg" == "-allr" ]
    then
        export BUILD_ALL_STUDIOMUX=TRUE
        echo "#######      Building all Targets (OSX, iOS, Plugin).. ROOT_FOLDER: $ROOT_FOLDER_STUDIOMUX" 2>&1 | tee -a $LOGFILE
        cd $ROOT_FOLDER_STUDIOMUX/build/osx
        ../../source/scripts/build_all.sh 2>&1 | tee -a $LOGFILE ; test ${PIPESTATUS[0]} -eq 0
        RESULT=$?
    fi

    if [ "$arg" == "-osx" ] || [ "$arg" == "-osxr" ]
    then
        export BUILD_OSX_STUDIOMUX=TRUE
        echo "#######      Building OSX Targets (Plugin, ControlPanel, App).. rootfolder: $ROOT_FOLDER_STUDIOMUX" 2>&1 | tee -a $LOGFILE
        cd $ROOT_FOLDER_STUDIOMUX/build/osx
        echo "in folder: $PWD"
        ../../source/scripts/build_osx.sh 2>&1 | tee -a $LOGFILE ; test ${PIPESTATUS[0]} -eq 0
        RESULT=$?
	fi
    if [ "$arg" == "-server" ]
    then
        export BUILD_OSX_STUDIOMUX=TRUE
        echo "#######      Building OSX Targets (Plugin, ControlPanel, App).. rootfolder: $ROOT_FOLDER_STUDIOMUX" 2>&1 | tee -a $LOGFILE
        cd $ROOT_FOLDER_STUDIOMUX/build/osx
        echo "in folder: $PWD"
        ../../source/scripts/build_server.sh 2>&1 | tee -a $LOGFILE ; test ${PIPESTATUS[0]} -eq 0
        RESULT=$?
    fi

    if [ "$arg" == "-ios" ] || [ "$arg" == "-iosr" ] || [ "$arg" == "-iosrupload" ] || [ "$arg" == "-iosupload" ]
    then
        export BUILD_IOS_STUDIOMUX=TRUE
        echo "#######      Building iOS App.." 2>&1 | tee -a $LOGFILE
        cd $ROOT_FOLDER_STUDIOMUX/build/osx
        ../../source/scripts/build_ios.sh 2>&1 | tee -a $LOGFILE ; test ${PIPESTATUS[0]} -eq 0
        RESULT=$?
	fi

        if [ "$RESULT" != "0" ]
        then
            echo "#######      ERROR: Build ($arg) failed, exiting (1)"
            exit 1
        else
            :
        fi
        
    if [ "$arg" == "-iosrupload" ] || [ "$arg" == "-iosupload" ]
    then
        export UPLOAD_IOS_STUDIOMUX=TRUE
        echo "#######      Uploading iOS App.." 2>&1 | tee -a $LOGFILE
        cd $ROOT_FOLDER_STUDIOMUX/build/osx
        ../../source/scripts/upload_ios.sh 2>&1 | tee -a $LOGFILE ; test ${PIPESTATUS[0]} -eq 0
        RESULT=$?
    fi

        export BUILD_ANDROID_STUDIOMUX=FALSE
        export BUILD_IOS_STUDIOMUX=FALSE
        export BUILD_OSX_STUDIOMUX=FALSE
        export BUILD_ALL_STUDIOMUX=FALSE
        export UPLOAD_IOS_STUDIOMUX=FALSE
done


echo "#######      Build Script finished without Errors!" 2>&1 | tee -a $LOGFILE







