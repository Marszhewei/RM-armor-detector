# 获取当前目录下所有文件
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

FIND_PACKAGE(OpenCV REQUIRED)

# 设置生成库的位置（在编译目录下的mylib目录中）
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/mylib)

# 将所有文件加到库中
ADD_LIBRARY(serial SHARED ${DIR_LIB_SRCS})

