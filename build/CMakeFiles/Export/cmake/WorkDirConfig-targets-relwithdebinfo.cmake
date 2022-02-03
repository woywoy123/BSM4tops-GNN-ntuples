#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WorkDir::FourTopsGNNSampleProduction" for configuration "RelWithDebInfo"
set_property(TARGET WorkDir::FourTopsGNNSampleProduction APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(WorkDir::FourTopsGNNSampleProduction PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libFourTopsGNNSampleProduction.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libFourTopsGNNSampleProduction.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS WorkDir::FourTopsGNNSampleProduction )
list(APPEND _IMPORT_CHECK_FILES_FOR_WorkDir::FourTopsGNNSampleProduction "${_IMPORT_PREFIX}/lib/libFourTopsGNNSampleProduction.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
