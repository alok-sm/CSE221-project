all: ko/enable_arm_pmu.ko program
perf_arm_pmu: program.c
	@echo CC program
	@$(CC) -O3 -std=gnu99 program.c -o program 
ko/enable_arm_pmu.ko: ko/enable_arm_pmu.c
	@echo KMOD ko/enable_arm_pmu.ko
	@$(MAKE) -C ko > /dev/null
runtests: all
	@echo SUDO load-module
	@./load-module
	@./program 1 
	@./program 2 
	@./program 4 
	@./program 8 
	@./program 16 
	@./program 32
	@./program 64 
	@./program 128 
	@./program 256 
	@./program 512 
	@./program 1024
	@./program 2048 
	@./program 4096
	@./program 8192 
	@./program 16384 
	@./program 32000 
	@./program 32768 
	@./program 65536 
	@./program 131072 
	@./program 262144 
	@./program 524288
	@./program 1048576 
	@./program 2097152 
	@echo SUDO unload-module
	@./unload-module

clean:
	@($(MAKE) -C ko clean > /dev/null) && rm -f program *.o *~
