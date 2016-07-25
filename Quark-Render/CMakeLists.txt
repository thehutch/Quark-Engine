####################################################################################################
## [C++::INCLUDES]
####################################################################################################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Quark-Core/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Quark-Debug/include)

####################################################################################################
## [C++::MODULES]
####################################################################################################
IF (QUARK_BUILD_DX)
    ADD_SUBDIRECTORY(QuarkDX)
ELSEIF (NOT QUARK_BUILD_GL)
    ADD_SUBDIRECTORY(QuarkGL)
ELSEIF (QUARK_BUILD_VK)
    ADD_SUBDIRECTORY(QuarkVK)
ENDIF()
