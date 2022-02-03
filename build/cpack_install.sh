#!/usr/bin/bash
#
# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
#
# Script used for installing a project for CPack. Hiding any build errors
# from the package generator.
#

# Turn off error reporting:
set +e

# Make sure that the project is built. The DESTDIR setting is just to make sure
# that some strange build steps don't interfere with the installation.
#DESTDIR=/ make -k

# Install the project:
DESTDIR=${DESTDIR}/usr/WorkDir/21.2.193 \
    make -k install/fast

# Remove the .dbg files from being packaged, in case we are in RelWithDebInfo
# build mode:
rm -f ${DESTDIR}/usr/WorkDir/21.2.193/InstallArea/x86_64-centos7-gcc8-opt/bin/*.dbg
rm -f ${DESTDIR}/usr/WorkDir/21.2.193/InstallArea/x86_64-centos7-gcc8-opt/lib/*.dbg

# Exit gracefully:
exit 0
