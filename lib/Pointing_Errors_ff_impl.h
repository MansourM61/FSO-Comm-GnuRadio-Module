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

#ifndef INCLUDED_FSO_COMM_POINTING_ERRORS_FF_IMPL_H
#define INCLUDED_FSO_COMM_POINTING_ERRORS_FF_IMPL_H

#include <FSO_Comm/Pointing_Errors_ff.h>

#include <cmath>
#define _USE_MATH_DEFINES

#define POW2(x) ((x)*(x))

namespace gr {
  namespace FSO_Comm {

    class Pointing_Errors_ff_impl : public Pointing_Errors_ff
    {
     private:
      // private class variables
      float fJitter, fLinkLen, fTx_Dia, fTx_Theta, fRx_Dia, fTempCorr, fSampRate;
      int  iGaussGenCounter;
      float fGaussGenArray[2];
      unsigned long ulCounter;
      float GaussNormNumGen(void);
      float RayleighNumGen(void);

     public:
      Pointing_Errors_ff_impl(float Jitter = 1e-3, float LinkLen = 200, float Tx_Dia = 1e-3, float Tx_Theta = 0.05, float Rx_Dia = 100e-3, float TempCorr = 25e-3, float SampRate = 32e3);
      ~Pointing_Errors_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void set_Jitter(float Jitter) {fJitter = Jitter;}
      float Jitter(void) {return fJitter;}

      void set_LinkLen(float LinkLen) {fLinkLen = LinkLen;}
      float LinkLen(void) {return fLinkLen;}

      void set_Tx_Dia(float Tx_Dia) {fTx_Dia = Tx_Dia;}
      float Tx_Dia(void) {return fTx_Dia;}

      void set_Tx_Theta(float Tx_Theta) {fTx_Theta = Tx_Theta;}
      float Tx_Theta(void) {return fTx_Theta;}

      void set_Rx_Dia(float Rx_Dia) {fRx_Dia = Rx_Dia;}
      float Rx_Dia(void) {return fRx_Dia;}

      void set_TempCorr(float TempCorr) {fTempCorr = TempCorr;}
      float TempCorr(void) {return fTempCorr;}

      void set_SampRate(float SampRate) {fSampRate = SampRate;}
      float SampRate(void) {return fSampRate;}

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_POINTING_ERRORS_FF_IMPL_H */

