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


#ifndef INCLUDED_FSO_COMM_POINTING_ERRORS_FF_H
#define INCLUDED_FSO_COMM_POINTING_ERRORS_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief FSO Pointing Errors Channel
     * \ingroup FSO_Comm
     * \brief This block simulates the effect of pointing errors (vibration) in FSO channel.
     */
    class FSO_COMM_API Pointing_Errors_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<Pointing_Errors_ff> sptr;

      /*!
       * \brief Make a pointing errors block
       *
       * \param Jitter vibration displacement (m)
       * \param LinkLen FSO channel link length (m)
       * \param Tx_Dia transmitter aperture diameter (m)
       * \param Tx_Theta transmitter beam half-angle divergence angle (Deg)
       * \param Rx_Dia receiver aperture diameter (m)
       * \param TempCorr temppral correlation of pointing errors channel (s)
       * \param SampRate sampling rate of signal (samples per second)
       */
      static sptr make(float Jitter, float LinkLen, float Tx_Dia, float Tx_Theta, float Rx_Dia, float TempCorr, float SampRate);

      /*!
       * \brief Set pointing errors jitter
       *
       * \param Jitter vibration displacement (m)
       */
      virtual void set_Jitter(float Jitter) = 0;
      /*!
       * \brief Return current pointing errors jitter
       */
      virtual float Jitter(void) = 0;

      /*!
       * \brief Set pointing errors link length
       *
       * \param LinkLen FSO channel link length (m)
       */
      virtual void set_LinkLen(float LinkLen) = 0;
      /*!
       * \brief Return current pointing errors link length
       */
      virtual float LinkLen(void) = 0;

      /*!
       * \brief Set pointing errors transmitter aperture diameter
       *
       * \param Tx_Dia transmitter aperture diameter (m)
       */
      virtual void set_Tx_Dia(float Tx_Dia) = 0;
      /*!
       * \brief Return current pointing errors transmitter aperture diameter
       */
      virtual float Tx_Dia(void) = 0;

      /*!
       * \brief Set poinintg errors transmitter beam divergence
       *
       * \param Tx_Theta transmitter beam half-angle divergence angle (Deg)
       */
      virtual void set_Tx_Theta(float Tx_Theta) = 0;
      /*!
       * \brief Return current poinintg errors transmitter beam divergence
       */
      virtual float Tx_Theta(void) = 0;

      /*!
       * \brief Set pointing errors receiver aperture diameter
       *
       * \param Rx_Dia receiver aperture diameter (m)
       */
      virtual void set_Rx_Dia(float Rx_Dia) = 0;
      /*!
       * \brief Return current pointing errors receiver aperture diameter
       */
      virtual float Rx_Dia(void) = 0;

      /*!
       * \brief Set pointing errors temporal correlation
       *
       * \param TempCorr temppral correlation of pointing errors channel (s)
       */
      virtual void set_TempCorr(float TempCorr) = 0;
      /*!
       * \brief Return current pointing errors temporal correlation
       */
      virtual float TempCorr(void) = 0;

      /*!
       * \brief Set poinintg errors sampling rate
       *
       * \param SampRate sampling rate of signal (samples per second)
       */
      virtual void set_SampRate(float SampRate) = 0;
      /*!
       * \brief Return current poinintg errors sampling rate
       */
      virtual float SampRate(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_POINTING_ERRORS_FF_H */

