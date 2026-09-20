# psp-pthread

psp-pthread is the PlayStation Portable-specific maintenance fork of
pthread-embedded. It provides the POSIX threads implementation used with the
PSPDEV toolchain.

This fork targets the PSP only. Historical DSP/BIOS, PlayStation 2, and
PlayStation Vita platform ports and their build files have been removed from
the active source tree.

## Requirements

- PSPDEV and PSPSDK
- CMake 3.20 or newer

The PSPSDK installation supplies the PSP pthread OS abstraction through
`libpthreadglue`.

## Build

Configure and build with the PSPDEV CMake toolchain:

```sh
cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE="$PSPDEV/psp/share/pspdev.cmake" \
    -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

The build produces the static `pthread` library.

## Install

Install into the active PSP prefix with CMake:

```sh
cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE="$PSPDEV/psp/share/pspdev.cmake" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="$PSPDEV/psp"
cmake --build build --parallel
cmake --install build
```

The install includes:

```text
include/pthread.h
include/sched.h
include/semaphore.h
include/pte_types.h
include/bits/posix_opt.h
include/sys/_pthreadtypes.h
include/sys/sched.h
include/sys/pte_generic_osal.h
lib/libpthread.a
lib/pkgconfig/pthread.pc
```

The pkg-config metadata is relocatable and records the PSPSDK
`libpthreadglue` dependency.

## PSP test application

The existing pthread-embedded test suite can be built as a PSP application:

```sh
cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE="$PSPDEV/psp/share/pspdev.cmake" \
    -DCMAKE_BUILD_TYPE=Release \
    -DPSP_PTHREAD_BUILD_TESTS=ON
cmake --build build --parallel
```

The tests are cross-compiled for the PSP and are not executed on the build
host. The build also creates the PSP test application through PSPSDK's CMake
support.

## Source layout

- Root `*.c` files — pthread-embedded implementation
- `platform/psp/` — PSP-specific types and test application entry point
- `platform/helper/` — common TLS helper used by the PSP port
- `tests/` — pthread-embedded behavioral test suite
- `doc/` — retained general and PSP documentation

CMake is the supported build system for this PSP fork.

## License

The pthread-embedded library is licensed under the GNU Lesser General Public
License, version 2 or later. See `COPYING.LIB` and the other retained license
files for details.
