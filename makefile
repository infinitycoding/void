
all:
	$(MAKE) -C src
	$(MAKE) -C test

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean

style:
	$(MAKE) -C src style
	$(MAKE) -C test style

