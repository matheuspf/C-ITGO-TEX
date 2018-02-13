library(Skillings.Mack)



names <- c("DIRECT", "DIRECT-L", "ADC", "SGEO-QN", "DIRECT-KS", "C-ITGO")

#1: DIRECT
#2: DIRECT-L
#3: ADC
#4: SGEO-QN
#5: DIRECT-KS
#6: C-ITGO

M <- matrix(
c(198.89, 292.79, 176.25, 2161.0, 97.22, 151.3642,
  1117.7, 1785.73, 735.76, 14430.0, 491.28, 734.501,
  47282.89, 18983.55, 5014.13, 102678.0, 3675.84, 4994.541,
  16057.46, 16758.44, 5129.85, 61064.0, 3759.05, 4628.6193,
  1063.78, 1267.07, 675.74, 5853.0, 192.00, 459.0552,
  42322.65, 4858.93, 2006.82, 29937.0, 618.32, 1000.5385,
  95708.25, 68754.02, 16473.02, 186297.0, 5524.77, 8233.7342,
  217215.58, 269064.35, 30471.83, 175124, 22189.47, 32635.435
),
ncol=8, byrow=FALSE)


res <- list

for(i in 1:6)
{
    x <- M[c(5), ]
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