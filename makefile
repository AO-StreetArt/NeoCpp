# Makefile Variables
INSTALL_DIR = /usr/local/include/

#Makefile Targets
tests:
	cd test && $(MAKE)

clean:
	cd test && $(MAKE) clean

install:
	cp -r neocpp $(INSTALL_DIR)/

uninstall:
	rm -r $(INSTALL_DIR)/neocpp
