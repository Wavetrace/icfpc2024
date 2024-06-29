for i in *.txt; do echo $i; ../../../code/dec_hs < $i > ../hs/$i.hs; done
