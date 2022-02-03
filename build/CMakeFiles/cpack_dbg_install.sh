#!/usr/bin/bash
#
# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
#
# Script used for installing a project for CPack. Hiding any build errors
# from the package generator.
#

# Turn off error reporting:
set +e

# Set the output directory:
OUTDIR=${DESTDIR}/usr/WorkDir/21.2.193/InstallArea/x86_64-centos7-gcc8-opt

# Create the bin and lib directories:
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.18.3/Linux-x86_64/bin/cmake -E make_directory ${OUTDIR}/bin
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.18.3/Linux-x86_64/bin/cmake -E make_directory ${OUTDIR}/lib

# Copy the debug files into the place CPack expects to find them:
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.18.3/Linux-x86_64/bin/cmake -E copy /home/tnom6927/AnalysisFramework/FourTopsGNNSampleProduction/FourTopsGNNSampleProduction/build/x86_64-centos7-gcc8-opt/bin/*.dbg \
    ${OUTDIR}/bin/
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.18.3/Linux-x86_64/bin/cmake -E copy /home/tnom6927/AnalysisFramework/FourTopsGNNSampleProduction/FourTopsGNNSampleProduction/build/x86_64-centos7-gcc8-opt/lib/*.dbg \
    ${OUTDIR}/lib/

# Exit gracefully:
exit 0
