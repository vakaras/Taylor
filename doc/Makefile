default: fresh

# Sugeneruoti straipsnį.
konspektas.pdf:
	xelatex main.tex
	xelatex main.tex
	mv main.pdf aprašymas.pdf

fresh: clear konspektas.pdf

# Išvalyti šiukšles.
clean:
	rm -f *.aux *.log *.xdv *.out *.toc

# Ištrinti visus sugeneruotus failus.
clear: clean
	rm -f *.pdf
