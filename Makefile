# display all warnings (-Wall) for wrong code
# -Wextra -pedantic just more warnings
# -std=c99 set c version to be used
CFLAGS = -Wall -Wextra -pedantic -std=c99
PREREQUISITES = main.c error/error.c error/error.h raw/raw.c raw/raw.h keys/keys.h keys/keys.c

# build target "editor" with variable "PREREQUISITES" as required PREREQUISITES to build it
editor: $(PREREQUISITES)	 								
# $() to reference variables, implicit variable "CC" expands to command "cc"
# compile "PREREQUISITES" using cc with output(-o) named "editor"
	$(CC) $(PREREQUISITES) -o editor ${CFLAGS}

run:
	./editor

clean:
	rm -f editor		
