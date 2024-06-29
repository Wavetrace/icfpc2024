for i in `seq 21`; do echo $i; echo -n 'get lambdaman'$i | ./tr_str -ei | ../icfpc2024/utils/send.sh |  ./tr_str -in | tee ../icfpc2024/data/lamdaman/$i.txt; sleep 1.2; done
