@echo off


set "ROOT_FOLDER_TOUCHABLE=%cd%"

set "LOGFILE=%cd%\build_win.log"
set "POTENTIAL_LOG_NAME=%1"
set "WIN_BUILD=%cd%\build\win"
set "WIN32_BUILD=%cd%\build\win32"
set "WIN_PRODUCTS=%cd%\products\win"
set "BUILD_DIR=%cd%\build"

set "TRUE="

IF "%POTENTIAL_LOG_NAME%" == "-gen" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-all" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-allr" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-clean" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-update" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-win" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-force" set TRUE=1
IF "%POTENTIAL_LOG_NAME%" == "-server" set TRUE=1
IF NOT defined TRUE (
    set "LOGFILE=%POTENTIAL_LOG_NAME%"
)



REM # DELETE AND RECREATE BUILD.LOG

del "%LOGFILE%"
type nul > "%LOGFILE%"

powershell "echo """"#######      Initiating Build Script with options: %*"""" 2>&1 | tee -a %LOGFILE%"
powershell "echo """"#######      Options allowed: -clean (cleans build folder and products) | -all (cleans all targets, then builds and deploys all applicable targets) | -allr (builds all applicable targets) | -gen (creates VS Projects) | -update (updates git sources) | -server (builds windows server)  """" 2>&1 | tee -a %LOGFILE%"




set /A BUILD_OPTION=0
set REQUIRE_BUILD=0
set /A REV_NUMBER=111111 
set BUILD_NUMBER=11
set IS_X86=0
if exist versionnumber.txt (
set BUILD_NUMBER=114
) else (
  powershell "echo """"build text not found"""" 2>&1 | tee -a %LOGFILE%"


powershell "echo """"#######      GETTING BUILD_NUMBER"""" 2>&1 | tee -a %LOGFILE%"


  set REV_NUMBER=0


  REM # setting build number
  REM set MM_COMMITS=git rev-list master --count
  FOR /F "tokens=* USEBACKQ" %%F IN (`git rev-list master --count`) DO (
    SET TA_COMMITS=%%F
  )


  echo TA_COMMITS: %TA_COMMITS%



  cd zdb



  REM # setting build number
  set ZDB_COMMITS=git rev-list dev --count
  FOR /F "tokens=* USEBACKQ" %%F IN (`git rev-list dev --count`) DO (
    SET ZDB_COMMITS=%%F
  )



echo REV_NUM_ZDB: %ZDB_COMMITS% 
echo REV_NUM_MYMON: %TA_COMMITS%

  set /a REV_NUMBER=%ZDB_COMMITS% + %TA_COMMITS% - 1830

  cd ..


) 





set BUILD_NUMBER=%REV_NUMBER%
set VERSION=1.506


powershell "echo """"#######      Using BUILD_NUMBER: %REV_NUMBER%"""" 2>&1 | tee -a %LOGFILE%"
powershell "echo """"#######      Using VERSIOn_NUMBER: %VERSION%"""" 2>&1 | tee -a %LOGFILE%"



REM # CHECK FOR CLEAN / UPDATE IN FIRST LOOP

FOR %%A IN (%*) DO (

    IF %%A==-clean (
    	CALL :CLEAN 
    	if errorlevel 1 (
			powershell "echo """"#######      ERROR: Cleaning all targets (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
   			exit /b 1
		)
	)

	IF %%A==-update (
    	CALL :UPDATE 
    	if errorlevel 1 (
			powershell "echo """"#######      ERROR: Failed to update sources (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
   			exit /b 1
		)
	)
)


REM # CHECK FOR BUILD AND GENERATE OPERATIONS IN SECOND LOOP

FOR %%A IN (%*) DO (

  IF %%A==-server (
       set /A BUILD_OPTION=1
        CALL :CLEAN 
        if errorlevel 1 (
            powershell "echo """"#######      ERROR: Cleaning all targets (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
            exit /b 1
        )
      CALL :BUILD_SERVER 
      if errorlevel 1 (
      powershell "echo """"#######      BUILD SCRIPT FAILED (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
        exit /b 1
    )
  )

	IF %%A==-all (
        CALL :CLEAN 
        if errorlevel 1 (
            powershell "echo """"#######      ERROR: Cleaning all targets (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
            exit /b 1
        )
    	CALL :BUILD 
    	if errorlevel 1 (
			powershell "echo """"#######      BUILD SCRIPT FAILED (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
   			exit /b 1
		)
	)
    IF %%A==-allr (
        CALL :BUILD 
        if errorlevel 1 (
            powershell "echo """"#######      BUILD SCRIPT FAILED (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
            exit /b 1
        )
    )
	IF %%A==-gen (
    	CALL :GEN_NO_DEPLOY 
    	if errorlevel 1 (
			powershell "echo """"#######      BUILD SCRIPT FAILED (exiting early).."""" 2>&1 | tee -a %LOGFILE%"
   			exit /b 1
		)
	)
)





REM # SCRIPT RAN THROUGH WITH/WITHOUT ERRORS

if errorlevel 1 (
			powershell "echo """"#######      ERROR: Build Script finished with Errors"""" 2>&1 | tee -a %LOGFILE%"
   			EXIT /b 1
		)

powershell "echo """"#######      Build Script finished without breaking Errors."""" 2>&1 | tee -a %LOGFILE%"
EXIT /B 0


REM # GEN FUNCTION
:GEN 

REM # CREATE BUILD DIRECTORY

if exist %BUILD_DIR% (
    powershell "echo """"#######  build dir already blabla"""" 2>&1 | tee -a %LOGFILE%"

) else (
powershell "mkdir build 2>&1 | tee -a %LOGFILE%"
)
cd build
if exist %WIN_BUILD% (
    powershell "echo """"#######  build\win dir already blabla"""" 2>&1 | tee -a %LOGFILE%"

) else (
powershell "mkdir win 2>&1 | tee -a %LOGFILE%"
)
cd win

powershell "cmake -DIS_X86=OFF -DDEPLOY=ON -DBUILD_NUMBER:STRING=%BUILD_NUMBER% -DVERSION:STRING=%VERSION% ..\..\source -G """"Visual Studio 16 2019"""" -A x64 2>&1 | tee -a %LOGFILE%"

if errorlevel 1 (
			powershell "echo """"#######      ERROR: Failed to Create VS Projects"""" 2>&1 | tee -a %LOGFILE%"
   			cd ..
            cd ..
   			exit /b 1
		)
cd ..
cd ..

EXIT /B 0


REM # GEN WITHOUT DEPLOY FUNCTION
:GEN_NO_DEPLOY 

REM # CREATE BUILD DIRECTORY

if exist %BUILD_DIR% (
  powershell "echo """"#######   build dir already blabla"""" 2>&1 | tee -a %LOGFILE%"
) else (
powershell "mkdir build 2>&1 | tee -a %LOGFILE%"
)
cd build
if exist %WIN_BUILD% (
    powershell "echo """"#######  build\win dir already blabla"""" 2>&1 | tee -a %LOGFILE%"
) else (
powershell "mkdir win 2>&1 | tee -a %LOGFILE%"
)
cd win

powershell "cmake -DIS_X86=OFF -DDEPLOY=OFF -DBUILD_NUMBER:STRING=%BUILD_NUMBER% -DVERSION:STRING=%VERSION% ..\..\source -G  """"Visual Studio 16 2019"""" -A x64 2>&1 | tee -a %LOGFILE%"


if errorlevel 1 (
            powershell "echo """"#######      ERROR: Failed to Create VS Projects"""" 2>&1 | tee -a %LOGFILE%"
            cd ..
            cd ..
            exit /b 1
        )
cd ..
cd ..

EXIT /B 0


REM # UPDATE SOURCES FUNCTION

:UPDATE

powershell "git pull 2>&1 | tee -a %LOGFILE%"
if errorlevel 1 (
			powershell "echo """"#######      ERROR: Failed to update main git"""" 2>&1 | tee -a %LOGFILE%"
   			exit /b 1
		)
cd zdb
powershell "git pull 2>&1 | tee -a %LOGFILE%"
if errorlevel 1 (
			powershell "echo """"#######      ERROR: Failed to update zdb git"""" 2>&1 | tee -a %LOGFILE%"
   			cd ..
            cd ..
   			exit /b 1
		)
cd ..
cd ..
EXIT /B 0


REM # BUILD FUNCTION
:BUILD

:BUILD_SERVER
REM # CALL GENERATE FUNCTION
CALL :GEN
REM # CHECK FOR ERRORS
if errorlevel 1 (
   exit /b %errorlevel%
)

cd build
cd win 

REM # BUILD SERVER
powershell "echo """"#######      Building Server for WIN.."""" 2>&1 | tee -a %LOGFILE%"
powershell "cmake --build . --target touchAbleServer --config Release -- /M  2>&1 | tee -a %LOGFILE%"

REM # CHECK FOR ERRORS
if errorlevel 1 (
	powershell "echo """"#######      ERROR: Building Server for WIN.."""" 2>&1 | tee -a %LOGFILE%"
   	cd ..
    cd ..
   exit /b 1
)

if %BUILD_OPTION%==1 (
  powershell "echo """"#######      SUCCES: Building Server for WIN.."""" 2>&1 | tee -a %LOGFILE%"
          cd ..
            cd ..
  EXIT /B 0
)



REM # BUILD APP
powershell "echo """"#######      Building Application for WIN.."""" 2>&1 | tee -a %LOGFILE%"
powershell "cmake --build . --target touchAblePro --config Release -- /M  2>&1 | tee -a %LOGFILE%"


REM # CHECK FOR ERRORS
if errorlevel 1 (
	powershell "echo """"#######      ERROR: Building Application for WIN.."""" 2>&1 | tee -a %LOGFILE%"
   	cd ..
    cd ..
   exit /b 1
)

REM # DEPLOY PRODUCTS
powershell "echo """"#######      Deploying built targets to /products.."""" 2>&1 | tee -a %LOGFILE%"
powershell "cmake --build . --target install --config Release 2>&1 | tee -a %LOGFILE%"

REM # CHECK FOR ERRORS
if errorlevel 1 (
	powershell "echo """"#######      ERROR: Deploying Plugin & Control Panel for WIN.."""" 2>&1 | tee -a %LOGFILE%"
   	cd ..
    cd ..
   exit /b 1
)


cd ..
cd ..

EXIT /B 0

REM # CLEAN FUNCTION
:CLEAN

REM # CLEAN BUILD DIRECTORY
powershell "echo """"#######      Cleaning Build Directory.."""" 2>&1 | tee -a %LOGFILE%"


if exist %WIN_BUILD% (
powershell "rm %cd%\build\win -r -force 2>&1 | tee -a %LOGFILE%"
) else (
powershell "echo """"#######    \build\win  not existing """" 2>&1 | tee -a %LOGFILE%"
)

REM # CLEAN PRODUCTS DIRECTORY
powershell "echo """"#######      Cleaning Products Directory.."""" 2>&1 | tee -a %LOGFILE%"
if exist %WIN_PRODUCTS% (
powershell "rm %cd%\products\win -r -force 2>&1 | tee -a %LOGFILE%"
) else (
  powershell "echo """"#######    \product\win  not existing """" 2>&1 | tee -a %LOGFILE%"
)
EXIT /B 0











