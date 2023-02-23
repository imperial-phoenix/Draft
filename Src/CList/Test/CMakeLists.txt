set(TARGET_NAME "CListTest")

set(SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/CListTest.cpp)

add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries(${TARGET_NAME} PRIVATE gtest CList)