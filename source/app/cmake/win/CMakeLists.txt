cmake_minimum_required (VERSION 3.0)
set(OSX TRUE)
set(IOS FALSE)

# include MyMon specific cmake 
include(../intercom.cmake)

set(TARGET_NAME ${NAME}_win)



# include win specific cmake for zdb
set(BUILD_AS_LIBRARY )
set(BUILD_AS_MODULE )
set(EXCLUDE_ZDB_RESOURCES TRUE)

# include win specific cmake
include(../../../../zdb/scripts/win.cmake)




target_compile_definitions(${NAME} PRIVATE WIN32=1 WIN64=1 _LIB=1 HAS_TIMESPEC=1)

target_compile_definitions(${NAME} PUBLIC FORCE_CONTENTSCALE=0 ZDB_DISABLE_AUDIO=1)
target_compile_definitions(zdb_win PUBLIC FORCE_CONTENTSCALE=0 ZDB_DISABLE_AUDIO=1)



set_property(GLOBAL PROPERTY USE_FOLDERS ON)



	#link_directories("C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/lib")
add_definitions(/W1)

#configure_file(
	#Package_vc${COMPILER_VERSION}.${PLATFORM}.appxmanifest.in
    #${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
    #@ONLY)


# link

target_link_libraries(${NAME} zdb_win)
    #target_link_libraries(${NAME} mincore.lib mfuuid.lib kernel32.lib user32.lib)

set_target_properties(${NAME} PROPERTIES COMPILE_FLAGS "-DUSE_ZDB_WIN")


install(TARGETS ${NAME} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../../../products/win/")

