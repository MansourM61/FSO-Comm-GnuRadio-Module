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

#ifndef INCLUDED_FSO_COMM_CHANNEL_ANALYSER_FF_IMPL_H
#define INCLUDED_FSO_COMM_CHANNEL_ANALYSER_FF_IMPL_H

#include <FSO_Comm/Channel_Analyser_ff.h>

#include <cmath>
#define _USE_MATH_DEFINES

#define POW2(x) ((x)*(x))

namespace gr {
  namespace FSO_Comm {

    class Channel_Analyser_ff_impl : public Channel_Analyser_ff
    {
     private:
      // private class variables
      bool bMode;  // true = input is DC, false = input is pulse
      unsigned int uiChunkSize;
      signed int siSamplingOffset;
      float ufBandWidth;
      float ufSampRate;
      unsigned int uiNoSamp;
      float fSampPerPulse;
      int iChunckIndex;
      void initialise(void);
      unsigned int FindFirstRisingEdge(const float *InArray, unsigned int input_len, float *mean_val);

     public:
      Channel_Analyser_ff_impl(bool mode = false, int ChunkSize = 50, int SamplingOffset = 0, float BandWidth = 3.2e3, float SampRate = 32e3);
      ~Channel_Analyser_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void set_mode(bool mode) {bMode = mode;}
      bool mode(void) {return bMode;}

      void set_ChunkSize(unsigned int ChunkSize) {uiChunkSize = ChunkSize;}
      unsigned int ChunkSize(void) {return uiChunkSize;}

      void set_SamplingOffset(signed int SamplingOffset) {siSamplingOffset = SamplingOffset;}
      signed int SamplingOffset(void) {return siSamplingOffset;}

      void set_BandWidth(float BandWidth) {ufBandWidth = BandWidth; initialise();}
      float BandWidth(void) {return ufBandWidth;}

      void set_SampRate(float SampRate) {ufSampRate = SampRate; initialise();}
      float SampRate(void) {return ufSampRate;}

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_CHANNEL_ANALYSER_FF_IMPL_H */

