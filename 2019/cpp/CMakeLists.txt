
cmake_minimum_required(VERSION 3.5)

FILE(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR} "test/*.cpp")
MESSAGE(${SRC_FILES})
MESSAGE("====================================")
FOREACH(FILE_PATH ${SRC_FILES})
    MESSAGE(${FILE_PATH})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
ENDFOREACH(FILE_PATH)
MESSAGE("====================================")
