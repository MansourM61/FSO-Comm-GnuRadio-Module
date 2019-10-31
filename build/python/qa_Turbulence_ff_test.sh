#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/python
export PATH=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/build/python:$PATH
export LD_LIBRARY_PATH=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/build/swig:$PYTHONPATH
/usr/bin/python2 /home/mojtaba/Documents/gr-FSO_Comm/FSO-Comm-GnuRadio-Module/python/qa_Turbulence_ff.py 
