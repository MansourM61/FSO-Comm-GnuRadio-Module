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

class qa_Optical_Receiver_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# test parameters
    	Resp = 0.5
    	Gain = 1e3
    	Impedance = 50
	noise_pow = 0.0
	# calculate conversion gain
	ConvCoeff = 1.0*Resp * Gain / Impedance
	# create blocks and connect flowgraph
        src_data = (0, 1, 2, 3, 4)
        expected_result = tuple(x*ConvCoeff for x in src_data)
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Optical_Receiver_ff(Resp, Gain, Impedance, noise_pow)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
	# set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check accuracy of calculated values from blocks 
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)
	
    def test_002_t (self):
	# test parameters
    	Resp = 0.5
    	Gain = 1e3
    	Impedance = 50
	noise_pow = 1e-6
	# create blocks and connect flowgraph
        src_data = (1, )*100000
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Optical_Receiver_ff(Resp, Gain, Impedance, noise_pow)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
	# set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	mean_val = sum(result_data)/len(result_data)
	var_val = sum((x - mean_val) ** 2 for x in result_data) / len(result_data)
	# check accuracy of calculated values from blocks 
        self.assertAlmostEqual(10, mean_val, 0)
        self.assertAlmostEqual(2, round(var_val*1e8), 0)	

if __name__ == '__main__':
    gr_unittest.run(qa_Optical_Receiver_ff, "qa_Optical_Receiver_ff.xml")
