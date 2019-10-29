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


#ifndef INCLUDED_FSO_COMM_TURBULENCE_FF_H
#define INCLUDED_FSO_COMM_TURBULENCE_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief FSO Turbulence Channel
     * \ingroup FSO_Comm
     * \brief This block simulates the effect of turbulence (scintillation) in FSO channel.
     */
    class FSO_COMM_API Turbulence_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<Turbulence_ff> sptr;

      /*!
       * \brief Make a turbulence block
       *
       * \param Cn2 refractive index structure constant (m^(-2/3))
       * \param Wavelen optical beam wavelength (m)
       * \param LinkLen FSO channel link length (m)
       * \param Rx_Dia receiver aperture diameter (m)
       * \param TempCorr temppral correlation of turbulence channel (s)
       * \param SampRate sampling rate of signal (samples per second)
       */
      static sptr make(float Cn2, float Wavelen, float LinkLen, float Rx_Dia, float TempCorr, float SampRate);

      /*!
       * \brief Set turbulence Cn2
       *
       * \param Cn2 refractive index structure constant (m^(-2/3))
       */
      virtual void set_Cn2(float Cn2) = 0;
      /*!
       * \brief Return current turbulence Cn2
       */
      virtual float Cn2(void) = 0;

      /*!
       * \brief Set turbulence wavelength
       *
       * \param Wavelen optical beam wavelength (m)
       */
      virtual void set_Wavelen(float Wavelen) = 0;
      /*!
       * \brief Return current turbulence wavelength
       */
      virtual float Wavelen(void) = 0;

      /*!
       * \brief Set turbulence link length
       *
       * \param LinkLen FSO channel link length (m)
       */
      virtual void set_LinkLen(float LinkLen) = 0;
      /*!
       * \brief Return current turbulence link length
       */
      virtual float LinkLen(void) = 0;

      /*!
       * \brief Set turbulence receiver apertture diameter
       *
       * \param Rx_Dia receiver apertture diameter (m)
       */
      virtual void set_Rx_Dia(float Rx_Dia) = 0;
      /*!
       * \brief Return current turbulence receiver aperture diameter
       */
      virtual float Rx_Dia(void) = 0;

      /*!
       * \brief Set turbulence temporal correlation
       *
       * \param TempCorr temppral correlation of turbulence channel (s)
       */
      virtual void set_TempCorr(float TempCorr) = 0;
      /*!
       * \brief Return current turbulence temporal correlation
       */
      virtual float TempCorr(void) = 0;

      /*!
       * \brief Set turbulence sampling rate
       *
       * \param SampRate sampling rate of signal (samples per second)
       */
      virtual void set_SampRate(float SampRate) = 0;
      /*!
       * \brief Return current turbulence sampling rate
       */
      virtual float SampRate(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_TURBULENCE_FF_H */

