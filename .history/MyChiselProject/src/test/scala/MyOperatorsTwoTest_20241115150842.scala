import chisel3._
import chisel3.iotesters.{PeekPokeTester, Driver}

class MyOperatorsTwoTest(c: MyOperatorsTwo) extends PeekPokeTester(c) {
  poke(c.io.out_mux, 3.U)
  poke(c.io.out_cat, 5.U)
}

object MyOperatorsTwoTest extends App {
  Driver.execute(args, () => new MyOperatorsTwo) { c =>
    new MyOperatorsTwoTest(c)
  }
}