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
#include "Geometric_Loss_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    Geometric_Loss_ff::sptr
    Geometric_Loss_ff::make(float Tx_Dia, float Tx_DivAng, float LinkLen, float Rx_Dia)
    {
      return gnuradio::get_initial_sptr
        (new Geometric_Loss_ff_impl(Tx_Dia, Tx_DivAng, LinkLen, Rx_Dia));
    }

    /*
     * The private constructor
     */
    Geometric_Loss_ff_impl::Geometric_Loss_ff_impl(float Tx_Dia, float Tx_DivAng, float LinkLen, float Rx_Dia)
      : gr::sync_block("Geometric_Loss_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), fTx_Dia(Tx_Dia), fTx_DivAng(Tx_DivAng), fLinkLen(LinkLen), fRx_Dia(Rx_Dia)
    {}

    /*
     * Our virtual destructor.
     */
    Geometric_Loss_ff_impl::~Geometric_Loss_ff_impl()
    {
    }

    int
    Geometric_Loss_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];  // assign the pointer to the input array
      float *out = (float *) output_items[0];  // assign the pointer to the output array

      float Beam_Dia = 2.0*tan(M_PI*fTx_DivAng/180.0)*fLinkLen + fTx_Dia;  // beam diameter at receiver side (m)

      float GeoLoss = (fRx_Dia/Beam_Dia) * (fRx_Dia/Beam_Dia);  // calculate geometric loss coefficient

      GeoLoss = (GeoLoss > 1.0 || GeoLoss < 0.0) ? 1.0 : GeoLoss;  // assure the geometric loss value is valid

      for(int index = 0; index < noutput_items; index++) {  // go through the input array and apply the channel coefficient
	out[index] = in[index]*GeoLoss;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace FSO_Comm */
} /* namespace gr */

