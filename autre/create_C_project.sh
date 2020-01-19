if [ $# -ne 1 ]
then
  mkdir bin include obj src
  touch makefile
  echo "CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -g

LDLIBS?=

INCLUDE_PATH = ./include

TARGET   = exec

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := \$(wildcard \$(SRCDIR)/*.c)
INCLUDES := \$(wildcard \$(INCLUDE_PATH)/*.h)
OBJECTS  := \$(SOURCES:\$(SRCDIR)/%.c=\$(OBJDIR)/%.o)

\$(BINDIR)/\$(TARGET): \$(OBJECTS)
	mkdir -p \$(BINDIR)
	\$(CC) -o \$@ \$^ \$(CFLAGS) \$(LDLIBS)
	@echo \"Linking complete!\"

\$(OBJECTS): \$(OBJDIR)/%.o : \$(SRCDIR)/%.c
	mkdir -p \$(OBJDIR)
	\$(CC) -o \$@ -c \$< \$(CFLAGS) -I\$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f \$(OBJDIR)/*.o
	rm -f \$(OBJDIR)/*.gcda
	rm -f \$(OBJDIR)/*.gcno
	rm -f \$(BINDIR)/\$(TARGET)

all: \$(BINDIR)/\$(TARGET)" > makefile
  echo "project creation done"
else
  if [ $1 = "delete" ]
  then
    rm src/*.c
    rm include/*.h
    rm bin/*
    rm obj/*
    rm makefile
    rmdir src include bin obj
    echo "project deleted"
  else
    touch "src/$1.c"
    touch "include/$1.h"
    echo "#include <stdio.h>
 #include <stdlib.h>
 #include \"$1.h\"
 int main()
 {
   printf(\"Hello Michael\\n\");
   return 0;
 }" > "src/$1.c"
    echo "src/$1.c created"
    echo "include/$1.h created"
  fi
fi
