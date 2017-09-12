#include <iostream>
#include "Veb.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

class randomizer { // Park-Miller PRNG
private:
  int state;
public:
  randomizer(int seed) : state(seed) {}
  int operator () () {
    state = state * 16807 % 2147483647;
    return state;
  }
};

class tx {
private:
  int i, len, val;
  randomizer rrr;
public:
  tx(int _len) : len(_len), i(0), rrr(42), val(0) {}
  int operator () (bool ack) {
    if (ack && i < len) {
      i++;
      val = rrr() & 0xff;
    }
    return val;
  }
};

class rx {
private:
  int val, res;
  randomizer rrr;
public:
  rx() : val(0), rrr(42) {}
  bool operator () (int dat) {
    std::cout << "got: " << dat << ", expected: " << val << '\n';
    res = val != dat;
    val = rrr() & 0xff;
    return res;
  }
};

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    tx tx1(10);
    rx rx1;
    randomizer tx1r(108);
    randomizer rx1r(333);

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Veb* top = new Veb;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("tb.vcd");
    // initialize simulation inputs
    top->clk = 1;
    top->reset_n = 0;
    top->t_dat = 0;
    top->t_req = 0;
    top->i_ack = 0;
    // run simulation for 100 clock periods
    for (i = 0; i < 100; i++) {
        top->reset_n = (i > 4);
        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++) {
            tfp->dump (2 * i + clk);
            top->clk = !top->clk;
            top->eval ();
        }

        if (top->t_req) {
          top->t_dat = tx1(top->reset_n && top->i_ack);
        }

        if (top->reset_n && top->i_req && top->i_ack) {
          if (rx1(top->i_dat)) {
            std::cout << i << " error" << '\n';
          }
        }

        top->t_req = top->reset_n ? ((tx1r() & 0x800) != 0) : 0;
        top->i_ack = top->reset_n ? ((rx1r() & 0x800) != 0) : 0;

        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}
