tst {
  #*x = "SYS_SOCK_OPEN_ERR";
  *y=""#*y = "-1000";
  msierror_map(*x,*y);
  writeLine("stdout",*x)
  writeLine("stdout",*y)
}

INPUT *x=$"SYS_NULL_INPUT"
OUTPUT ruleExecOut
