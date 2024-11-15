class MyModule extends Module {
  val io = IO(new Bundle {
    val in  = Input(UInt(4.W))
    val out = Output(UInt(4.W))
  })

  val two  = 1 + 1
  printf("two : %d\n", io.in)
  println(two)
  val utwo = 1.U + 1.U
  println(utwo)
  
  io.out := io.in
}
println(getVerilog(new MyModule))
test(new MyModule) { c =>
    c.io.in.poke(3.U)
    c.clock.step(2) // circuit will print
}