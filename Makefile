# build target "editor" with "editor.c" as required prerequisite to build it
editor: editor.c									

# $() to reference variables, implicit variable "CC" expands to command "cc"
# compile "editor.c" using cc with output(-o) named "editor"
# display all warnings (-Wall) for wrong code
# -Wextra -pedantic just more warnings
# -std=c99 set c version to be used
	$(CC) editor.c -o editor -Wall -Wextra -pedantic -std=c99		
