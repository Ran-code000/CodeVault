// same 3-point moving average filter as before
visualize(() => new FirFilter(8, Seq(1.U, 1.U, 1.U)))