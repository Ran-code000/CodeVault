// 3-point moving average implemented in the style of a FIR filter
class MovingAverage3(bitWidth: Int) extends Module {
  val io = IO(new Bundle {
    val in = Input(UInt(bitWidth.W))
    val out = Output(UInt(bitWidth.W))
  })

  val z1 = RegNext(io.in) // Create a register whose input is connected to the argument io.in
  val z2 = RegNext(z1)    // Create a register whose input is connected to the argument z1

  io.out := (io.in * 1.U) + (z1 * 1.U) + (z2 * 1.U) // `1.U` is an unsigned literal with value 1
}