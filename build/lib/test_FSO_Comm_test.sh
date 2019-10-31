#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/lib
export PATH=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/build/lib:$PATH
export LD_LIBRARY_PATH=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-FSO_Comm 
