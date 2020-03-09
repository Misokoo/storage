#
# Ce Makefile contient les cibles suivantes :
#
# all   : compile le programme
# clean : supprime les fichiers générés automatiquement
# test  : lance tous les tests (scripts shell test-xxx.sh)

CFLAGS = -g -Wall -Wextra -Werror -Wvla

PROGS = backup

all: $(PROGS)

test: all
	@for i in test-*.sh ; do echo $$i ; sh $$i || exit 1 ; done

moodle:
	@rm -rf moodle
	mkdir moodle
	cp Makefile *test*.sh moodle
	tar czf moodle.tgz moodle
	rm -rf moodle

clean:
	rm -f *.o $(PROGS)
	rm -f *.log
	rm -f moodle.tgz

