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


#ifndef INCLUDED_FSO_COMM_LASER_FF_H
#define INCLUDED_FSO_COMM_LASER_FF_H

#include <FSO_Comm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace FSO_Comm {

    /*!
     * \brief FSO Laser Module
     * \ingroup FSO_Comm
     * \brief The block generate optical power output based on average power and extinction ratio.
     */
    class FSO_COMM_API Laser_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<Laser_ff> sptr;

      /*!
       * \brief Make a laser module block
       *
       * \param P_avg average optical power (W)
       * \param Wavelen optical beam wavelength (m)
       * \param ExtRatio extiction ratio
       */
      static sptr make(float P_avg, float Wavelen, float ExtRatio);

      /*!
       * \brief Set laser module average optical power
       *
       * \param P_avg average optical power (W)
       */
      virtual void set_P_avg(float P_avg) = 0;
      /*!
       * \brief Return current laser module average optical power
       */
      virtual float P_avg(void) = 0;

      /*!
       * \brief Set laser module wavelength
       *
       * \param Wavelen optical beam wavelength (m)
       */
      virtual void set_Wavelen(float Wavelen) = 0;
      /*!
       * \brief Return current laser module wavelength
       */
      virtual float Wavelen(void) = 0;

      /*!
       * \brief Set current laser module extinction ratio
       *
       * \param ExtRatio extiction ratio
       */
      virtual void set_ExtRatio(float ExtRatio) = 0;
      /*!
       * \brief Return current laser module extinction ratio
       */
      virtual float ExtRatio(void) = 0;

    };

  } // namespace FSO_Comm
} // namespace gr

#endif /* INCLUDED_FSO_COMM_LASER_FF_H */

