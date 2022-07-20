# 获取当前目录下所有文件
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

# 找opencv库
FIND_PACKAGE(OpenCV REQUIRED)

# 设置库生成路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/mylibrary)

# 创建共享库 setcam
ADD_LIBRARY(setcam SHARED ${DIR_LIB_SRCS})

# 链接 setcam opencv
TARGET_LINK_LIBRARIES(setcam ${OpenCV_LIBS})
