#
# build "preprocessed" .h files for inclusion of ARM scratch code
#

SPL_THUNK := fel-to-spl-thunk.h
THUNKS := clrsetbits.h readl_writel.h sid_read_root.h get_stackinfo.h memcpy.h

all: $(SPL_THUNK) $(THUNKS)
# clean up object files afterwards
	rm -f *.o

# This empty prerequisite enforces a rebuild of all the headers on every run
FORCE:

# If not specified explicitly: try to guess a suitable ARM toolchain prefix
CROSS_COMPILE ?= $(shell ../find-cross-gcc.sh riscv64)

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJDUMP := $(CROSS_COMPILE)objdump

CFLAGS := -c -march=rv64g -fno-common -fno-builtin -ffreestanding -nostdinc -fno-strict-aliasing -fno-pic
LDFLAGS := -nostdlib -T thunk.lds -static --no-relax

AWK_O_TO_H := LC_ALL=C awk -f objdump_to_h.awk

# The SPL thunk requires a different output format. The "style" variable for
# awk controls this, and causes the htole32() conversion to be omitted.
fel-to-spl-thunk.h: fel-to-spl-thunk.S FORCE
	$(CC) -o $(subst .S,.o,$<) $(CFLAGS) $<
	$(LD) -o $(subst .S,.elf,$<) $(LDFLAGS) $(subst .S,.o,$<)
	$(OBJDUMP) -d $(subst .S,.elf,$<) | $(AWK_O_TO_H) -v style=old > $@

$(THUNKS): %.h: %.S FORCE
	$(CC) -o $(subst .S,.o,$<) $(CFLAGS) $<
	$(LD) -o $(subst .S,.elf,$<) $(LDFLAGS) $(subst .S,.o,$<)
	$(OBJDUMP) -d $(subst .S,.elf,$<) | $(AWK_O_TO_H) > $@
