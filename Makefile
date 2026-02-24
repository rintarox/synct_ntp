all: ntp app

ntp: reconfigure
	$(MAKE) -C ntp

reconfigure: confinit
	cd ntp && export ac_cv_search_MD5Init=no && ./configure --without-crypto --disable-doxygen-html --disable-samples --disable-thread-support

confinit: ntp/bootstrap
	cd ntp && ./bootstrap

app: ntp
	cc -Intp/ -Intp/include -Intp/libntp/lib/isc/include -Intp/libntp/lib/isc/unix/include -Intp/ntpq/ -o cntab cntab.c ntp/ntpq/libntpq.a ntp/libntp/libntp.a -lm

clean: 
	$(MAKE) -C ntp clean
	rm -rf ./appendix/*

.PHONY: all ntp app clean reconfigure
