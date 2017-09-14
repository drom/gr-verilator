/* -*- c++ -*- */
/*
 * Copyright 2017 Aliaksei Chapyzhenka.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "siso_cc_impl.h"

namespace gr {
  namespace verilator {

    siso_cc::sptr
    siso_cc::make()
    {
      return gnuradio::get_initial_sptr
        (new siso_cc_impl());
    }

    /*
     * The private constructor
     */
    siso_cc_impl::siso_cc_impl()
      : gr::block("siso_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {}

    /*
     * Our virtual destructor.
     */
    siso_cc_impl::~siso_cc_impl()
    {
    }

    void
    siso_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      unsigned ninputs = ninput_items_required.size();
      for(unsigned i = 0; i < ninputs; i++)
      {
        ninput_items_required[i] = noutput_items;
      }
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    siso_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      for (int i = 0; i < noutput_items; i++)
      {
        gr_complex ini = in[i];
        out[i] = gr_complex(ini.imag(), ini.real());
      }
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace verilator */
} /* namespace gr */
