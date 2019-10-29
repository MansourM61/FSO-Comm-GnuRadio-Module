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


#ifndef INCLUDED_FSO_COMM_CHANNEL_ANALYSER_FF_H
#define INCLUDED_FSO_COMM_CHANNEL_ANALYSER_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief FSO Channel Analyser
     * \ingroup FSO_Comm
     * \brief Use this block alongside an on-off keying (OOK) pulse sequence as the source to estimate
     * Q-factor, and scintillation indices for levels '0' and '1' of FSO channel.
     * It is also possible to use a constant optical intensity and measure scintillation index for
     * average level.
     */
    class FSO_COMM_API Channel_Analyser_ff : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<Channel_Analyser_ff> sptr;

      /*!
       * \brief Make a Channel Analyser block
       *
       * \param mode mode of estimation, true = use a constant optical intensity as the source, false = use a random OOK pulse sequence
       * \param ChunkSize required number of pulses in each iteration to calculate the outputs (number of pulses)
       * \param SamplingOffset offset index of sampling point from the centre of OOK pulse (+/- offset)
       * \param BandWidth bandwidth of generated OOK pulse (Hz)
       * \param SampRate sample rate of the signal (samples per second)
       */
      static sptr make(bool mode, int ChunkSize, int SamplingOffset, float BandWidth, float SampRate);

      /*!
       * \brief Set channel analyser mode
       *
       * \param mode mode of estimation, true = use a constant optical intensity as the source, false = use a random OOK pulse sequence
       */
      virtual void set_mode(bool mode) = 0;
      /*!
       * \brief Return current channel analyser mode
       */
      virtual bool mode(void) = 0;

      /*!
       * \brief Set channel analyser chunk size
       *
       * \param ChunkSize required number of pulses in each iteration to calculate the outputs (number of pulses)
       */
      virtual void set_ChunkSize(unsigned int ChunkSize) = 0;
      /*!
       * \brief Return current channel analyser chunk size
       */
      virtual unsigned int ChunkSize(void) = 0;

      /*!
       * \brief Set channel analyser sampling offset
       *
       * \param SamplingOffset offset index of sampling point from the centre of OOK pulse (+/- offset)
       */
      virtual void set_SamplingOffset(signed int SamplingOffset) = 0;
      /*!
       * \brief Return current channel analyser sampling offset
       */
      virtual signed int SamplingOffset(void) = 0;

      /*!
       * \brief Set channel analyser bandwidth
       *
       * \param BandWidth bandwidth of generated OOK pulse (Hz)
       */
      virtual void set_BandWidth(float BandWidth) = 0;
      /*!
       * \brief Return current channel analyser bandwidth
       */
      virtual float BandWidth(void) = 0;

      /*!
       * \brief Set channel analyser sampling rate
       *
       * \param SampRate sample rate of the signal (samples per second)
       */
      virtual void set_SampRate(float SampRate) = 0;
      /*!
       * \brief Return current channel analyser sampling rate
       */
      virtual float SampRate(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_CHANNEL_ANALYSER_FF_H */

