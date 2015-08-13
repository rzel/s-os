## Building a CD image ##
_You do not **need** to build a CD image if you just want to try Sos. There are images available at the download page_

If you change the SoS Source code, you must rebuild the kernel. Instructions for doing this are on the [Building](Building.md) page.

## Burning a CD Image ##
In some operating systems, like most Linux distributions, you can simply double click the .iso file, and it will be burnt to a CD-Rom. In Mac OS X, you can burn the iso with Disk Utility. Most other operating systems require you to download or buy a third party application to burn the image.

## Running SoS ##
If you burnt a CD image, simply restart your computer with it in the drive. If your computer is set to boot from CD (if not, check your bios settings), then SoS will automatically start.

Alternatively, you can run the image in an emulator like Bochs, VMware, Virtualbox etc.

Another method of running SoS is to make an entry in your grub menu configuration file, pointing to the kernel.sys file.