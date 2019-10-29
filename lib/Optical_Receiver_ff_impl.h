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

#ifndef INCLUDED_FSO_COMM_OPTICAL_RECEIVER_FF_IMPL_H
#define INCLUDED_FSO_COMM_OPTICAL_RECEIVER_FF_IMPL_H

#include <FSO_Comm/Optical_Receiver_ff.h>

#include <cmath>
#define _USE_MATH_DEFINES

namespace gr {
  namespace FSO_Comm {

    class Optical_Receiver_ff_impl : public Optical_Receiver_ff
    {
     private:
      // private class variables
      float fResp, fG_TIA, fImp, fP_n;
      int  iGaussGenCounter;
      float fGaussGenArray[2];
      float GaussNormNumGen(void);

     public:
      Optical_Receiver_ff_impl(float Resp = 0.8, float G_TIA = 1e3, float Imp = 50, float P_n = 1e-6);
      ~Optical_Receiver_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void set_Resp(float Resp) {fResp = Resp;}
      float Resp(void) {return fResp;}

      void set_G_TIA(float G_TIA) {fG_TIA = G_TIA;}
      float G_TIA(void) {return fG_TIA;}

      void set_Imp(float Imp) {fImp = Imp;}
      float Imp(void) {return fImp;}

      void set_P_n(float P_n) {fP_n = P_n;}
      float P_n(void) {return fP_n;}

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_OPTICAL_RECEIVER_FF_IMPL_H */

