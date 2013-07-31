CPP=clang
CPPFLAGS=-O -Werror -MMD -std=c++11
LDLIBS=-lglfw -lGLU -lGL -lm

EXEC=Tragicum
OBJS=main.o
DEPS=${OBJS:.o=.d}

${EXEC}: ${OBJS}
	${CPP} ${OBJS} ${LDLIBS} -o ${EXEC}
clean:
	rm -vf ${EXEC} ${OBJS} ${DEPS}

-include ${DEPS}
