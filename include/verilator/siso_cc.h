/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_VERILATOR_SISO_CC_H
#define INCLUDED_VERILATOR_SISO_CC_H

#include <verilator/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace verilator {

    /*!
     * \brief <+description of block+>
     * \ingroup verilator
     *
     */
    class VERILATOR_API siso_cc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<siso_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of verilator::siso_cc.
       *
       * To avoid accidental use of raw pointers, verilator::siso_cc's
       * constructor is in a private implementation
       * class. verilator::siso_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace verilator
} // namespace gr

#endif /* INCLUDED_VERILATOR_SISO_CC_H */

