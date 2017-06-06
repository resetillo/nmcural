#set TARGET = main.abs

#$(TARGET): main.c div.s
#$(TARGET): main.c randuniform.s sortascend.s dsortascend.s sortdescend.s fsorta.s fsortd.s dsortdescend.s
nmc-gcc -g -mgas div_c.c  -c -I./include
#nmc-gcc -g -mgas div/div_c.c -c -I./include
#nmc-as-gnu -c -g -nmc4
#nmc-as-gnu -c -g -nmc4 -o sortd.o sortdescend.s
#nmc-as-gnu -c -g -nmc4 -o dsorta.o dsortascend.s
#nmc-as-gnu -c -g -nmc4 -o dsortd.o dsortdescend.s
#nmc-as-gnu -c -g -nmc4 -o fsorta.o fsorta.s
#nmc-as-gnu -c -g -nmc4 -o fsortd.o fsortd.s
#nmc-gcc -g -mgas test/test_sort.c -c -I./include
#nmc-gcc -g -mgas main.o rand.o test_sort.o sort.o sortd.o dsorta.o dsortd.o fsorta.o fsortd.o -o$(TARGET)

nmc-gcc -g -mgas div_c.o
# div_c.o
#all: $(TARGET)
#nmc-emurun.sh main.o
