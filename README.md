# error_map_msvc

```
  --- perrtab.r

  *s=""; *i=""
  msierror_map(*s,*i)  # fill *s with "\n" delimited string error names
                       #  and *i with "\n" delimited corresponding integers
  --- ermap.r
  *s = ""; *i = "<some_integer>"
  msierror_map(*s,*i)  # *s is zero length,  fetch the error name from int(*i)

  --- ermapf.r
  *s="<SOME_ERROR_NAME>"
  msierror_map(*s,*i)  # if *s is nonzero length,  store stringized error integer into *i

