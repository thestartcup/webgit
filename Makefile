COFFEE = coffee -c
CC = emcc -c
OPT = -O2
INCLUDES = -Ideps/libgit2/include
CFLAGS = $(OPT) $(INCLUDES)
LD = emcc
LIBDIRS = -Ldeps/libgit2/build
LIBS = -lgit2
LDFLAGS = $(OPT) $(LIBDIRS) -s WASM=1

JSFILES = src/webgit.js
OBJS = src/clone.bc src/init.bc

all: webgit.min.js

test: test.html

test.html: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

webgit.min.js: $(JSFILES)
	cat $^ | uglifyjs -cmo $@

%.js: %.coffee
	$(COFFEE) -p $< > $@

%.bc: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f webgit.min.js $(JSFILES) $(OBJS) test*
