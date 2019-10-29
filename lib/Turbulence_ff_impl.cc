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
#include "Turbulence_ff_impl.h"

namespace gr {
  namespace FSO_Comm {

    Turbulence_ff::sptr
    Turbulence_ff::make(float Cn2, float Wavelen, float LinkLen, float Rx_Dia, float TempCorr, float SampRate)
    {
      return gnuradio::get_initial_sptr
        (new Turbulence_ff_impl(Cn2, Wavelen, LinkLen, Rx_Dia, TempCorr, SampRate));
    }

    /*
     * The private constructor
     */
    Turbulence_ff_impl::Turbulence_ff_impl(float Cn2, float Wavelen, float LinkLen, float Rx_Dia, float TempCorr, float SampRate)
      : gr::sync_block("Turbulence_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))), fCn2(Cn2), fWavelen(Wavelen), fLinkLen(LinkLen), fRx_Dia(Rx_Dia), fTempCorr(TempCorr), fSampRate(SampRate), iGaussGenCounter(0), ulCounter(0)
    {
	memset(fGaussGenArray, 0.0, sizeof(float)*2);  // initialise the array
    }

    /*
     * Our virtual destructor.
     */
    Turbulence_ff_impl::~Turbulence_ff_impl()
    {
    }

    int
    Turbulence_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];  // assign the pointer to the input array
      float *out = (float *) output_items[0];  // assign the pointer to the output array

      float fF_t = 1.0/fTempCorr;  // turbulence fading maximum frequency (Hz)

      unsigned long Sig2TurbRatio = int(ceil(fSampRate*1.0/fF_t));  // number of signal samples to number of turbulence coefficients ratio

      float TurbCoeff = LogNormalNumGen();  // generate a turbulence channel coeeficient based on log-normal distribution

      for (int index = 0; index < noutput_items; ++index) {  // go through the input samples and apply the turbulence channel coefficient

	out[index] = in[index] * TurbCoeff;
	 
	++ulCounter;

	if(ulCounter % Sig2TurbRatio == 0) {  // if the number of updated samples are equal to the length of a turbulence sample time
	  TurbCoeff = LogNormalNumGen();  // generate another turbulence channel coefficient
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    float
    Turbulence_ff_impl::GaussNormNumGen(void)
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
    Turbulence_ff_impl::LogNormalNumGen(void)
    {
	// generate a random number based on log-normal distribution
	float k = 2*M_PI/fWavelen;  // wave number (rad/m)
    	float sig2_R = 1.23*fCn2*pow(k, 7.0/6.0)*pow(fLinkLen, 11.0/6.0);  // Rytov variance
    	float fD_AAF = sqrt(k*POW2(fRx_Dia)/(4.0*fLinkLen));  // auxilary parameter for aperture averaging effect
    	float fAAF = pow(1.0 + 1.062*POW2(fD_AAF), -7.0/6.0);  // aperture averaging factor

    	float sig_x = sqrt(fAAF*sig2_R/4.0);  // sigma parameter weak turbulence
    	float mu_x = -fAAF*sig2_R/4.0;  // mu parameter weak turbulence
       
        return exp( 2.0*(GaussNormNumGen()*sig_x + mu_x) );  // calculate Log-Normal random sequence
    }

  } /* namespace FSO_Comm */
} /* namespace gr */

