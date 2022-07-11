cmake_minimum_required(VERSION 3.10)
project(leGame)

set(CMAKE_GENERATOR "Ninja")

message(STATUS)
if(UNIX)
    message(STATUS "|   BUILDING UNIX   | --")
elseif(WIN32)
    message(STATUS "|   BUILDING WIN32   | --")
endif()
message(STATUS "Generator: " ${CMAKE_GENERATOR})
message(STATUS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
include_directories("${CMAKE_SOURCE_DIR}/src")
set(THIRD_PARTY "${CMAKE_SOURCE_DIR}/3rdparty")
include_directories(${THIRD_PARTY})

if(MINGW)
    set(SDL2_DIR "${THIRD_PARTY}/SDL_Bundle_Mingw")
    set(SDL2_INCLUDE_DIRS ${SDL2_DIR}/include) # Same as SDL2_IMAGE_INCLUDE_DIR and SDL2_MIXER_INCLUDE_DIR
    set(SDL2_LIBRARIES
        -lmingw32 
        ${SDL2_DIR}/lib/libSDL2main.a 
        ${SDL2_DIR}/lib/libSDL2.dll.a
        #-mwindows
        )
    set(SDL2_IMAGE_LIBRARIES ${SDL2_DIR}/lib/libSDL2_image.dll.a)
    set(SDL2_MIXER_LIBRARIES ${SDL2_DIR}/lib/libSDL2_mixer.dll.a)
    set(SDL2_TTF_LIBRARIES ${SDL2_DIR}/lib/libSDL2_ttf.dll.a)


    ## This copy section should be done cleaner to prevent people from ripping their hair in fury ##
    configure_file(${SDL2_DIR}/bin/libFLAC-8.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libfreetype-6.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libjpeg-9.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libmodplug-1.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libmpg123-0.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libogg-0.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libopus-0.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libopusfile-0.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libpng16-16.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libtiff-5.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libvorbis-0.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libvorbisfile-3.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/libwebp-7.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/SDL2.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/SDL2_image.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/SDL2_mixer.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/SDL2_ttf.dll . COPYONLY)
    configure_file(${SDL2_DIR}/bin/zlib1.dll . COPYONLY)
    ## ------------------------------------------------------------------------------------------ ##

elseif(UNIX)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})  
endif()

include_directories(${SDL2_INCLUDE_DIRS} ${THIRD_PARTY})
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${MISC_FLAGS}
     -static-libgcc -static-libstdc++)

add_definitions(-DSDL_MAIN_HANDLED) #Windows?


# COPY DOES NOT NEED ADMIN ACCESS
#--------------------------------------------------------
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
if (EXISTS ${ASSETS_DIR} AND IS_DIRECTORY ${ASSETS_DIR})
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()
#--------------------------------------------------------


# SYMLINK NEEDS ADMIN ACCESS
#--------------------------------------------------------
#set(assetsource "${CMAKE_SOURCE_DIR}/assets")
#set(assetbuild "${CMAKE_BINARY_DIR}/assets")
#add_custom_command(
#    TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E create_symlink "${assetsource}" "${assetbuild}" 
#    DEPENDS ${assetsource}
#    COMMENT "symbolic link resources folder from ${assetsource} <= ${assetbuild}"
#)
#--------------------------------------------------------
