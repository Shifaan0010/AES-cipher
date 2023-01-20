CC = clang

a.out : main.o aes.o sub_bytes.o shift_rows.o mix_columns.o key_schedule.o aes.h
	$(CC) main.o aes.o sub_bytes.o shift_rows.o mix_columns.o key_schedule.o

main.o : main.c aes.h
	$(CC) -c main.c

aes.o : aes.c aes.h
	$(CC) -c aes.c

sub_bytes.o : sub_bytes.c aes.h
	$(CC) -c sub_bytes.c

shift_rows.o : shift_rows.c aes.h
	$(CC) -c shift_rows.c

mix_columns.o : mix_columns.c aes.h
	$(CC) -c mix_columns.c

key_schedule.o : key_schedule.c aes.h
	$(CC) -c key_schedule.c
