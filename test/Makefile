.PHONY: all
all: bitmap etest hello simple test

.PHONY: bitmap
bitmap:
	idris --build bitmap.ipkg

.PHONY: etest
etest:
	-idris --build etest.ipkg

.PHONY: hello
hello:
	idris --build hello.ipkg

.PHONY: events
events:
	idris --build events.ipkg

.PHONY: test
test:
	idris --build test.ipkg
