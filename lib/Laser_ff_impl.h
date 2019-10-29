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

#ifndef INCLUDED_FSO_COMM_LASER_FF_IMPL_H
#define INCLUDED_FSO_COMM_LASER_FF_IMPL_H

#include <FSO_Comm/Laser_ff.h>

#include <cmath>
#define _USE_MATH_DEFINES

namespace gr {
  namespace FSO_Comm {

    class Laser_ff_impl : public Laser_ff
    {
     private:
      // private class variables
      float fP_avg, fWavelen, fExtRatio;

     public:
      Laser_ff_impl(float P_avg = 1e-3, float Wavelen = 850e-9, float ExtRatio = 5.0);  // P_avg = average power (W),  Wavelen = wavelength (m), ExtRatio = extinction ratio
      ~Laser_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void set_P_avg(float P_avg) {fP_avg = P_avg;}
      float P_avg(void) {return fP_avg;}

      void set_Wavelen(float Wavelen) {fWavelen = Wavelen;}
      float Wavelen(void) {return fWavelen;}

      void set_ExtRatio(float ExtRatio) {fExtRatio = ExtRatio;}
      float ExtRatio(void) {return fExtRatio;}

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_LASER_FF_IMPL_H */

