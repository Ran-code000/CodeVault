import chisel3._
import chisel3.util._

class Decoder extends Module {
  val io = IO(new Bundle {
    val instruction = Input(UInt(32.W)) // 输入指令（32 位）
    val controlSignals = Output(new Bundle {
      val aluOp = Output(UInt(3.W)) // ALU 操作类型（如加法、减法等）
      val regWrite = Output(Bool()) // 寄存器写控制
      val memRead = Output(Bool()) // 内存读取控制
      val memWrite = Output(Bool()) // 内存写控制
      val jumpFlag = Output(Bool()) // 跳转指令控制
      val jumpAddress = Output(UInt(32.W)) // 跳转目标地址
      val branchFlag = Output(Bool()) // 分支判断控制
      val branchAddress = Output(UInt(32.W)) // 分支目标地址
    })
    val intAssert = Input(Bool()) // 中断信号
    val intHandlerAddress = Input(UInt(32.W)) // 中断处理程序地址
  })

  // 假设指令格式：指令类型可以通过操作码（opcode）识别
  val opcode = io.instruction(31, 26)  // 取出操作码（6 位）
  val rs = io.instruction(25, 21)  // 源寄存器 rs
  val rt = io.instruction(20, 16)  // 源寄存器 rt
  val rd = io.instruction(15, 11)  // 目标寄存器 rd
  val imm = io.instruction(15, 0)  // 立即数（16 位）
  val targetAddress = io.instruction(25, 0) // 跳转目标地址

  // 初始化控制信号
  io.controlSignals.aluOp := 0.U
  io.controlSignals.regWrite := false.B
  io.controlSignals.memRead := false.B
  io.controlSignals.memWrite := false.B
  io.controlSignals.jumpFlag := false.B
  io.controlSignals.jumpAddress := 0.U
  io.controlSignals.branchFlag := false.B
  io.controlSignals.branchAddress := 0.U

  // 分支指令的处理
  val isBranchInstruction = (opcode === "b000100".U) // 假设分支指令的操作码为 000100
  val isJumpInstruction = (opcode === "b000010".U)  // 假设跳转指令的操作码为 000010

  // 中断信号处理
  val isInterrupt = io.intAssert
  when(isInterrupt) {
    io.controlSignals.jumpFlag := true.B
    io.controlSignals.jumpAddress := io.intHandlerAddress
  }

  // 跳转指令处理
  when(isJumpInstruction) {
    io.controlSignals.jumpFlag := true.B
    io.controlSignals.jumpA；ddress := Cat(io.instruction(25, 0), 0.U(2.W)) // 假设目标地址是指令的低 26 位并左移 2 位
  }

  // 分支指令处理
  when(isBranchInstruction) {
    io.controlSignals.branchFlag := true.B
    // 假设分支目标地址是立即数（在分支指令中给出的地址偏移量），需要加上当前 PC 的值
    io.controlSignals.branchAddress := imm
  }

  // 非跳转、非分支指令的控制信号设置（如算术、加载/存储等）
  switch(opcode) {
    is("b000000".U) { // 假设操作码 000000 是算术逻辑指令
      io.controlSignals.aluOp := "b001".U // 加法
      io.controlSignals.regWrite := true.B
    }
    is("b100011".U) { // 假设操作码 100011 是 lw（加载指令）
      io.controlSignals.memRead := true.B
      io.controlSignals.regWrite := true.B
    }
    is("b101011".U) { // 假设操作码 101011 是 sw（存储指令）
      io.controlSignals.memWrite := true.B
    }
    // 可以继续根据更多的操作码进行设置
  }
}
