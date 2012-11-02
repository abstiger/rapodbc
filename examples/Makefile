CC=gcc
CFLAGS=-Wall -g -O2 -fPIC -DPIC -I. -I..
LDFLAGS=-L. -L..
RAP=../rapodbc

EXAMPLES=t_dbs101_datasrc_def_cur.o \
	     t_dbs102_datasrc_index_cur.o \
	     t_dbs103_datasrc_field_cur.o \
	     t_dbs104_datasrc_field_cnt_sel.o \
	     t_dbs105_datasrc_field_def_sel.o \
	     t_dbs201_set_def_sel.o \
	     t_dbs202_set_cfg_cur.o \
	     t_dbs301_sdi_cur.o \
	     t_dbs302_ddi_cur.o \
	     t_dbs303_hdi_cur.o \
	     t_dbs304_hdi_day_sel.o \
	     t_dbs305_hdi_mon_sel.o \
	     t_dbs306_hdi_flag_sel.o \
	     t_dbs401_rule_cur.o

%.c: %.cfg
	$(RAP) $*

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

all: libexamples.so 

libexamples.so: $(EXAMPLES)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared $^ -ldbsbas -lodbc -o $@

clean:
	@rm -rf *.h *.c *.o *.so 
