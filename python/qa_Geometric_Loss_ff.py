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

class qa_Geometric_Loss_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# test parameters
        src_data = (0, 1, 2, 3, 4)
	Tx_Dia = 3e-3
	Tx_theta = 0.2
	linklen = 100
	Rx_Dia = 50e-3
	# calculate geometric loss
	L = self.GeoLoss(Tx_Dia, Tx_theta, linklen, Rx_Dia)
	# create the blocks and connect the flowgraph
        expected_result = (0, 1*L, 2*L, 3*L, 4*L)
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Geometric_Loss_ff(Tx_Dia, Tx_theta, linklen, Rx_Dia)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        # set up fg
        self.tb.run ()
        # check data
        result_data = dst.data()
	# check the validaty of the calculated results
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)
	
    def GeoLoss(self, Tx_Dia, Div_ang, LinkLen, Rx_Dia):
	# calculate geometry loss based on geometric optics beam propagation
      	Beam_Dia = 2.0*math.tan(math.pi*Div_ang/180.0)*LinkLen + Tx_Dia;  # beam diameter at receiver side (m)
      	Loss = (Rx_Dia/Beam_Dia) * (Rx_Dia/Beam_Dia);  # geometric loss
      	Loss = 1.0 if (Loss > 1.0 or Loss < 0.0) else Loss  # assure the validity of calculated loss
	return Loss

if __name__ == '__main__':
    gr_unittest.run(qa_Geometric_Loss_ff, "qa_Geometric_Loss_ff.xml")
