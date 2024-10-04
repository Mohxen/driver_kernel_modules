# Char Device Kernel Module

```bash
sudo make
```

## The Output: `char_device.ko`

Your kernel module `char_device.ko` has been successfully created. This is the compiled kernel object file (module) that you can now load into the kernel.

### Next Steps: Loading and Unloading the Module

#### 1. Load the Kernel Module:
Use `insmod` to insert the module into the running kernel:

```bash
sudo insmod char_device.ko
```

#### 2. Check if the Module is Loaded:

```bash
sudo lsmod | grep hello
```

#### 3. Check the Kernel Log:

```bash
sudo dmesg | tail
```

#### 4. Create the Device File:

```bash
sudo mknod /dev/char_device c 511 0
sudo chmod 666 /dev/char_device
```

#### 5. Test the Device:

```bash
echo "Hello from user space" > /dev/char_device
cat /dev/char_device
```

#### 6. Unload the Kernel Module:

```bash
sudo rmmod char_device
```

#### 7. Check the kernel log again to ensure the driver was unloaded properly:

```bash
sudo dmesg | tail 
```