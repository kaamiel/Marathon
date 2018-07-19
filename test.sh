#!/bin/bash

if [ $# -ne 2 ]
then

    echo -e "\n ./test.sh <prog> <dir>\t"\
    "uruchamia program <prog> dla wszystkich plików wejściowych <dir>/*.in,\n"\
    "porównuje wyniki z odpowiadającymi im plikami <dir>/*.out i <dir>/*.err i wypisuje efekty.\n"

else

  failed=0
  n=0

  tmp=$(mktemp -u)

  echo -e "\nTestuję $1 w katalogu $2..\n"

  for f in $2/*.in
  do

    ./$1 < $f > ${tmp}.out 2> ${tmp}.err
    
    echo -ne "\033[1;37m${f%.in}\033[0m\t"
    
    if diff ${f%in}out ${tmp}.out > /dev/null 2>&1
    then
      echo -ne "\033[0;32mout passed\033[0m\t"
    else
      echo -ne "\033[0;31mout failed\033[0m\t"
      ((++failed))
    fi
    
    
    if diff ${f%in}err ${tmp}.err > /dev/null 2>&1
    then
      echo -e "\033[0;32merr passed\033[0m"
    else
      echo -e "\033[0;31merr failed\033[0m"
      ((++failed))
    fi
    
    ((++n))

  done

  rm -f ${tmp}.{out,err}

  echo -e "\nFailed $failed out of $((2*$n)) tests ($n *.in files).\n"

fi

