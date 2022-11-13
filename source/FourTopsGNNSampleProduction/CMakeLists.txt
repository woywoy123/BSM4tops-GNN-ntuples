atlas_subdir( FourTopsGNNSampleProduction None)

atlas_depends_on_subdirs( PUBLIC
                          xAODTruth
                          TopAnalysis)

find_package( ROOT REQUIRED COMPONENTS Core Gpad Tree Hist RIO MathCore Graf)

atlas_add_root_dictionary(FourTopsGNNSampleProduction _cintDictSource
                          ROOT_HEADERS ROOT/LinkDef.h
                          EXTERNAL_PACKAGES ROOT)

atlas_add_library( FourTopsGNNSampleProduction ROOT/*.cxx Root/*.h
                   FourTopsGNNSampleProduction/*.h FourTopsGNNSampleProduction/*/*.h 
                   ${_cintDictSource}
                   PUBLIC_HEADERS FourTopsGNNSampleProduction 
                   LINK_LIBRARIES TopAnalysis xAODTruth ${ROOT_LIBRARIES}
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} )

atlas_install_data( DIRECTORY share/* )
