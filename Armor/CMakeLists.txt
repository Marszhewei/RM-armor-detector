# 获取当前目录下所有文件
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

# 寻找opencv
FIND_PACKAGE(OpenCV REQUIRED)

# 设置路径，最后生成的共享库在编译目录下的mylibrary
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/mylibrary)

# 生成armor共享库
ADD_LIBRARY(armor SHARED ${DIR_LIB_SRCS})

# 链接 armor opencv
TARGET_LINK_LIBRARIES(armor ${OpenCV_LIBS})

