project(udpsocket)
cmake_minimum_required(VERSION 2.8.0)


#compile flags
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -O0 -g -ggdb -fPIC -std=gnu99 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -g -ggdb -fPIC -std=c++0x")


#build .so
include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/clog)

aux_source_directory(./client CLIENT_SRC)
aux_source_directory(./server SERVER_SRC)
aux_source_directory(./clog LOG_SRC)

add_library(sd_sdk SHARED ${CLIENT_SRC} ${SERVER_SRC} ${LOG_SRC})
#target_link_libraries(sd_sdk )

#build exe
 
set(LIB_OUT_DOR ${PROJECT_SOURCE_DIR}/build)
link_directories(${LIB_OUT_DOR})
include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/clog)

add_executable(client test/serviceDiscoveryClient.cpp)
target_link_libraries(client sd_sdk)

add_executable(server test/serviceDiscoveryServer.cpp)
target_link_libraries(server sd_sdk)