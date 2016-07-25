####################################################################################################
## [C++::CMAKE VERSION]
####################################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

####################################################################################################
## [C++::FLAGS]
####################################################################################################
IF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-rtti")
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-rtti")
ENDIF()

####################################################################################################
## [C++::OUTPUT]
####################################################################################################
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

####################################################################################################
## [C++::INCLUDES]
####################################################################################################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Quark-Core/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Quark-Debug/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Quark-Render/QuarkGL/include)

####################################################################################################
## [C++::MODULES]
####################################################################################################
ADD_SUBDIRECTORY(Quark-Core)
ADD_SUBDIRECTORY(Quark-Debug)
ADD_SUBDIRECTORY(Quark-Render)

ADD_SUBDIRECTORY(Quark-Tools)
