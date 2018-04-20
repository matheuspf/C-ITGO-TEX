#! /bin/bash

pdflatex -halt-on-error -output-directory=out -jobname=ITGO main.tex
bibtex out/ITGO.aux
pdflatex -halt-on-error -output-directory=out -jobname=ITGO main.tex
pdflatex -halt-on-error -output-directory=out -jobname=ITGO main.tex

cp out/ITGO.pdf pdf/ITGO.pdf