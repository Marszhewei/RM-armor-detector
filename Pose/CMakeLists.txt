AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

find_package(OpenCV REQUIRED)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/mylibrary)

ADD_LIBRARY(pnp SHARED ${DIR_LIB_SRCS})

target_link_libraries(pnp serial ${OpenCV_LIBS})

