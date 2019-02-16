#
# makefile for mkdoc's sample
#
.SUFFIXES: .html -j.html
RM = rm -f
CP = cp -p

#
# making with making idxhtml
#
idxhtml = $(HOME)/export/mkdoc-1j/idxhtml

#
# install.html directory
#
HTML_DIR = /home/taiji/homepage/misc/software/xbgi-3_0

#
# sub directories
#
SUBDIRS =

#
# index, index text and items in English
#
HTMLS       =
INDEX       = index.html
INDEX_ITEMS = readme.doc copying.doc install.doc notice.doc problem.doc $(HTMLS)

#
# index, index text and items in Japanese
#
BHTMLS       = 
BINDEX       = index-j.html
BINDEX_ITEMS = readmej.doc copyingj.doc installj.doc noticej.doc problemj.doc $(HTMLS)

#
# bulid all
#
all: $(INDEX) $(BINDEX)

$(INDEX): $(INDEX_ITEMS)
	env LANG=C $(idxhtml) $(INDEX_ITEMS) > $@

$(BINDEX): $(BINDEX_ITEMS)
	env LANG=ja $(idxhtml) $(BINDEX_ITEMS) | euctojis > $@

$(HTMLS) $(BHTMLS):
	cd $(dir $@); $(MAKE)

#
# clean all
#
clean:
	-$(RM) $(HTMLS) $(INDEX)
	-$(RM) $(BHTMLS) $(BINDEX)
#	-$(RM) *~ core
#	@for i in $(SUBDIRS);\
#	do\
#		(cd $$i; $(MAKE) clean);\
#	done

#
# install.html
#
install.html:
	$(CP) $(INDEX) $(HTMLS) $(HTML_DIR)
	$(CP) $(BINDEX) $(BHTMLS) $(HTML_DIR)
