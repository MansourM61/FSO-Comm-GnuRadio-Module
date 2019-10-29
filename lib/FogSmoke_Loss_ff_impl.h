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

#ifndef INCLUDED_FSO_COMM_FOGSMOKE_LOSS_FF_IMPL_H
#define INCLUDED_FSO_COMM_FOGSMOKE_LOSS_FF_IMPL_H

#include <FSO_Comm/FogSmoke_Loss_ff.h>

#include <cmath>
#define _USE_MATH_DEFINES

#define POW2(x) ((x)*(x))

#define T_TH_FS (2.0/100.0)
#define LAMBDA_0 550.0e-9

namespace gr {
  namespace FSO_Comm {

    class FogSmoke_Loss_ff_impl : public FogSmoke_Loss_ff
    {
     private:
      // private class variables
      float fWavelen, fLinkLen, fVis;

     public:
      FogSmoke_Loss_ff_impl(float Wavelen = 850e-9, float LinkLen = 1e3, float Vis = 20e3);
      ~FogSmoke_Loss_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void set_Wavelen(float Wavelen) {fWavelen = Wavelen;}
      float Wavelen(void) {return fWavelen;}

      void set_LinkLen(float LinkLen) {fLinkLen = LinkLen;}
      float LinkLen(void) {return fLinkLen;}

      void set_Vis(float Vis) {fVis = Vis;}
      float Vis(void) {return fVis;}

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_FOGSMOKE_LOSS_FF_IMPL_H */

