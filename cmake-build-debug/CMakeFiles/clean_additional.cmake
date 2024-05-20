# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Canvas_Threads_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Canvas_Threads_autogen.dir\\ParseCache.txt"
  "Canvas_Threads_autogen"
  )
endif()
