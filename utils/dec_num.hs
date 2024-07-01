import Data.Char

decode :: Integer -> String -> Integer
decode acc [] = acc
decode acc (a:xs) =
    let digit = toInteger $ (ord a) - (ord '!')
    in  decode (acc * 94 + digit) xs

main = do
    s <- getLine
    -- putStrLn $ "line: " ++ s
    print $ decode 0 s