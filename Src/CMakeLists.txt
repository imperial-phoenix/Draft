# Headers common to all projects
set(SHARED_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/Include)

# List of all targets
set(TARGET_LIST)

# Subdirectories
add_subdirectory(List)

# pvs target
if (IS_PVS_AVAILABLE)

   include(${PROJECT_SOURCE_DIR}/Extern/Pvs/PVS-Studio.cmake)

   pvs_studio_add_target(TARGET Pvs ALL
                         FORMAT fullhtml
                         ANALYZE ${TARGET_LIST}
                         MODE GA:1,2)

endif()