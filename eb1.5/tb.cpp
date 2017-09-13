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
  int val;
  randomizer rrr;
public:
  tx(int seed) : val(0), rrr(seed) {}
  int operator () (bool ack) {
    if (ack) {
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
  rx(int seed) : val(0), rrr(seed) {}
  bool operator () (int dat) {
    val = rrr() & 0xff;
    res = val != dat;
    if (res) {
      std::cout << "Error: got: " << dat << ", expected: " << val << '\n';
    }
    return res;
  }
};

class fsm {
private:
  int state;
  int trans[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
public:
  fsm() : state(0) {}
  void operator () (int now) {
    if (now != state) {
      trans[state][now]++;
      state = now;
    }
  }
  void dump () {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (trans[i][j] > 0) {
          std::cout << i << "." << j << ":" << trans[i][j] << '\n';
        }
      }
    }
  }
};

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    tx tx1(1142);
    rx rx1(1142);
    randomizer tx1r(108);
    randomizer rx1r(333);
    fsm fsm1;

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
    for (i = 0; i < 1000; i++) {
        top->reset_n = (i > 4);
        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++) {
            tfp->dump (2 * i + clk);
            top->clk = !top->clk;
            top->eval ();
        }

        if (top->reset_n) {
          top->i_ack = (rx1r() & 0x800) != 0;
          top->t_req = (tx1r() & 0x800) != 0;
          top->t_dat = tx1(top->t_req && top->t_ack);
          top->i_req && top->i_ack && rx1(top->i_dat);
        }
        fsm1(top->stt);
        if (Verilated::gotFinish()) exit(0);
    }
    fsm1.dump();
    tfp->close();
    exit(0);
}
