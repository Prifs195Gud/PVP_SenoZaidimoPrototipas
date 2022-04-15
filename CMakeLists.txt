cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)

project(PVP_SenoZaidimoPrototipas)

set(SOURCE
   ${CMAKE_CURRENT_SOURCE_DIR}/PVP_SenoZaidimoPrototipas/*.cpp
   PARENT_SCOPE
)

set(HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/PVP_SenoZaidimoPrototipas/*.h
   PARENT_SCOPE
)