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

class qa_Turbulence_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# test parameters
	Cn2 = 1e-12
	wavelen = 850e-9
	linklen = 200
	Rx_Dia = 50e-3
	Time_Correlation = 25e-3
	# calculate turbulence channel coeeficient
	k = 2.0*math.pi/wavelen  # wave number (rad/m)
    	sig2_R = 1.23*Cn2*pow(k, 7.0/6.0)*pow(linklen, 11.0/6.0)  # Rytov variance
    	D_AAF = math.sqrt(k*(Rx_Dia*Rx_Dia)/(4.0*linklen))  # auxilary parameter for aperture averaging effect
    	AAF = pow(1.0 + 1.062*(D_AAF*D_AAF), -7.0/6.0)  # aperture averaging factor
    	sig_x = math.sqrt(AAF*sig2_R/4.0)  # sigma parameter weak turbulence
    	mu_x = -AAF*sig2_R/4.0  # mu parameter weak turbulence
	mean_val_c = math.exp(mu_x + 0.5*sig_x**2.0)
	var_val_c = 4.0*(math.exp(sig_x**2.0) - 1.0) * math.exp(2.0*mu_x + sig_x**2.0)
	SampleRate = 32e3
	# create blocks and connect flowgraph
        src_data = (1, )*1000000
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Turbulence_ff(Cn2, wavelen, linklen, Rx_Dia, Time_Correlation, SampleRate)
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
        self.assertAlmostEqual(round(mean_val_c), round(mean_val), 0)
        self.assertAlmostEqual(round(var_val_c*1e2), round(var_val*1e2), 0)	

if __name__ == '__main__':
    gr_unittest.run(qa_Turbulence_ff, "qa_Turbulence_ff.xml")
