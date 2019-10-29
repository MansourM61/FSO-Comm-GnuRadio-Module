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
#include "Optical_Receiver_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    Optical_Receiver_ff::sptr
    Optical_Receiver_ff::make(float Resp, float G_TIA, float Imp, float P_n)
    {
      return gnuradio::get_initial_sptr
        (new Optical_Receiver_ff_impl(Resp, G_TIA, Imp, P_n));
    }

    /*
     * The private constructor
     */
    Optical_Receiver_ff_impl::Optical_Receiver_ff_impl(float Resp, float G_TIA, float Imp, float P_n)
      : gr::sync_block("Optical_Receiver_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), fResp(Resp), fG_TIA(G_TIA), fImp(Imp), fP_n(P_n), iGaussGenCounter(0)
    {
	memset(fGaussGenArray, 0, sizeof(float)*2);  // initialise the array
    }

    /*
     * Our virtual destructor.
     */
    Optical_Receiver_ff_impl::~Optical_Receiver_ff_impl()
    {
    }

    int
    Optical_Receiver_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];  // assign the pointer to the input array
      float *out = (float *) output_items[0];  // assign the pointer to the output array

      float Rec_Gain = fResp*fG_TIA/fImp;  // calculate the optical receiver conversion gain
      float I_n = sqrt(fP_n/fImp);  // calculate the noise current

      for(int index = 0; index < noutput_items; index++) {  // go through the input samples and convert input optical power to electrical signal including noise
	out[index] = in[index]*Rec_Gain + I_n*GaussNormNumGen();        
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    float
    Optical_Receiver_ff_impl::GaussNormNumGen(void)
    {
      // the code is adopted from 'https://rosettacode.org/wiki/Statistics/Normal_distribution#C'

      ++iGaussGenCounter;
      // Marsaglia polar method
      // https://en.wikipedia.org/wiki/Marsaglia_polar_method
      if (iGaussGenCounter%2 != 0) {  // generating random numbers
        float x, y, rsq, f;  // temporary variables
        do {
            x = 2.0 * rand() / (float)RAND_MAX - 1.0;  // x point calculation
            y = 2.0 * rand() / (float)RAND_MAX - 1.0;  // y point calculation
            rsq = x * x + y * y;  // calculate distance
        } while(rsq >= 1.0 || rsq == 0.0);  // repeat the calculation till the points are in the square

        f = sqrt(-2.0*log(rsq)/rsq);  // auxiliary value
        fGaussGenArray[0] = x*f;  // first random value
        fGaussGenArray[1] = y*f;  // second random value

        return fGaussGenArray[0];
      }
      else {  // returning already calculated number
        return fGaussGenArray[1];
      }
    }


  } /* namespace FSO_Comm */
} /* namespace gr */

