# Building QEMU static build container 
I run arch, if you do too this can save a lot of time. QEMU is super picky with Clib, and Ubuntu has the right one.
```bash
cd docker
docker build . -t qemu-ioctl
```

After building the container, you can get an envirorment with qemu build deps already installed by running
`docker run -it  -v 'full_path_to_your_qemu_source:/qemu' qemu-ioctl:latest`

If everything went as planned you should now see something like:
`root@ca72f3da28f6:/#`

The number will be different, don't worry, it's ok. You should see a `/qemu` directory. This directory is the docker volume that enables data persistency across container. After all you want your compiled binary to stay after the container dies.

# Cloning qemu

Outside of the container, checkout the latest stable version. At the moment of writing this is 4.1. 

`git checkout origin/stable-4.1`

Inside the container, create a build directory, cd into it and run the following command:

```
../configure --disable-bsd-user --disable-guest-agent --disable-strip --disable-werror --disable-gcrypt --disable-debug-info --disable-debug-tcg --disable-tcg-interpreter --enable-attr --disable-brlapi --disable-linux-aio --disable-bzip2 --disable-cap-ng --disable-curl --disable-fdt --disable-glusterfs --disable-gnutls --disable-nettle --disable-gtk --disable-rdma --disable-libiscsi --disable-vnc-jpeg --disable-kvm --disable-lzo --disable-curses --disable-libnfs --disable-numa --disable-opengl --disable-vnc-png --disable-rbd --disable-vnc-sasl --disable-sdl --disable-seccomp --disable-smartcard --disable-snappy --disable-spice --disable-libusb --disable-usb-redir --disable-vde --disable-vhost-net --disable-virglrenderer --disable-virtfs --disable-vnc --disable-vte --disable-xen --disable-xen-pci-passthrough --disable-xfsctl --enable-linux-user --disable-system --disable-blobs --disable-tools --target-list=x86_64-linux-user --static --disable-pie
```

If this goes well you should be able to make qemu. The compiled binary should be in `build/x86_64-linux-user/`.
Also, if in the configure you change `--target-list=x86_64-linux-user` to `--target-list=arm-linux-user` it will build a static qemu that can run arm binaries.

# 