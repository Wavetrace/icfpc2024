((( \ n1 -> (( \ n2 -> (n1   (n2   n2 ) )  )   ( \ n2 -> (n1   (n2   n2 ) )  ) )  )   ( \ n3 -> ( \ n4 -> ((( \ n1 -> ( \ n2 -> if (n1  < n2 )  then n1  else n2   )  )   n4 )   (1  + if (n4  > 2 )  then (((( \ n1 -> (( \ n2 -> (n1   (n2   n2 ) )  )   ( \ n2 -> (n1   (n2   n2 ) )  ) )  )   ( \ n5 -> ( \ n6 -> ( \ n7 -> if (n6  == n4 )  then n7  else ((n5   (n6  + 1 ) )   if ((n3   n6 )  > (n6  - 1 ) )  then if ((n4  `mod` n6 )  == 0 )  then ((n7  `div` (n3   n6 ) )  * ((n3   n6 )  - 1 ) )  else n7   else n7  )   )  )  ) )   2 )   n4 )  else n4  ) )  )  ) )   1234567 ) 