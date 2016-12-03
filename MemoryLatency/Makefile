all: ko/enable_arm_pmu.ko program
perf_arm_pmu: program.c
	CC program
	@$(CC) -O0 -std=gnu99 program.c -o program 
ko/enable_arm_pmu.ko: ko/enable_arm_pmu.c
	KMOD ko/enable_arm_pmu.ko
	@$(MAKE) -C ko > /dev/null
runtests: all
	@./load-module
#	# @./program $(ARGS)
	@./program 1
	@./program 10
	@./program 100
	@./program 1000
	@./program 1200
	@./program 1300
	@./program 1400
	@./program 1500
	@./program 1600
	@./program 1800
	@./program 2000
	@./program 5000
	@./program 8000
	@./program 9000
	@./program 10000
	@./program 12000
	@./program 13000
	@./program 15000
	@./program 20000
	@./program 25000
	@./program 30000
	@./program 35000
	@./program 40000
	@./program 50000
	@./program 60000
	@./program 70000
	@./program 80000
	@./program 100000
	@./program 300000
	@./program 500000
#	#@./program 10000000
	@./unload-module

clean:
	@($(MAKE) -C ko clean > /dev/null) && rm -f program *.o *~
