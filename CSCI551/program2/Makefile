mmvec: mm.c
	icc -std=c99 -O2 -D -march=core-avx2  -qopt-report=5 -qopt-report-phase=vec mm.c -o  mmvec
mmnovec: mm.c 
	icc -std=c99  -O2 -D -march=core-avx2  -no-vec mm.c -o  mmnovec
clean: 
	rm -f *.o *.out *.optrpt mmnovec mmvec