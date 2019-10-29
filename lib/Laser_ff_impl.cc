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
#include "Laser_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    Laser_ff::sptr
    Laser_ff::make(float P_avg, float Wavelen, float ExtRatio)
    {
      return gnuradio::get_initial_sptr
        (new Laser_ff_impl(P_avg, Wavelen, ExtRatio));
    }

    /*
     * The private constructor
     */
    Laser_ff_impl::Laser_ff_impl(float P_avg, float Wavelen, float ExtRatio)
      : gr::sync_block("Laser_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), fP_avg(P_avg), fWavelen(Wavelen), fExtRatio(ExtRatio)
    {}

    /*
     * Our virtual destructor.
     */
    Laser_ff_impl::~Laser_ff_impl()
    {
    }

    int
    Laser_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];  // assign the pointer to the input array
      float *out = (float *) output_items[0];  // assign the pointer to the output array

      float max_val = 0;
      float min_val = 0;
      for(int index = 0; index < noutput_items; index++) {  // go through the samples and find mean, maximum, minimum values
	if(in[index] > max_val) {  // if the sample is larger than maximum value
	  max_val = in[index];  // update the maximum value
	} else {  // or
	  if(in[index] < min_val) min_val = in[index];  // if the sample is less than minimum value, update the minimum value
	}
      }

      float P_l = 2.0*fP_avg / (1.0 + fExtRatio);  // optical signal low level amplitude (W)
      float P_h = 2.0*fP_avg / (1.0 + 1.0/fExtRatio);  // optical signal high level amplitude (W)

      float Del_P = P_h - P_l;  // optical signal amplitude (W)

      // normalise input signal
      for(int index = 0; index < noutput_items; index++) {  // go through the samples and apply the laser characteristic parameters
	out[index] = (2*in[index] - (max_val + min_val)) / (max_val - min_val);  // normalise optical signal
	out[index] = out[index]*Del_P/2.0 + fP_avg;  // scale optical signal
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace FSO_Comm */
} /* namespace gr */

