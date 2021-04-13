PROJ_NAME = typing_game
TEST_PROJ_NAME = Test_$(PROJ_NAME)

SRC =src/worddraw.c \
src/wordprint.c \
src/wordclear.c \
src/numberprint.c \

ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif


all:
	gcc -I $(INC_H) $(SRC) main.c -o $(call FixPath,$(PROJ_NAME).$(EXEC))
