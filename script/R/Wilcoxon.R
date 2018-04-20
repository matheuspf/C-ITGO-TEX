library(Skillings.Mack)

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


#citation("pwilcox");




names <- c("C-ITGO", "IAPSO", "IABC-MAL", "MBA", "LCA", "CMA-ES", "MVDE", "APSO")

# C-ITGO  IAPSO IABC-MAL  MBA  LCA   CMA-ES  MVDE  APSO

# >= 5
M <- matrix(
c(940.68, 12500, 15000, 47340, 15000, 4658, 15000, 50000, 
535.08, 2000, 15000, 7650, 15000, 19445, 10000, 120000, 
136.48, NA, 15000, 13280, NA, 1706, 7000, NA, 
856.4, 6000, NA, NA, 24000, NA, NA, 30000, 
491.24, 6000, 15000, 6300, 24000, 12998, 30000, 30000, 
1101.64, 7500, 15000, 70650, 24000, 30018, 15000, 200000, 
773, 800, NA, 1120, NA, NA, NA, 8000, 
286.48, 400, NA, NA, NA, NA, NA, 2000),
ncol=8, byrow=FALSE)



res <- list

for(i in 2:dim(M)[1])
{
    x <- M[c(1), ]
    y <- M[c(i), ]

	#(You can suppress the warning (due to ties) by specifying the argument exact=FALSE) 
	#explicacao na pagina 120 do livro
    #res <- wilcox.test(y, x, paired = TRUE, alternative = "greater",exact = FALSE)
	res <- wilcox.test(y, x, alternative="greater", exact = FALSE)
	
    print(names[i])
    print(res)
    writeLines("\n\n")
}


#citation("Skillings.Mack")


#res <- Ski.Mack(maty, simulate.p.value = TRUE, B = 1000)

#print('Mean rank')
#print(rowMeans(res[["rankdata"]]))