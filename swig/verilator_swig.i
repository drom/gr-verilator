/* -*- c++ -*- */

#define VERILATOR_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "verilator_swig_doc.i"

%{
#include "verilator/siso_cc.h"
%}


%include "verilator/siso_cc.h"
GR_SWIG_BLOCK_MAGIC2(verilator, siso_cc);
