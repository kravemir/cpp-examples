cmake_minimum_required(VERSION 3.0)

find_library(AIO_LIBRARY
    NAMES aio
)

if (AIO_LIBRARY)
  message(STATUS "AIO Library found: ${AIO_LIBRARY}")
else()
  message(FATAL_ERROR "AIO Library not found")
endif()

add_executable(async-io main.c)
target_link_libraries(async-io ${AIO_LIBRARY} rt)