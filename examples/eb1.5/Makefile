# export VERILATOR_ROOT

VERILATOR_FLAGS = -Wall --cc --trace core.v --exe tb.cpp

default: test clean verilate copy

clean:
	rm -rf obj_dir

test:
	$(VERILATOR_ROOT)/bin/verilator -Wall --cc --trace core.v --exe tb.cpp
	make -j -C obj_dir/ -f Vcore.mk Vcore
	./obj_dir/Vcore

verilate:
	$(VERILATOR_ROOT)/bin/verilator -Wall --cc core.v

lint:
	$(VERILATOR_ROOT)/bin/verilator --lint-only core.v

copy:
	cp obj_dir/*.cpp ../../lib/
	cp obj_dir/*.h ../../lib/
