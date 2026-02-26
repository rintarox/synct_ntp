## Synct
Small c-program to get NTP time variables by means of libntpq.a and libntp.a

### Building and usage of NTP

Manual building of utilities and static libraries:

1) ./bootstrap      - preparation of configure enviroment
2) ./configure      - autoconfiguration for current system.

View information about flags ./configure --help=recursive 

2.1) To Disable non used functions in this project you need to set flags:

```
export ac_cv_search_MD5Init=no && ./configure --without-crypto --disable-doxygen-html --disable-samples --disable-thread-support
```

3) make (in root directory) - build libraries and NTP utils.

4) To use functions from libntp.a | libntpq.a with gcc set flags:

```
cc -I~/ntp/ -I~/ntp/include -I~/ntp/libntp/lib/isc/include -I~/ntp/libntp/lib/isc/unix/include -I~/ntp/ntpq/ -o app app.c ~/ntp/ntpq/libntpq.a ~/ntp/libntp/libntp.a -lm
```

- ntp/				- configure files storage => config.h
- ntp/include			- main header files for libntp => libntp.h 
- ntp/libntp/lib/isc/include	- inner function for platform depended building => isc/platform.h 
- ntp/libntp/lib/unix/include	- header for unix systems => isc/net.h
- ntp/ntpq			- header files of libntpq => libntpq.h 

If writing your own software dont forget to include config.h !BEFORE! libntpq.h   // few days ago tried to find mistake for hours ._.
Like in example below
```
#include "config.h"
#include "libntpq.h"

int func (void) { . . . }
```

-- --
### Result 

Preview of the output:

<img src="Example1.png" width="400" alt="Exmaple1">
