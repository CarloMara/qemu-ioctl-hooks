# QEMU IOCTL Hooks
Here you can find everything you need to reproduce [the post](https://carlo.marag.no/posts/qemu-ioctl-hooks/)

# QEMU build environment using Docker
I run arch. If you do too, this can save a lot of time. QEMU is super picky with GLIB, and Ubuntu has the right one.
```bash
cd docker
docker build . -t qemu-ioctl
```

After building the container, you can get an environment with QEMU build dependencies already installed by running
`docker run -it  -v 'full_path_to_your_qemu_source:/qemu' qemu-ioctl:latest`

If everything went as planned you should now see something like:
`root@ca72f3da28f6:/#`

You should see a `/qemu` directory. Here is the docker volume that enables data persistence across the container. After all, you want your compiled binary to stay after the container dies.

# Cloning qemu

Outside of the container, check out the latest stable version. At the moment of writing, this is 4.1. 

`git checkout origin/stable-4.1`

Inside the container, create a build directory, cd into it and run the following command:

```
../configure --disable-bsd-user --disable-guest-agent --disable-strip --disable-werror --disable-gcrypt --disable-debug-info --disable-debug-tcg --disable-tcg-interpreter --enable-attr --disable-brlapi --disable-linux-aio --disable-bzip2 --disable-cap-ng --disable-curl --disable-fdt --disable-glusterfs --disable-gnutls --disable-nettle --disable-gtk --disable-rdma --disable-libiscsi --disable-vnc-jpeg --disable-kvm --disable-lzo --disable-curses --disable-libnfs --disable-numa --disable-opengl --disable-vnc-png --disable-rbd --disable-vnc-sasl --disable-sdl --disable-seccomp --disable-smartcard --disable-snappy --disable-spice --disable-libusb --disable-usb-redir --disable-vde --disable-vhost-net --disable-virglrenderer --disable-virtfs --disable-vnc --disable-vte --disable-xen --disable-xen-pci-passthrough --disable-xfsctl --enable-linux-user --disable-system --disable-blobs --disable-tools --target-list=x86_64-linux-user --static --disable-pie
```

If this goes well, you should be able to make QEMU. The compiled binary should be in `build/x86_64-linux-user/`.
If you change `--target-list=x86_64-linux-user` to `--target-list=arm-linux-user`, you build a static QEMU that can run arm binaries. Useful for real embedded stuff

# Building the example

```bash
cd ioctl_test
gcc dump_info.c -o dump_info
```

You can then look at the post for the other steps.

# Appling the patch

In `qemu_patch`, there's diff with the modifications needed to run the last example. This patch is tested only on `stable-4.1`

