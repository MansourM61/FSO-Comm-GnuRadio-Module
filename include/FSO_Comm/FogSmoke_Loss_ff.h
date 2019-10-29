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


#ifndef INCLUDED_FSO_COMM_FOGSMOKE_LOSS_FF_H
#define INCLUDED_FSO_COMM_FOGSMOKE_LOSS_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief Fog/Smoke Loss in FSO Channel
     * \ingroup FSO_Comm
     * \brief The block uses Kim model to simulate the attenuation of fog/smoke in FSO channels based on visibility.
     */
    class FSO_COMM_API FogSmoke_Loss_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<FogSmoke_Loss_ff> sptr;

      /*!
       * \brief Make a FogSmoke Loss block
       *
       * \param Wavelen optical beam wavelength (m)
       * \param LinkLen FSO channel link length (m)
       * \param Vis FSO channel visibility (m)
       */
      static sptr make(float Wavelen, float LinkLen, float Vis);

      /*!
       * \brief Set fog/smoke loss wavelength
       *
       * \param Wavelen optical beam wavelength (m)
       */
      virtual void set_Wavelen(float Wavelen) = 0;
      /*!
       * \brief Return current fogsmoke loss wavelength
       */
      virtual float Wavelen(void) = 0;

      /*!
       * \brief Set fog/smoke loss link length
       *
       * \param LinkLen FSO channel link length (m)
       */
      virtual void set_LinkLen(float LinkLen) = 0;
      /*!
       * \brief Return current fog/smoke loss link length
       */
      virtual float LinkLen(void) = 0;

      /*!
       * \brief Set fog/smoke loss visibility
       *
       * \param Vis FSO channel visibility (m)
       */
      virtual void set_Vis(float Vis) = 0;
      /*!
       * \brief Return current fog/smoke loss visibility
       */
      virtual float Vis(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_FOGSMOKE_LOSS_FF_H */

