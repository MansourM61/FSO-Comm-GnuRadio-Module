#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import FSO_Comm_swig as FSO_Comm
import math

class qa_FogSmoke_Loss_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_002_t (self):
	# test parameters
        src_data = (0, 1, 2, 3, 4)
    	wavelen = 850e-9
    	linklen = 100
	visibility = 10e3
	# calculate the loss
	L = self.FogLoss(wavelen, linklen, visibility)
	# create the blocks and connect flowgraph
        expected_result = (0, 1*L, 2*L, 3*L, 4*L)
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.FogSmoke_Loss_ff(wavelen, linklen, visibility)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        # set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check validaty of the output values from block
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_003_t (self):
	# test parameters
        src_data = (0, 1, 2, 3, 4)
    	wavelen = 850e-9
    	linklen = 100
	visibility = 3e3
	# calculate the loss
	L = self.FogLoss(wavelen, linklen, visibility)
	# create the blocks and connect flowgraph
        expected_result = (0, 1*L, 2*L, 3*L, 4*L)
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.FogSmoke_Loss_ff(wavelen, linklen, visibility)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        # set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check validaty of the output values from block
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_004_t (self):
	# test parameters
        src_data = (0, 1, 2, 3, 4)
    	wavelen = 850e-9
    	linklen = 100
	visibility = 0.75e3
	# calculate the loss
	L = self.FogLoss(wavelen, linklen, visibility)
	# create the blocks and connect flowgraph
        expected_result = (0, 1*L, 2*L, 3*L, 4*L)
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.FogSmoke_Loss_ff(wavelen, linklen, visibility)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        # set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check validaty of the output values from block
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_005_t (self):
	# test parameters
        src_data = (0, 1, 2, 3, 4)
    	wavelen = 850e-9
    	linklen = 100
	visibility = 0.1e3
	# calculate the loss
	L = self.FogLoss(wavelen, linklen, visibility)
	# create the blocks and connect flowgraph
        expected_result = (0, 1*L, 2*L, 3*L, 4*L)
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.FogSmoke_Loss_ff(wavelen, linklen, visibility)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        # set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check validaty of the output values from block
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def FogLoss(self, wavelen, linklen, Vis):
	# calculate fog/smoke loss based on Kim model	
	T_TH_FS = 2.0/100.0
	LAMBDA_0 = 550e-9
	Vis = Vis/1000.0
	linklen = linklen/1000.0
      	if(Vis > 50.0):
          q = 1.6;
      	elif (Vis <= 50.0 and Vis > 6.0):
          q = 1.3;
      	elif (Vis <= 6.0 and Vis > 1.0):
          q = 0.67*Vis + 0.34;
      	elif (Vis <= 1.0 and Vis > 0.5):
          q = Vis + 0.5;
	else:
	  q = 0.0
      	fbeta_l = (-math.log(T_TH_FS)/Vis) * pow(wavelen/LAMBDA_0, -q)
      	return math.exp(-fbeta_l*linklen);


if __name__ == '__main__':
    gr_unittest.run(qa_FogSmoke_Loss_ff, "qa_FogSmoke_Loss_ff.xml")
