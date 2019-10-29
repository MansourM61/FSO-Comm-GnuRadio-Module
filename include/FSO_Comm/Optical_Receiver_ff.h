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


#ifndef INCLUDED_FSO_COMM_OPTICAL_RECEIVER_FF_H
#define INCLUDED_FSO_COMM_OPTICAL_RECEIVER_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief FSO Optical Receiver
     * \ingroup FSO_Comm
     * \brief The optical receiver models a photodiode followed by a transimpedance amplifer (TIA) converting optical power to electrial current.
     */
    class FSO_COMM_API Optical_Receiver_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<Optical_Receiver_ff> sptr;

      /*!
       * \brief Make an optical receiver block
       *
       * \param Resp photodiode responsivity (A/W)
       * \param G_TIA transimpedance amplifer (TIA) gain (Ohms)
       * \param Imp circuit impedance (Ohms)
       * \param P_n noise power (w)
       */
      static sptr make(float Resp, float G_TIA, float Imp, float P_n);

      /*!
       * \brief Set optical receiver sensitivity
       *
       * \param Resp photodiode responsivity (A/W)
       */
      virtual void set_Resp(float Resp) = 0;
      /*!
       * \brief Return current optical receiver sensitivity
       */
      virtual float Resp(void) = 0;

      /*!
       * \brief Set optical receiver TIA gain
       *
       * \param G_TIA transimpedance amplifer (TIA) gain (Ohms)
       */
      virtual void set_G_TIA(float G_TIA) = 0;
      /*!
       * \brief Return current optical receiver TIA gain
       */
      virtual float G_TIA(void) = 0;

      /*!
       * \brief Set optical receiver impedance
       *
       * \param Imp circuit impedance (Ohms)
       */
      virtual void set_Imp(float Imp) = 0;
      /*!
       * \brief Return current optical receiver impedance
       */
      virtual float Imp(void) = 0;

      /*!
       * \brief Set optical receiver noise power
       *
       * \param P_n noise power (w)
       */
      virtual void set_P_n(float P_n) = 0;
      /*!
       * \brief Return current optical receiver noise power
       */
      virtual float P_n(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_OPTICAL_RECEIVER_FF_H */

