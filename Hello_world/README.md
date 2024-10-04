# Hello World Kernel Module
```bash
make 

## The Output: `hello.ko`

Your kernel module `hello.ko` has been successfully created. This is the compiled kernel object file (module) that you can now load into the kernel.

### Next Steps: Loading and Unloading the Module

#### 1. Load the Kernel Module:
Use `insmod` to insert the module into the running kernel:

```bash
sudo insmod hello.ko```

#### 2. Check if the Module is Loaded:

```bash
sudo lsmod | grep hello```

#### 3. Check the Kernel Log:

```bash
sudo dmesg | tail```

#### 4. Unload the Kernel Module:

```bash
sudo rmmod hello```

#### 5. Check the kernel log again for the "Goodbye, World!" message:

```bash
sudo dmesg | tail```