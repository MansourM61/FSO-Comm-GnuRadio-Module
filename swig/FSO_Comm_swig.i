/* -*- c++ -*- */

#define FSO_COMM_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "FSO_Comm_swig_doc.i"

%{
#include "FSO_Comm/Channel_Analyser_ff.h"
#include "FSO_Comm/Geometric_Loss_ff.h"
#include "FSO_Comm/Laser_ff.h"
#include "FSO_Comm/Optical_Receiver_ff.h"
#include "FSO_Comm/Pointing_Errors_ff.h"
#include "FSO_Comm/Turbulence_ff.h"
#include "FSO_Comm/FogSmoke_Loss_ff.h"
%}


%include "FSO_Comm/Channel_Analyser_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, Channel_Analyser_ff);
%include "FSO_Comm/Geometric_Loss_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, Geometric_Loss_ff);
%include "FSO_Comm/Laser_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, Laser_ff);
%include "FSO_Comm/Optical_Receiver_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, Optical_Receiver_ff);
%include "FSO_Comm/Pointing_Errors_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, Pointing_Errors_ff);
%include "FSO_Comm/Turbulence_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, Turbulence_ff);

%include "FSO_Comm/FogSmoke_Loss_ff.h"
GR_SWIG_BLOCK_MAGIC2(FSO_Comm, FogSmoke_Loss_ff);
