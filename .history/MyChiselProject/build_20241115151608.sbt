name := "MyChiselProject"

version := "0.1"

scalaVersion := "2.13.10"

libraryDependencies ++= Seq(
  "edu.berkeley.cs" % "chisel3_2.13" % "3.5.0", // Chisel 3 依赖
  "org.scalatest" % "scalatest_2.13" % "3.2.9" % Test, // 测试框架
  "org.scalactic" % "scalactic_2.13" % "3.2.9" % Test // 测试框架
)
