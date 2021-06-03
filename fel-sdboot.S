/*
 * Copyright (C) 2016  Bernhard Nortmann <bernhard.nortmann@web.de>
 *
 * Based on previous works
 * Copyright (C) 2016  Siarhei Siamashka <siarhei.siamashka@gmail.com>
 * Copyright (C) 2012  Henrik Nordstrom <henrik@henriknordstrom.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

/*
 * This file is a utility stub (bootloader code) to force the device into
 * FEL mode, by jumping directly to the corresponding (N-)BROM entry point.
 *
 * Build instructions:
 *   make fel-sdboot.sunxi
 *
 *   If needed, adjust CROSS_COMPILE and MKIMAGE according to your
 *   toolchain, e.g.
 *   make fel-sdboot.sunxi CROSS_COMPILE=armv7a-hardfloat-linux-gnueabi- \
 *   MKIMAGE=/usr/local/bin/mkimage
 *
 *
 * Install instructions:
 *   dd if=fel-sdboot.sunxi of=/dev/sdX bs=1024 seek=8
 */

_start:
	li	ra, 0x20
	jr	ra
