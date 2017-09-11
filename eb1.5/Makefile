# export VERILATOR_ROOT

VERILATOR_FLAGS = -Wall --cc --trace eb1_5.v

default: verilate compile

verilate:
	$(VERILATOR_ROOT)/bin/verilator $(VERILATOR_FLAGS)

compile:
	make -j -C obj_dir/ -f Veb1_5.mk Veb1_5
