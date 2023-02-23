# Headers common to all projects
set(SHARED_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/Include)

# List of targets to Pvs
set(PVS_TARGET_LIST)

# Subdirectories
add_subdirectory(CList)

# Pvs target
if (IS_PVS_AVAILABLE)

   include(${PROJECT_SOURCE_DIR}/Extern/Pvs/PVS-Studio.cmake)

   add_custom_target(RmPvsLog
      COMMAND ${CMAKE_COMMAND} -E rm -r -f ${PROJECT_SOURCE_DIR}/Output/PvsReport)

   pvs_studio_add_target(TARGET Pvs ALL
                         FORMAT fullhtml
                         ANALYZE ${PVS_TARGET_LIST}
                         MODE GA:1,2
                         LOG ${PROJECT_SOURCE_DIR}/Output/PvsReport)

   add_dependencies(Pvs RmPvsLog)

endif()