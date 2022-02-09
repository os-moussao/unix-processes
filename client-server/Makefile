all: client server

%: %.c
	cc $< -o $@.out
%.out: %.c
	cc $< -o $@
cl:
	rm -f *.out
clean: cl
