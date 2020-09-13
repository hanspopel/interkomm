@echo off




set "ROOT_FOLDER_MYMON=%cd%"


rm "%ROOT_FOLDER_MYMON%"/build.log
touch "%ROOT_FOLDER_MYMON%"/build.log

cd build


echo "#######      Building VS Project.."
powershell "cmake ../source -G""Visual Studio 16 2019"" 2>&1 | tee -a $ROOT_FOLDER_MYMON/build.log"

echo "#######      Building Plugin for WIN.."
cmake --build . --target MyMonService --config Release -- -j 40


if errorlevel 1 (
	echo "#######      ERROR: Building ControlPanel for WIN"
   	echo "####### 	   Failure Reason Given is %errorlevel%"
   exit /b %errorlevel%
)


echo "#######      Building ControlPanel for WIN.."
cmake --build . --target MyMonControlPanel --config Release -- -j 40

if errorlevel 1 (
	echo "#######      ERROR: Building ControlPanel for WIN"
   	echo "####### 	   Failure Reason Given is %errorlevel%"
   exit /b %errorlevel%
)



echo "#######      Deploying built targets to /products.."
cmake --build . --target install --config Release


if errorlevel 1 (
	echo "#######      ERROR: Deploying Plugin & Control Panel for WIN"
   	echo "####### 	   Failure Reason Given is %errorlevel%"
   exit /b %errorlevel%
)



cd ..