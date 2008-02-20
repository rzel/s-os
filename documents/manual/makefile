all:
	pdflatex main
	pdflatex main # The first generates the table of contents
	rm *.aux
clean:
	rm *.aux *.log *.ps

print:
	pdftops main.pdf
	psbook -s 4 main.ps manual.ps
	#psnup -n 2 -Pa5 -pa3 main2.ps manual.ps
	rm main.ps #main3.ps
