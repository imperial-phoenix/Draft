set(TARGET_NAME "CList")

set(HEADER_FILES
   ${CMAKE_CURRENT_LIST_DIR}/Include/Include/CList.h)

set(SOURCE_FILES
   ${CMAKE_CURRENT_LIST_DIR}/CList.c)

add_library(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS}
                                                 ${CMAKE_CURRENT_LIST_DIR}/Include)

if (IS_GOOGLETEST_FOUND)
   add_subdirectory(Test)
endif()

set(PVS_TARGET_LIST ${PVS_TARGET_LIST} ${TARGET_NAME} PARENT_SCOPE)