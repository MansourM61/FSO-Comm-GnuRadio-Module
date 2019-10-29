/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "Channel_Analyser_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    Channel_Analyser_ff::sptr
    Channel_Analyser_ff::make(bool mode, int ChunkSize, int SamplingOffset, float BandWidth, float SampRate)
    {
      return gnuradio::get_initial_sptr
        (new Channel_Analyser_ff_impl(mode, ChunkSize, SamplingOffset, BandWidth, SampRate));
    }

    /*
     * The private constructor
     */
    Channel_Analyser_ff_impl::Channel_Analyser_ff_impl(bool mode, int ChunkSize, int SamplingOffset, float BandWidth, float SampRate)
      : gr::sync_decimator("Channel_Analyser_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 4, sizeof(float)), 1), bMode(mode), uiChunkSize(ChunkSize), siSamplingOffset(SamplingOffset), ufBandWidth(BandWidth), ufSampRate(SampRate), iChunckIndex(0)
    {
      initialise();  // initialise parameters and decimation factor
    }

    void
    Channel_Analyser_ff_impl::initialise(void)
    {
      float PulseDuration = 1.0/ufBandWidth;  // pulse duration (s)
      float SampleTime = 1.0/ufSampRate;  // sampling time (s)
      fSampPerPulse = PulseDuration/SampleTime;  // number of samples per pulse
      uiNoSamp =  int(round(fSampPerPulse*uiChunkSize));  // number of samples per chunck of bits

      // make sure sampling offset is within th valid range
      siSamplingOffset = ( siSamplingOffset > +int(fSampPerPulse/2.0) ) ? +int(fSampPerPulse/2.0) : siSamplingOffset;
      siSamplingOffset = ( siSamplingOffset < -int(fSampPerPulse/2.0) ) ? -int(fSampPerPulse/2.0) : siSamplingOffset;

      sync_decimator::set_decimation(uiNoSamp);  // set the decimation factor so for the total samples per one chunck, one output sample is created
    }

    /*
     * Our virtual destructor.
     */
    Channel_Analyser_ff_impl::~Channel_Analyser_ff_impl()
    {
    }

    int
    Channel_Analyser_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      iChunckIndex += noutput_items;  // update chunck index

      const float *in = (const float *) input_items[0];  // assign the pointer to the input array

      float *Q_fac = (float *) output_items[0];  // assign the pointer to the output array

      float *Scint_Ind = NULL;
      float *Scint_Ind_0 = NULL;
      float *Scint_Ind_1 = NULL;

      if(output_items.size() == 4)  // if the output ports are connected in the flowgraph, assign the other output pointers
      {
        Scint_Ind = (float *) output_items[1];
        Scint_Ind_0 = (float *) output_items[2];
        Scint_Ind_1 = (float *) output_items[3];
      }

      unsigned int input_len = noutput_items*uiNoSamp;  // number of input samples array

      int Index_O = 0;  // index of output array
      unsigned int No_LS = 0;  // number of proccessed samples in the current chunck

      if (bMode == true) {  //  if the analyser is used for DC input
	// ignore the first rising edge and sampling offset
        float E_1_LS = 0.0;  // initialise averaging variables
        float E_2_LS = 0.0;

        for(int index = 0; index < input_len; index += int(fSampPerPulse))  // go through the input array with the step equal to a pulse sample
	{
	   E_1_LS += in[index];  // update the averaging variables
	   E_2_LS += POW2(in[index]);
	   ++No_LS;

	   if (No_LS % uiChunkSize == 0) {  // if correct number of samples are scanned, update the output array accordingly
             E_1_LS /= No_LS;  // calculate the average
             E_2_LS /= No_LS;

   	     Q_fac[Index_O] = -1.0;  // update the output array for current output index 
	     Scint_Ind[Index_O] = E_2_LS/POW2(E_1_LS) - 1.0;
	     Scint_Ind_0[Index_O] = -1.0;
	     Scint_Ind_1[Index_O] = -1.0;

	     ++Index_O;  // update the output index
	     if(Index_O >= noutput_items) break;  // make sure extra data is not generated
             E_1_LS = 0.0;  // reset the averaging variables
             E_2_LS = 0.0;
             No_LS = 0;  // reset number of scanned sample
	   }	     
        }

      } else {  //  if the analyser is used for random pulse input

        float E_1_L0 = 0.0;  // initialise averaging variables
        float E_2_L0 = 0.0;
        unsigned int No_L0 = 0;
        float E_1_L1 = 0.0;
        float E_2_L1 = 0.0;
        unsigned int No_L1 = 0;

	float mu_0 = 0.0;
	float mu_1 = 0.0;
	float sig_0 = 0.0;
	float sig_1 = 0.0;

        float thresh = 0;
	unsigned int Index_S0 = FindFirstRisingEdge(in, input_len, &thresh) + int(fSampPerPulse/2.0) + siSamplingOffset;  // find the first riging edge of the incoming pulse sequence abnd update the threshold level

        for(int index = Index_S0; index < input_len; index += int(fSampPerPulse))  // go through the input array with the step equal to a pulse sample
	{
	  if(in[index] < thresh) {  // if the input pulse level is less threshold level; level = '0'
	    E_1_L0 += in[index];  //update the averaging variables of level '0'
	    E_2_L0 += POW2(in[index]);
	    ++No_L0;
	  } else {  // if the input pulse level is less threshold level; level = '1'
	    E_1_L1 += in[index];  //update the averaging variables of level '1'
	    E_2_L1 += POW2(in[index]);
	    ++No_L1;	  
	  }
	  ++No_LS;  // update number od scanned sample

	  if (No_LS % uiChunkSize == 0) {  // if correct number of samples are scanned, update the output array accordingly
	    E_1_L0 /= No_L0;  // calculate the average
	    E_2_L0 /= No_L0;

	    E_1_L1 /= No_L1;
	    E_2_L1 /= No_L1;

	    mu_0 = E_1_L0;
	    mu_1 = E_1_L1;
	    sig_0 = sqrt(E_2_L0 - POW2(E_1_L0));
	    sig_1 = sqrt(E_2_L1 - POW2(E_1_L1));
	     
   	    Q_fac[Index_O] = abs(mu_1 - mu_0) / (sig_1 + sig_1);  // calculate Q-factor nad update output arrays

	    Scint_Ind[Index_O] = -1.0;
	    Scint_Ind_0[Index_O] = E_2_L0/POW2(E_1_L0) - 1.0;
	    Scint_Ind_1[Index_O] = E_2_L1/POW2(E_1_L1) - 1.0;

	    ++Index_O;  // update the output index
	    if(Index_O >= noutput_items) break;  // make sure extra data is not generated
            E_1_L0 = 0.0;  // reset averaging variables
            E_2_L0 = 0.0;
            E_1_L1 = 0.0;
            E_2_L1 = 0.0;
            No_L0 = 0;  // reset number of scanned sample
            No_L1 = 0;
	    No_LS = 0;
	   }	     

         }

      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }


    unsigned int
    Channel_Analyser_ff_impl::FindFirstRisingEdge(const float *InArray, unsigned int input_len, float *mean_val)
    {
      float max_val = 0;
      float min_val = 0;
      *mean_val = 0.0;
      for(int index = 0; index < input_len; index++) {  // go through the samples and find maximum, minimum, and mean values
	if(InArray[index] > max_val) {  // if the sample is larger than the maximum value
	  max_val = InArray[index];
	} else {  // or 
	  if(InArray[index] < min_val) min_val = InArray[index];  // if the sample is less than the minimum value update the minimum value
	}
	*mean_val += InArray[index];
      }

      *mean_val /= input_len;  // calculate the mean value

      float F1, F2;
      int Index_E = 0;
      for(int index = 0; index < input_len - 1; ++index) {  // go through the samples and test the rising edge on the normalised values with indices i and i+1
	F1 = (2*InArray[index] - (max_val + min_val)) / (max_val - min_val);  // calculate the normalised sample with index i
	F2 = (2*InArray[index + 1] - (max_val + min_val)) / (max_val - min_val);  // calculate the normalised sample with index i	  
	if ((F1 < 0) && (F2 >= 0)) {  // if it is a rising edge
	  Index_E = index + 1;  // update index of risign edge and quit the loop
	  break;
	}
      }
      return Index_E;   // return the index of rising edge
    }

  } /* namespace FSO_Comm */
} /* namespace gr */

