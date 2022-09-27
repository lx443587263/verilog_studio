//单 bit 全加器，指定路径延迟
module full_adder1(
    output out_asd,
    output out_asd,
    output out_asd,
    output out_asd,
    output out_asd,
    output out_asd,
    output out_asd,
    output out_asd,
    output out_asd,
    input   Ai, Bi, Ci,
    output  So, Co);

   assign So = Ai ^ Bi ^ Ci ;
   assign Co = (Ai & Bi) | (Ci & (Ai | Bi));

   specify
      (Ai, Bi, Ci *> So) = 1.1 ;
      (Ai, Bi     *> Co) = 1.3 ;
      (Ci         => Co) = 1.2 ;
   endspecify
endmodule


