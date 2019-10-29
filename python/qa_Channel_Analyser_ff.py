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

class qa_Channel_Analyser_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# test parameters
	mode = True
	ChunckSize = 47
	SampleOffset = 0
	BandWidth = 10e3
	SampleRate = 32000
	NoSampPerBit = 10
	# create the blocks and connect the flowgraph
        src_raw = [1, 0, 0, 1, 0, 1, 0, 1, 1, 0]
	src_bits = [[x,]*NoSampPerBit for x in src_raw]
	src_data = [item for sublist in src_bits for item in sublist]*1000	
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Channel_Analyser_ff(mode, ChunckSize, SampleOffset, BandWidth, SampleRate)
        dst_Q = blocks.vector_sink_f()
        dst_Scint_Ind = blocks.vector_sink_f()
        dst_Scint_Ind_0 = blocks.vector_sink_f()
        dst_Scint_Ind_1 = blocks.vector_sink_f()
        self.tb.connect(src, (sqr, 0))
        self.tb.connect((sqr, 0), dst_Q)
        self.tb.connect((sqr, 1), dst_Scint_Ind)
        self.tb.connect((sqr, 2), dst_Scint_Ind_0)
        self.tb.connect((sqr, 3), dst_Scint_Ind_1)
        # set up fg
        self.tb.run()
        # check data
        result_data_Q = dst_Q.data()
        result_data_Scint_Ind = dst_Scint_Ind.data()
	result_data_Scint_Ind_0 = dst_Scint_Ind_0.data()
	result_data_Scint_Ind_1 = dst_Scint_Ind_1.data()
	# calculate the averages based on the input date
	E_1_L0 = sum(src_data)*1.0/len(src_data)	
	E_2_L0 = sum([x**2 for x in src_data])*1.0/len(src_data)
	Scint_Ind_c = E_2_L0/(E_1_L0**2) - 1.0
	# check accuracy of calculated values from blocks
        self.assertAlmostEqual(1.0*sum(result_data_Q)/len(result_data_Q), -1.0, 0)
        self.assertAlmostEqual(Scint_Ind_c, 1.0*sum(result_data_Scint_Ind)/len(result_data_Scint_Ind), 0)	
        self.assertAlmostEqual(1.0*sum(result_data_Scint_Ind_0)/len(result_data_Scint_Ind_0), -1.0, 0)
        self.assertAlmostEqual(1.0*sum(result_data_Scint_Ind_1)/len(result_data_Scint_Ind_1), -1.0, 0)

    def Dir (self):
	# test parameters
	mode = False
	ChunckSize = 100
	SampleOffset = 0
	BandWidth = 10e3
	SampleRate = 32000
	NoSampPerBit = 10
	# create the blocks and connect the flowgraph
        src_raw = [1, 0.1, -0.2, 1.5, 0.2, 0.95, 0.1, 1.25, 0.75, -0.25]
	src_bits = [[x,]*NoSampPerBit for x in src_raw]
	src_data = [item for sublist in src_bits for item in sublist]*1000	
        src = blocks.vector_source_f(src_data)
        sqr = FSO_Comm.Channel_Analyser_ff(mode, ChunckSize, SampleOffset, BandWidth, SampleRate)
        dst_Q = blocks.vector_sink_f()
        dst_Scint_Ind = blocks.vector_sink_f()
        dst_Scint_Ind_0 = blocks.vector_sink_f()
        dst_Scint_Ind_1 = blocks.vector_sink_f()
        self.tb.connect(src, (sqr, 0))
        self.tb.connect((sqr, 0), dst_Q)
        self.tb.connect((sqr, 1), dst_Scint_Ind)
        self.tb.connect((sqr, 2), dst_Scint_Ind_0)
        self.tb.connect((sqr, 3), dst_Scint_Ind_1)
        # set up fg
        self.tb.run()
        # check data
        result_data_Q = dst_Q.data()
        result_data_Scint_Ind = dst_Scint_Ind.data()
	result_data_Scint_Ind_0 = dst_Scint_Ind_0.data()
	result_data_Scint_Ind_1 = dst_Scint_Ind_1.data()
	# calculate the averages based on the input date
	max_val = max(src_data)
	min_val = min(src_data)
	thresh = 1.0*sum(src_data)/len(src_data)
	PulseDur = 1.0/BandWidth
	SampTime = 1.0/SampleRate
	SampPerPulse = PulseDur/SampTime
	Index_E = 0
	for index in range(0, len(src_data) - 1):
	  F1 = (2.0*src_data[index] - (max_val + min_val)) / (max_val - min_val);
	  F2 = (2.0*src_data[index + 1] - (max_val + min_val)) / (max_val - min_val);	  

	  if (F1 < 0) and (F2 >= 0):
	    Index_E = index + 1
	    break
	Index_S = Index_E + int(round(SampPerPulse/2.0)) + SampleOffset
	L_S = src_data[Index_S::int(SampPerPulse)]
	L_0_raw = [[x,] if x < thresh else [] for x in L_S]
	L_0 = [item for sublist in L_0_raw for item in sublist]
	L_1_raw = [[x,] if x >= thresh else [] for x in L_S]
	L_1 = [item for sublist in L_1_raw for item in sublist]
	E_1_L0 = sum(L_0)*1.0/len(L_0)	
	E_2_L0 = sum([x**2 for x in L_0])*1.0/len(L_0)
	Scint_Ind_0_c = E_2_L0/(E_1_L0**2) - 1.0
	E_1_L1 = sum(L_1)*1.0/len(L_1)	
	E_2_L1 = sum([x**2 for x in L_1])*1.0/len(L_1)
	Scint_Ind_1_c = E_2_L1/(E_1_L1**2) - 1.0
	var_L0 = E_2_L0 - E_1_L0**2
	var_L1 = E_2_L1 - E_1_L1**2
	Q_Factory_c = 1.0*abs(E_1_L1 - E_1_L0) / (math.sqrt(var_L1) + math.sqrt(var_L0))
	print(result_data_Scint_Ind_0)
	# check accuracy of calculated values from blocks 
        self.assertAlmostEqual(math.floor(Q_Factory_c), math.floor(1.0*sum(result_data_Q)/len(result_data_Q)), 0)
        self.assertAlmostEqual(-1.0, 1.0*sum(result_data_Scint_Ind)/len(result_data_Scint_Ind), 0)	
        self.assertAlmostEqual(math.floor(Scint_Ind_0_c), math.floor(1.0*sum(result_data_Scint_Ind_0)/len(result_data_Scint_Ind_0)), 0)
        self.assertAlmostEqual((Scint_Ind_1_c), (1.0*sum(result_data_Scint_Ind_1)/len(result_data_Scint_Ind_1)), 0)

if __name__ == '__main__':
    gr_unittest.run(qa_Channel_Analyser_ff, "qa_Channel_Analyser_ff.xml")
