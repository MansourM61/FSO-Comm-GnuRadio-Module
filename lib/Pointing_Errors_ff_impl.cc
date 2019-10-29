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
#include "Pointing_Errors_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    Pointing_Errors_ff::sptr
    Pointing_Errors_ff::make(float Jitter, float LinkLen, float Tx_Dia, float Tx_Theta, float Rx_Dia, float TempCorr, float SampRate)
    {
      return gnuradio::get_initial_sptr
        (new Pointing_Errors_ff_impl(Jitter, LinkLen, Tx_Dia, Tx_Theta, Rx_Dia, TempCorr, SampRate));
    }

    /*
     * The private constructor
     */
    Pointing_Errors_ff_impl::Pointing_Errors_ff_impl(float Jitter, float LinkLen, float Tx_Dia, float Tx_Theta, float Rx_Dia, float TempCorr, float SampRate)
      : gr::sync_block("Pointing_Errors_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), fJitter(Jitter), fLinkLen(LinkLen), fTx_Dia(Tx_Dia), fTx_Theta(Tx_Theta), fRx_Dia(Rx_Dia), fTempCorr(TempCorr), fSampRate(SampRate), iGaussGenCounter(0), ulCounter(0)
    {
	memset(fGaussGenArray, 0.0, sizeof(float)*2);  // initialise the array
    }

    /*
     * Our virtual destructor.
     */
    Pointing_Errors_ff_impl::~Pointing_Errors_ff_impl()
    {
    }

    int
    Pointing_Errors_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];  // assign the pointer to the input array
      float *out = (float *) output_items[0];  // assign the pointer to the output array

      float fF_t = 1.0/fTempCorr;  // turbulence fading maximum frequency (Hz)

      unsigned long Sig2PERatio = int(ceil(fSampRate*1.0/fF_t));  // number of signal samples to number of pointing errors coefficients ratio

      float PECoeff = RayleighNumGen();  // generate a pointing errors channel coeeficient based on Rayleigh distribution

      for (int index = 0; index < noutput_items; ++index) {  // go through the input samples and apply the pointing errors channel coefficient

	out[index] = in[index] * PECoeff;
	 
	++ulCounter;

	if(ulCounter % Sig2PERatio == 0) {  // if the number of updated samples are equal to the length of a pointing errors sample time
	  PECoeff = RayleighNumGen();  // generate another pointing errors channel coefficient
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    float
    Pointing_Errors_ff_impl::GaussNormNumGen(void)
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


    float
    Pointing_Errors_ff_impl::RayleighNumGen(void)
    {
	// generate a random number based on Rayleigh distribution
        float fW_Rx = fTx_Dia/2.0 + fLinkLen*tan(fTx_Theta*M_PI/180.0);  // beam radius at Rx side

        float v_PE = sqrt(M_PI/2.0)*(fRx_Dia/(2.0*fW_Rx));  // aperture to vertical beam size ratio
        float fW2_eq_PE = POW2(fW_Rx)*sqrt(M_PI)*erf(v_PE)/(2.0*v_PE*exp(-POW2(v_PE)));  // equivalent vertical beam size at receiver side


	float x, y;

	x = GaussNormNumGen()*fJitter;
	y = GaussNormNumGen()*fJitter;

	float r = sqrt( POW2(x) + POW2(y) );  // calculate random radius based on the normal distribution
       
        return exp( -2.0*POW2(r) / fW2_eq_PE );  // calculate Log-Normal random sequence
    }


  } /* namespace FSO_Comm */
} /* namespace gr */

