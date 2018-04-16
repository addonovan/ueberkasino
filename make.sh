#!/bin/bash

# set up opensplice
export OSPL_HOME=${HOME}/OSPL
export OSPL_URI=file://ospl.xml
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${OSPL_HOME}/lib
export PATH=${PATH}:${OSPL_HOME}/bin

# source the opensplice stuff
cwd="$(pwd)"
cd ${OSPL_HOME}
source ${OSPL_HOME}/release.com > /dev/null
cd "$cwd"

echo "OSPL_HOME         ${OSPL_HOME}"
echo "OSPL_URI          ${OSPL_URI}"
echo "LD_LIBRARY_PATH   ${LD_LIBRARY_PATH}"

echo ""
echo ""

# actually make with all of the arguments we got
make "$@"
