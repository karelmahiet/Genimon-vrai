# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GenimonV2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GenimonV2_autogen.dir\\ParseCache.txt"
  "GenimonV2_autogen"
  )
endif()
