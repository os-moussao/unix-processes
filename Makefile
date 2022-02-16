all:

%: %.c
	cc $< -o $@.out
%.out: %.c
	cc $< -o $@
clean:
	rm -f *.out

# remove txt files
rmtxt:
	rm -f *.txt

# alias
cl: clean rmtxt