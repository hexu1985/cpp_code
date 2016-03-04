# test.c使用的makefile

CC = gcc
RM = rm -f
PROG = ./test
PROFOPT = -pg
PROFCMD = gprof
#COPT = -O2
OBJS = $(PROG).o
LDLIBS = -L/usr/local/lib/

test: $(OBJS)
	$(CC) $(COPT) -o $@ $(OBJS) $(LDLIBS)

profile: $(OBJS)
	$(CC) $(COPT) $(PROFOPT) $(PROG).c -o $(PROG) $(LDLIBS)
	$(PROG)
	$(PROFCMD) $(PROG)

clean:
	$(RM) $(PROG).o gmon.out $(PROG)

execute:
	$(PROG)

