for i in *.txt; do echo $i; ../../../code/dec_hs < $i | perl -pe 's/\n/\\n/g;' | sed -e 's/( \\ n1 -> (( \\ n2 -> (n1   (n2   n2 ) )  )   ( \\ n2 -> (n1   (n2   n2 ) )  ) )  )/fix/'  > ../hs2/$i.hs; done
