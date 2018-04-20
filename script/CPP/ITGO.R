library(Skillings.Mack)
library(MASS)

#1: C-ITGO - 8
#2: IAPSO - 7
#3: SAMP-Jaya - 4
#4: IABC-MAL - 5
#5: PSO-DE - 3
#6: HPSO - 3
#7: MBA - 6
#8: LCA - 5
#9: NM-PSO -2
#10: CB-ABC - 3
#11: QPSO - 2
#12: G-QPSO -2
#13: DELC - 3
#14: CMA-ES - 5
#15: MVDE - 5
#16: IPSO - 3
#17: WCA - 4
#18: APSO - 7





# C-ITGO  IAPSO  SAMP-Jaya  IABC-MAL  PSO-DE  HPSO  MBA  LCA  CB-ABC  DELC  CMA-ES  MVDE  IPSO  WCA  APSO



# >= 3
maty <- matrix(
c(940.68, 12500, 3618.25, 15000, 66600, 81000, 47340, 240000, 15000, 15000, 20000, 4658, 15000, 20000, 46450, 100000, 50000, 
535.08, 2000, 6861, 15000, 24950, 81000, 7650, 240000, 15000, 15000, 20000, 19445, 10000, 20000, 11750, 100000, 120000, 
136.48, NA, NA, 15000, 17600, NA, 13280, NA, NA, NA, 10000, 1706, 7000, NA, NA, NA, NA, 
856.4, 6000, NA, NA, NA, NA, NA, NA, 24000, NA, NA, NA, NA, 20000, NA, NA, 30000, 
491.24, 6000, 3744.66, 15000, 54350, NA, 6300, NA, 24000, 15000, 30000, 12998, 30000, 20000, 15150, NA, 30000, 
1101.64, 7500, 6513.33, 15000, 42100, 81000, 70650, 240000, 24000, 15000, 30000, 30018, 15000, 20000, 27500, 100000, 200000, 
773, 800, NA, NA, NA, NA, 1120, NA, NA, NA, NA, NA, NA, NA, NA, 100000, 8000, 
286.48, 400, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 20000, 500, NA, 2000),
ncol=8, byrow=FALSE)




# C-ITGO  IAPSO IABC-MAL  MBA  LCA   CMA-ES  MVDE  APSO


if(FALSE)
{
# >= 5
maty <- matrix(
c(940.68, 12500, 15000, 66600, 47340, 15000, 20000, 4658, 15000, 20000, 46450, 50000, 
535.08, 2000, 15000, 24950, 7650, 15000, 20000, 19445, 10000, 20000, 11750, 120000, 
136.48, NA, 15000, 17600, 13280, NA, 10000, 1706, 7000, NA, NA, NA, 
856.4, 6000, NA, NA, NA, 24000, NA, NA, NA, 20000, NA, 30000, 
491.24, 6000, 15000, 54350, 6300, 24000, 30000, 12998, 30000, 20000, 15150, 30000, 
1101.64, 7500, 15000, 42100, 70650, 24000, 30000, 30018, 15000, 20000, 27500, 200000, 
773, 800, NA, NA, 1120, NA, NA, NA, NA, NA, NA, 8000, 
286.48, 400, NA, NA, NA, NA, NA, NA, NA, 20000, 500, 2000),
ncol=8, byrow=FALSE)
#citation("Skillings.Mack")
}

res <- Ski.Mack(maty, simulate.p.value = TRUE, B = 5000)

print('Mean rank')
print(rowMeans(res[["rankdata"]]))

alfa=0.05
k=res[["Ntreatments"]]

#cálculo do qui-quadrado
print('Chi-Squared')
x2=qchisq(1-alfa,k-1)
print(x2)

#Cálculo do Skillings-Mack
T=res[["adjustedSum"]]%*%ginv(res[["varCovarMatrix"]])%*%t(res[["adjustedSum"]])
print('Cálculo do Skillings-Mack')
print(T)

if(T>=x2) {
  print("Rejeita H0 - Pelo Menos Um Metodo eh Superior aos Demais")
} else {
  print("Aceita H0 - Não ha Diferença Estatistica entre os Metodos eh Superior aos Demais") 
}

comparacao<-matrix(c(rep(0,k*k)),nrow=k, ncol=k)
adj<-res[["adjustedSum"]]

for(i in 1:k-1){
  l<-i+1 
  for(j in l:k){
    comparacao[i,j]=abs(adj[j]-adj[i])   
  }
}
print("Comparacao")
print(comparacao)

#supoem-se que o controle seja o primeiro
comparacaocontrole<-c(rep(0,k))
for(i in 2:k){
   comparacaocontrole[i]=abs(adj[i]-adj[1])
}
print("Comparacao Controle")
print(comparacaocontrole)

#conta o número de testes/instâncias com valores para cada Grupo/Técnica
matdados<-res[["rawdata"]]
n<-res[["Nblocks"]]
vetT<-matrix(c(rep(0,n)),nrow=1,ncol=n)
for(i in 1:n){
  for(j in 1:k){
    if(!is.na(matdados[i,j])){
	   vetT[i]<-vetT[i]+1;
    }	
  }
}

print("Numero de Valores Validos em Cada Grupo/Tecnica")
print(vetT)

#verifica pela estatística que o controle eh melhor que os outros
estatcomparacao<-c(rep(0,k))
for(i in 1:k){
   estatcomparacao[i]=sqrt(2*qchisq(1-alfa,k-1)*(vetT[i]+(k-1)*n))
}
print("Estatistica de Controle")
print(estatcomparacao)

#faz a comparacao final com a estatistica
for(i in 1:k){
   if(comparacaocontrole[i]>estatcomparacao[i]){
      print("controle eh melhor que grupo/tecnica ")
	  print(i)
   }
}

#sqrt(2*qchisq(1-0.05,5-1)*(727+(5-1)*745))

#sqrt((n+1)*(k*n-k+1)/12)*cRangeNor(0.05,k)
