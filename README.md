# How to use

We provide 3 examples for nuclei sdk amp examples used with linux sdk.

1. Clone Nuclei SDK

~~~shell
git clone https://github.com/Nuclei-Software/nuclei-sdk
cd nuclei-sdk
git switch develop
export NUCLEI_SDK_ROOT=$(pwd)
~~~

2. Clone Nuclei Linux SDK

~~~shell
# follow https://github.com/Nuclei-Software/nuclei-linux-sdk#clone-repo to clone repo
export NUCLEI_LINUXSDK_ROOT=/path/to/linuxsdk
~~~

3. Generate amp binaries

Take ``rtamp`` as example.

~~~shell
cd $NUCLEI_SDK_ROOT
git clone https://github.com/Nuclei-Software/nsdk_ampdemo
cd nsdk_ampdemo
cd rtamp
./gen.sh $NUCLEI_LINUXSDK_ROOT
~~~

4. Change Linux SDK

Assume we are using evalsoc UX900FD SMP 8 Core, and AMP Core start from hartid = 2.

Then we need to do following changes to nuclei linux sdk.

~~~diff
diff --git a/conf/evalsoc/build.mk b/conf/evalsoc/build.mk
index 76e594f..d158f17 100644
--- a/conf/evalsoc/build.mk
+++ b/conf/evalsoc/build.mk
@@ -4,13 +4,13 @@ QEMU_MACHINE_OPTS := -M nuclei_u,download=flashxip -smp 8 -m 1.5G
 # initramfs pre command before generate initrd ramfs
 INITRAMFS_PRECMD := bash $(confdir)/preramfs.sh $(confdir) $(buildroot_initramfs_sysroot) copyfiles.txt
 # eg. $(confdir)/amp/cx.bin
-CORE1_APP_BIN :=
-CORE2_APP_BIN :=
-CORE3_APP_BIN :=
-CORE4_APP_BIN :=
-CORE5_APP_BIN :=
-CORE6_APP_BIN :=
-CORE7_APP_BIN :=
+CORE1_APP_BIN := $(confdir)/amp/amp_c1.bin
+CORE2_APP_BIN := $(confdir)/amp/amp_c2.bin
+CORE3_APP_BIN := $(confdir)/amp/amp_c3.bin
+CORE4_APP_BIN := $(confdir)/amp/amp_c4.bin
+CORE5_APP_BIN := $(confdir)/amp/amp_c5.bin
+CORE6_APP_BIN := $(confdir)/amp/amp_c6.bin
+CORE7_APP_BIN := $(confdir)/amp/amp_c7.bin

 # Freq Settings
...skipping...
-CORE4_APP_BIN :=
-CORE5_APP_BIN :=
-CORE6_APP_BIN :=
-CORE7_APP_BIN :=
+CORE1_APP_BIN := $(confdir)/amp/amp_c1.bin
+CORE2_APP_BIN := $(confdir)/amp/amp_c2.bin
+CORE3_APP_BIN := $(confdir)/amp/amp_c3.bin
+CORE4_APP_BIN := $(confdir)/amp/amp_c4.bin
+CORE5_APP_BIN := $(confdir)/amp/amp_c5.bin
+CORE6_APP_BIN := $(confdir)/amp/amp_c6.bin
+CORE7_APP_BIN := $(confdir)/amp/amp_c7.bin

 # Freq Settings
 TIMER_HZ ?=
diff --git a/conf/evalsoc/freeloader.mk b/conf/evalsoc/freeloader.mk
index 54d4746..e570dba 100644
--- a/conf/evalsoc/freeloader.mk
+++ b/conf/evalsoc/freeloader.mk
@@ -12,4 +12,4 @@ ENABLE_SMP ?= 1
 ENABLE_L2 ?= 1
 AMPFW_START_OFFSET ?= 0x5E000000
 AMPFW_SIZE ?= 0x400000
-AMP_START_CORE ?= 8
+AMP_START_CORE ?= 2
~~~

5. Generate freeloader and boot images

With above changes, then we can build freeloader with amp binaries.

~~~shell
cd $NUCLEI_LINUXSDK_ROOT
# generate freeloader
make SOC=evalsoc CORE=ux900fd freeloader
# generate boot images
make SOC=evalsoc CORE=ux900fd bootimages
~~~

If bitstream and debug probe are connected to PC, then you can program freeloader
and place generated boot images to SDCard.

~~~shell
# flash freeloader to flash
make SOC=evalsoc CORE=ux900fd upload_freeloader
~~~

## Sample output

### amp binaries generation

~~~
$ ./gen.sh /Local/hqfang/workspace/software/nuclei-linux-sdk
Generate amp binaries for SOC=evalsoc, linux sdk /Local/hqfang/workspace/software/nuclei-linux-sdk
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c1.bin
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c2.bin
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c3.bin
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c4.bin
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c5.bin
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c6.bin
Clean all build objects
Generate gcc.ld from gcc_evalsoc.ld
   text    data     bss     dec     hex filename
  15214    1952   10616   27782    6c86 ampdemo.elf
riscv-nuclei-elf-objcopy ampdemo.elf -O binary ampdemo.bin
Copy ampdemo.bin -> /Local/hqfang/workspace/software/nuclei-linux-sdk/conf/evalsoc/amp/amp_c7.bin
~~~

### Sample output of running linux together with amp rt-thread on evalsoc ux900fd 8core

Please check [linux_rtos_amp.txt](linux_rtos_amp.txt).
