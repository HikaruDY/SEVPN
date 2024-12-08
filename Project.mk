OUTPUT_DIR = bin

CFLAGS_INTERNAL = -I$(SROOT)/src/ -O2
CFLAGS_INTERNAL += -Wno-cpp -Wno-implicit-function-declaration -Wno-deprecated-declarations -Wno-incompatible-pointer-types -Wno-pointer-to-int-cast  -Wno-int-to-pointer-cast -Wno-address-of-packed-member
CFLAGS_INTERNAL += -DNDEBUG -DVPN_SPEED -DUNIX -DUNIX_LINUX -D_REENTRANT -DREENTRANT -D_THREAD_SAFE -D_THREADSAFE -DTHREAD_SAFE -DTHREADSAFE -D_FILE_OFFSET_BITS=64
LIBS_INTERNAL = z readline ncurses ssl crypto


SUBDIRS_SBIN = vpnx
SUBDIRS_OBJONLY = Cedar Mayaqua

vpnx_OBJS = Cedar Mayaqua
