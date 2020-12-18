struct test_ip {
  // register
  Variable8 r0; // bits: 8
  Variable8 r1; // bits: 1

  // wire
  Variable16 w0; // bits: 14
  Variable8  w1; // bits: 5

};

/* test_ip.ov
design test_ip {
  reg  logic:8  r0;
  reg  bit      r1;
  wire logic:13 w0;
  wire logic:5  w1;

  proc reset() {
    r0 <= 0;
    r1 <= 0;
  }

  proc main() {
    r0 <= w0[7:0];
    if (w1[0]) {
      r1 <= w1[1];
    } else {
      r1 <= w1[2];
    }
  }

  proc pre_update() {

  }
}
*/

/* test_ip.v
module test_ip(
  input clk;
  input rst_n;
  input [13:0] w0,
  input [4:0] w1,
  output reg [7:0] r0,
  output reg r1
);
  
  always @(posedge clk) begin
    if (~rst_n) begin
      r0 <= 0;
      r1 <= 0;
    end else begin
      r0 <= w0[7:0];
      if (w1[0]) begin
        r1 <= w1[1];
      end else begin
        r1 <= w1[2];
      end
    end
  end

endmodule

*/

void test_ip_reset(struct test_ip* obj, char* d, char* q, char* mem, char* wire) {
  setvalue8(d, &obj->r0, 0);
  setvalue8(d, &obj->r1, 0);
}

void test_ip_main(struct test_ip* obj, char* d, char* q, char* mem, char* wire) {
  uint16 w0 = getvalue16(wire, &obj->w0);
  uint8 w0_auto7to0 = w0 & 0x00FF;

  uint8 w1 = getvalue8(wire, &obj->w1);
  uint8 w1_auto0to0 = w1 & 0x1;
  uint8 w1_auto1to1 = w1 & 0x2;
  uint8 w1_auto2to2 = w1 & 0x4;

  uint8 r1_ssa0 = w1_auto1to1;
  uint8 r1_ssa1 = w1_auto2to2;
  uint8 r1_phi  = w1_auto0to0 ? r1_ssa0 : r1_ssa1;

  setvalue8(d, &obj->r0, w0_auto7to0);
  setvalue8(d, &obj->r1, r1_phi);
}

void test_ip_pre_update(struct test_ip* obj, char* d, char* q, char* mem, char* wire) {

}