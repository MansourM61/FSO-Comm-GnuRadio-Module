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

class qa_Pointing_Errors_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# test parameters
	Jitter = 0.2
	linklen = 20
	Tx_Dia = 5e-3
	Tx_theta = 3
	Rx_Dia = 0.5
	Time_Correlation = 20e-3
	SampleRate = 32e3
	# calculate the pointing errors channel coefficient
        W_Rx = Tx_Dia/2.0 + linklen*math.tan(Tx_theta*math.pi/180.0)  # beam radius at Rx side
        v_PE = math.sqrt(math.pi/2.0)*(Rx_Dia/(2.0*W_Rx))  # aperture to vertical beam size ratio
        W2_eq_PE = (W_Rx*W_Rx)*math.sqrt(math.pi)*math.erf(v_PE)/(2.0*v_PE*math.exp(-(v_PE*v_PE)))  # equivalent vertical beam size at receiver side
	gam = math.sqrt(W2_eq_PE)/(2.0*Jitter)
	mean_val_c = gam**2/(1 + gam**2)
	var_val_c = gam**2.0/(2.0 + gam**2.0) - gam**4.0/( (1.0 + gam**2.0)**2 )
	# create blocks and connect flowgraph
        src_data = (1, )*1000000
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Pointing_Errors_ff(Jitter, linklen, Tx_Dia, Tx_theta, Rx_Dia, Time_Correlation, SampleRate)
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
        self.assertAlmostEqual(round(mean_val_c*10), round(mean_val*10), 0)
        self.assertAlmostEqual(round(var_val_c*1e2), round(var_val*1e2), 0)	

if __name__ == '__main__':
    gr_unittest.run(qa_Pointing_Errors_ff, "qa_Pointing_Errors_ff.xml")
