("L"  ++ ((fix   ( \ n1 -> ( \ n2 -> if (n2  == 2500 )  then "Hn"  else if ((n2  `mod` 50 )  == 0 )  then "\n"  else "Hn"    )  ) )   if ((n2  `mod` 11 )  == 0 )  then "#"  else "."  ) ) 