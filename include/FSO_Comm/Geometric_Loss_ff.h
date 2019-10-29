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


#ifndef INCLUDED_FSO_COMM_GEOMETRIC_LOSS_FF_H
#define INCLUDED_FSO_COMM_GEOMETRIC_LOSS_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief Geometric Loss in FSO Channel
     * \ingroup FSO_Comm
     * \brief Using geometric optics, the beam propagation loss is estimated for given beam properties. 
     */
    class FSO_COMM_API Geometric_Loss_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<Geometric_Loss_ff> sptr;

      /*!
       * \brief Make a geometric loss block
       *
       * \param Tx_Dia transmitter aperture diameter (m)
       * \param Tx_DivAng transmitter half-angle beam divergence (Deg)
       * \param LinkLen FSO channel link length (m)
       * \param Rx_Dia receiver aperture diameter (m)
       */
      static sptr make(float Tx_Dia, float Tx_DivAng, float LinkLen, float Rx_Dia);

      /*!
       * \brief Set geometric loss transmitter aperture diameter
       *
       * \param Tx_Dia transmitter aperture diameter (m)
       */
      virtual void set_Tx_Dia(float Tx_Dia) = 0;
      /*!
       * \brief Return current geometric loss transmitter aperture diameter
       */
      virtual float Tx_Dia(void) = 0;

      /*!
       * \brief Set geometric loss transmitter full-angle divergence angle
       *
       * \param Tx_DivAng transmitter half-angle beam divergence (Deg)
       */
      virtual void set_Tx_DivAng(float Tx_DivAng) = 0;
      /*!
       * \brief Return current geometric loss transmitter full-angle divergence angle
       */
      virtual float Tx_DivAng(void) = 0;

      /*!
       * \brief Set geometric loss transmitter link length
       *
       * \param LinkLen FSO channel link length (m)
       */
      virtual void set_LinkLen(float LinkLen) = 0;
      /*!
       * \brief Return current geometric loss transmitter link length
       */
      virtual float LinkLen(void) = 0;

      /*!
       * \brief Set geometric loss receiver aperture diameter
       *
       * \param Rx_Dia receiver aperture diameter (m)
       */
      virtual void set_Rx_Dia(float Rx_Dia) = 0;
      /*!
       * \brief Return cyurrent geometric loss receiver aperture diameter
       */
      virtual float Rx_Dia(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_GEOMETRIC_LOSS_FF_H */

