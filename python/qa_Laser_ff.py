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

class qa_Laser_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# test parameters
	output_pow = 1e-3
	wavelen = 850e-9
	ext_ratio = 20
        src_data = (0, 1, 1, 0, 1)
	# calculate laser output pattern
	expected_result = self.LaserOut(src_data, output_pow, ext_ratio)
	# create blocks and connect flowgraph
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Laser_ff(output_pow, wavelen, ext_ratio)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        # set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check accuracy of calculated values from blocks 
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def LaserOut(self, Bits, output_pow, ext_ratio):
	# calculate laser output box
      	mean_val = 0;
      	max_val = 0;
      	min_val = 0;
      	for num in Bits:  # go through the samples and find maximum, minimum, and mean values
	  if num > max_val:
	    max_val = num
	  else:
	    if(num < min_val):
	      min_val = num
	  mean_val += num
      	P_l = 2.0*output_pow / (1.0 + ext_ratio)  # optical signal low level amplitude (W)
      	P_h = 2.0*output_pow / (1.0 + 1.0/ext_ratio)  # optical signal high level amplitude (W)
      	Del_P = P_h - P_l  # optical signal amplitude (W)
	out = [0, ] * len(Bits)
        # normalise input signal
      	for index, num in enumerate(Bits):  # go through the samples and apply the lasdr characteristic parameter
	  out[index] = (2*num - (max_val + min_val)) / (max_val - min_val)  # normalise optical signal
  	  out[index] = out[index]*Del_P/2.0 + output_pow  # scale optical signal
	return out

if __name__ == '__main__':
    gr_unittest.run(qa_Laser_ff, "qa_Laser_ff.xml")
