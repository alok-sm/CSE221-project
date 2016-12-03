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
	@./program  ${ARGS}
	@echo SUDO unload-module
	@./unload-module

clean:
	@($(MAKE) -C ko clean > /dev/null) && rm -f program *.o *~
