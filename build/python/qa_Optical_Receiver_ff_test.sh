#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/mojtaba/Documents/gr-FSO_Comm/python
export PATH=/home/mojtaba/Documents/gr-FSO_Comm/build/python:$PATH
export LD_LIBRARY_PATH=/home/mojtaba/Documents/gr-FSO_Comm/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/mojtaba/Documents/gr-FSO_Comm/build/swig:$PYTHONPATH
/usr/bin/python2 /home/mojtaba/Documents/gr-FSO_Comm/python/qa_Optical_Receiver_ff.py 
