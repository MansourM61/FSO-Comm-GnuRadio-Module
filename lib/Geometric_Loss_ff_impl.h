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

#ifndef INCLUDED_FSO_COMM_GEOMETRIC_LOSS_FF_IMPL_H
#define INCLUDED_FSO_COMM_GEOMETRIC_LOSS_FF_IMPL_H

#include <FSO_Comm/Geometric_Loss_ff.h>

#include <cmath>
#define _USE_MATH_DEFINES

namespace gr {
  namespace FSO_Comm {

    class Geometric_Loss_ff_impl : public Geometric_Loss_ff
    {
     private:
      // private class variables
      float fTx_Dia, fTx_DivAng, fLinkLen, fRx_Dia;

     public:
      Geometric_Loss_ff_impl(float Tx_Dia = 1e-3, float Tx_DivAng = 0.01, float LinkLen = 1e3, float Rx_Dia = 100e-3);
      ~Geometric_Loss_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void set_Tx_Dia(float Tx_Dia) {fTx_Dia = Tx_Dia;}
      float Tx_Dia(void) {return fTx_Dia;}

      void set_Tx_DivAng(float Tx_DivAng) {fTx_DivAng = Tx_DivAng;}
      float Tx_DivAng(void) {return fTx_DivAng;}

      void set_LinkLen(float LinkLen) {fLinkLen = LinkLen;}
      float LinkLen(void) {return fLinkLen;}

      void set_Rx_Dia(float Rx_Dia) {fRx_Dia = Rx_Dia;}
      float Rx_Dia(void) {return fRx_Dia;}

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_GEOMETRIC_LOSS_FF_IMPL_H */

