# export VERILATOR_ROOT

VERILATOR_FLAGS = -Wall --cc --trace eb.v --exe tb.cpp

default: verilate compile run

clean:
	rm -rf obj_dir

verilate:
	$(VERILATOR_ROOT)/bin/verilator $(VERILATOR_FLAGS)

lint:
	$(VERILATOR_ROOT)/bin/verilator --lint-only $(VERILATOR_FLAGS)

compile:
	make -j -C obj_dir/ -f Veb.mk Veb

run:
	./obj_dir/Veb
