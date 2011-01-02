default: fresh

# Sugeneruoti straipsnį.
konspektas.pdf:
	xelatex -shell-escape main.tex
	bibtex main
	xelatex -shell-escape main.tex
	xelatex -shell-escape main.tex
	mv main.pdf aprašymas.pdf

fresh: clear konspektas.pdf

# Išvalyti šiukšles.
clean:
	rm -f *.aux *.log *.xdv *.out *.toc

# Ištrinti visus sugeneruotus failus.
clear: clean
	rm -f *.pdf
