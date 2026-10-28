VERILATOR = verilator --binary --timing --trace-fst --trace-structs -Wall -Wno-fatal -j 0
BUILD = build
TBS = $(wildcard *_tb.sv)

.PHONY: test clean
.SECONDARY:

# build/<name>/sim from <name>.sv + <name>_tb.sv
$(BUILD)/%/sim: %.sv %_tb.sv
	mkdir -p $(BUILD)/$*
	$(VERILATOR) --top-module $*_tb -Mdir $(BUILD)/$* -o sim \
	    '+define+DUMPFILE="$(BUILD)/$*.fst"' $^

# make _counter       <- build + run the testbench (fails on $fatal)
_%: $(BUILD)/%/sim
	./$<

# make counter.wave   <- run, then open the waveform
%.wave: _%
	gtkwave $(BUILD)/$*.fst &

# make test           <- run every testbench
test: $(TBS:%_tb.sv=_%)

clean:
	rm -rf $(BUILD)
