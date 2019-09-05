import System.IO


gerarProlog:: IO()
gerarProlog = do
 entrada <- openFile "BaseDeDadosHaskell.txt" ReadMode
 saida <- openFile "BaseDeDadosProlog.txt" WriteMode     
 pegarLinha entrada saida
 putStrLn "Arquivo Criando Com Sucesso!\n"
 putStrLn "1º Passo: Abra o Arquivo \"ProgramaProlog.pl\"."
 putStrLn "2º Passo: Digite \"gps.\" no Compilador."
 hClose entrada
 hClose saida


pegarLinha entrada saida= 
            do ineof <- hIsEOF entrada
               if ineof
                  then return()
                  else do inpStr <- hGetLine entrada
                          let linha = split ',' inpStr
                          let cidadeOrigem = head linha
                          let cidadeDestino = head(tail linha)
                          let cidadeDistancia = head(tail(tail linha))
                          let auxDistanciaString = stringToFloat cidadeDistancia
                          let auxDistanciaCalculo = auxDistanciaString * 1.5
                          let cidadeTempo = floatToString auxDistanciaCalculo 
                          hPutStrLn saida ("caminho("++cidadeOrigem++","++cidadeDestino++","++cidadeDistancia ++","++cidadeTempo++").")
                          pegarLinha entrada saida
 

split :: Eq a => a -> [a] -> [[a]]
split x y = func x y [[]]
    where
        func x [] z = reverse $ map (reverse) z
        func x (y:ys) (z:zs) = if y==x then 
            func x ys ([]:(z:zs)) 
        else 
             func x ys ((y:z):zs)


stringToFloat string = read string :: Float 
floatToString float= show float
   

