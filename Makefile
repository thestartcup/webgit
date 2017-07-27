COFFEE = coffee -c

JSFILES = src/webgit.js

all: webgit.min.js

webgit.min.js: $(JSFILES)
	cat $^ | uglifyjs -cmo $@

%.js: %.coffee
	$(COFFEE) -p $< > $@

clean:
	rm -f webgit.min.js $(JSFILES)
