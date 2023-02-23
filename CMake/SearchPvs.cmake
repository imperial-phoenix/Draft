# Модуль определения доступности Pvs в системе

# PATH_TO_SUBMODULES[in]  Путь до папки с внешними проектами
# IS_PVS_AVAILABLE[out]   Флаг доступности Pvs
function(is_pvs_available PATH_TO_SUBMODULES)
   if (WIN32)
      message(WARNING "PVS not available on Windows now")
   else()
      SET(PVS_STUDIO_BIN "pvs-studio-analyzer")
      SET(PVS_STUDIO_CONVERTER "plog-converter")
   endif()

   # Изначально полагаем, что PVS не найден
   SET(IS_PVS_AVAILABLE FALSE)

   find_program(PVS_STUDIO_BIN_PATH "${PVS_STUDIO_BIN}")

   if (EXISTS ${PVS_STUDIO_BIN_PATH})
      message(STATUS "pvs-studio-analyzer is found in ${PVS_STUDIO_BIN_PATH}")
   else()
      message(STATUS "pvs-studio-analyzer is not found")
   endif()

   find_program(PVS_STUDIO_CONVERTER_PATH "${PVS_STUDIO_CONVERTER}")

   if (EXISTS ${PVS_STUDIO_CONVERTER_PATH})
      message(STATUS "plog-converter is found in ${PVS_STUDIO_CONVERTER_PATH}")
   else()
      message(STATUS "plog-converter is not found")
   endif()

   if (PVS_STUDIO_BIN_PATH       AND
       PVS_STUDIO_CONVERTER_PATH AND
       EXISTS ${PATH_TO_SUBMODULES}/Pvs/PVS-Studio.cmake)
      SET(IS_PVS_AVAILABLE TRUE PARENT_SCOPE)
   else()
      SET(IS_PVS_AVAILABLE FALSE PARENT_SCOPE)
   endif()

endfunction()