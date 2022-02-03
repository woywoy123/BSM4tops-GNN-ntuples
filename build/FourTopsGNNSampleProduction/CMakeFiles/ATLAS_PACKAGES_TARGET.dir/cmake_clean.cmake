file(REMOVE_RECURSE
  "../x86_64-centos7-gcc8-opt/include/FourTopsGNNSampleProduction"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/ATLAS_PACKAGES_TARGET.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
