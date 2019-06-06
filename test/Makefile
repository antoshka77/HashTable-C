src = ${wildcard *.c}
DEFAULT_TEST:= ${src:.c=.test}
test:=${or ${TESTS},${TESTS},${DEFAULT_TEST}}

test: $(test)

%.test: %.c ../src/lib${NAME}.a
	$(CC) $(CFLAGS) -DTEST -I../src $< -L../src -l$(NAME) -o $@
	$(GDB) ./$@
	@$(RM) $@

.PHONY: clean
clean:
	$(RM) $(DEFAULT_TEST)
