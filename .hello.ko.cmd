cmd_/root/kernel_module/hello.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o /root/kernel_module/hello.ko /root/kernel_module/hello.o /root/kernel_module/hello.mod.o
