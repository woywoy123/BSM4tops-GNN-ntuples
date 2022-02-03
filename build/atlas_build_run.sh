#!/usr/bin/bash
#
# Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
#
# This script is used during the build to set up a functional runtime
# environment for running scripts/executables.
#

# Transmit errors:
set -e

# Set up the environment:
source /home/tnom6927/AnalysisFramework/FourTopsGNNSampleProduction/FourTopsGNNSampleProduction/build/x86_64-centos7-gcc8-opt/setup.sh || exit 1

# Run the command:
exec "$@" || exit 1
