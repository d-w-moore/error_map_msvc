tst {
  *x = "";
  *y = "-1000";
  msierror_map(*x,*y);
  writeLine("stdout",*x)
  writeLine("stdout",*y)
}

INPUT  null
OUTPUT ruleExecOut
