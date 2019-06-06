export NAME:=hashtable
EXE:=.exe
#--------------------
export TESTS
export CFLAGS:=-Wall -std=c11 -pedantic -Wextra -I../include $(CFLAGS)
PREFIX:=${or $(PREFIX),$(PREFIX),/usr/local}
includes=${wildcard include/*.h}

.PHONY: build
build:
	$(MAKE) -C src

.PHONY: example
example:
	$(MAKE) -C src $(NAME)
	cp src/$(NAME) $(NAME)$(EXE)

.PHONY: test
test: build
	$(MAKE) -C test

.PHONY: install
install: build
	mkdir -p "$(PREFIX)/lib"
	mkdir -p "$(PREFIX)/include"
	cp src/lib$(NAME).a "$(PREFIX)/lib"
	cp $(includes) "$(PREFIX)/include"

.PHONY: uninstall
uninstall:
	$(RM) "$(PREFIX)/lib/lib$(NAME).a"
	$(RM) ${foreach header,$(includes),"$(PREFIX)/$(header)"}

.PHONY: clean
clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	$(RM) $(NAME)$(EXE)
