project(db_sdk)
set(CMAKE_SYSTEM_NAME Linux)
cmake_minimum_required(VERSION 2.8.0)

#compile flags
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -O0 -g -ggdb -fPIC -std=gnu99 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -g -ggdb -fPIC -std=c++0x")

# build the .so
include_directories(${PROJECT_SOURCE_DIR}/src)
aux_source_directory(./src/mysql SRC_DIR)
aux_source_directory(./src/api API_SRC_DIR)
aux_source_directory(./src/basic LOG_SRC_DIR)
aux_source_directory(./src/log LOG_DIR)
add_library(db_sdk SHARED ${SRC_DIR} ${API_SRC_DIR} ${LOG_SRC_DIR} ${LOG_DIR})
target_link_libraries(db_sdk mysqlclient)

#build exe
 
set(LIB_OUT_DOR ${PROJECT_SOURCE_DIR}/../build)
link_directories(${LIB_OUT_DOR})
include_directories(./src)
set(source_file test/test.cpp)
add_executable(test ${source_file})

target_link_libraries(test db_sdk)

