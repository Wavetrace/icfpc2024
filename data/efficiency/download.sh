# example
for i in `seq 13`; do echo $i; echo -n 'get efficiency'$i | ./tr_str -ei | ../icfpc2024/utils/send.sh |  ./../icfpc2024/code/dec | tee ../icfpc2024/data/efficiency/$i.txt; sleep 1.2; done