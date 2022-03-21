#!/bin/bash
# cmps101-pt.u19 grading
# usage: pa2.sh
# (run within your pa2 directory to test your code)

SRCDIR=https://raw.githubusercontent.com/houi-lin/cmps101-pt.u19.grading/master/pa2

EXE_ALL=( pa2-func-check.sh pa2-lunit-check.sh pa2-munit-check.sh pa2-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  curl $SRCDIR/${EXE_ALL[i]} > ${EXE_ALL[i]}
  chmod +x ${EXE_ALL[i]}
  ./${EXE_ALL[i]}
  rm -f ${EXE_ALL[i]}
done