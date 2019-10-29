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
#include "FogSmoke_Loss_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    FogSmoke_Loss_ff::sptr
    FogSmoke_Loss_ff::make(float Wavelen, float LinkLen, float Vis)
    {
      return gnuradio::get_initial_sptr
        (new FogSmoke_Loss_ff_impl(Wavelen, LinkLen, Vis));
    }

    /*
     * The private constructor
     */
    FogSmoke_Loss_ff_impl::FogSmoke_Loss_ff_impl(float Wavelen, float LinkLen, float Vis)
      : gr::sync_block("FogSmoke_Loss_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), fWavelen(Wavelen), fLinkLen(LinkLen), fVis(Vis)
    {}

    /*
     * Our virtual destructor.
     */
    FogSmoke_Loss_ff_impl::~FogSmoke_Loss_ff_impl()
    {
    }

    int
    FogSmoke_Loss_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      float q = 0;   // q parameter
      float Vis = fVis/1.0e3;  // convert distances from metre to kilometre
      float LinkLen = fLinkLen/1.0e3;

      if(Vis > 50.0) {  // select proper 'q' value based on Kim model
        q = 1.6;
      } else if (Vis <= 50.0 && Vis > 6.0) {
        q = 1.3;
      } else if (Vis <= 6.0 && Vis > 1.0) {
        q = 0.67*Vis + 0.34;
      } else if (Vis <= 1.0 && Vis > 0.5) {
        q = Vis + 0.5;
      } else {
	q = 0.0;
      }

      float fbeta_l = (-log(T_TH_FS)/Vis) * pow(fWavelen/LAMBDA_0, -q);  // calculate the atttenuation coefficient

      float FogSmokeLoss = exp(-fbeta_l*LinkLen);  // calculate the loss coefficent

      for(int index = 0; index < noutput_items; index++) {  // go through the input and apply the channel coefficient to them
	out[index] = in[index] * FogSmokeLoss;
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace FSO_Comm */
} /* namespace gr */

