tst {
  *x = "";
  *y=""    # *y = "-1000";
  msierror_map(*x,*y);
  *z1 = split(*x,"\n")
  *z2 = split(*y,"\n")
  *s = size(*z1)
  for (*i=0 ; *i < *s;  *i = *i + 1)
  {
     writeLine ("stdout", elem(*z2,*i) ++ "\t"++elem(*z1,*i) )
  }
}

INPUT  null
OUTPUT ruleExecOut
