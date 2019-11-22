set(LIBRARY_NAME "rest")
set(REST_SOURECE_DIR ${PROJECT_SOURCE_DIR}/src)
set(REST_OGM_SOURECE_DIR ${PROJECT_SOURCE_DIR}/src/ogm)
set(REST_OGM_SERIALIZER_SOURECE_DIR ${PROJECT_SOURCE_DIR}/src/ogm/serializer)

include_directories(/usr/local/include/ include/public/)

file(GLOB SRC_FILES
        ${REST_SOURECE_DIR}/*.cpp
        ${REST_OGM_SOURECE_DIR}/*.cpp
        ${REST_OGM_SERIALIZER_SOURECE_DIR}/*.cpp)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES})

target_include_directories(
        ${LIBRARY_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/public/>
)