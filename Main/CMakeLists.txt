# 获取当前目录下所有文件
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#FIND_PACKAGE(OpenCV REQUIRED)

# 设置可执行文件输出位置（编译目录下的bin目录中）
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 编译
ADD_EXECUTABLE(main ${DIR_SRCS})

# 链接所需库
TARGET_LINK_LIBRARIES(main armor pnp setcam)
