/*
 * Copyright (C) 2012  Henrik Nordstrom <henrik@henriknordstrom.net>
 * Copyright (C) 2015  Siarhei Siamashka <siarhei.siamashka@gmail.com>
 * Copyright (C) 2016  Bernhard Nortmann <bernhard.nortmann@web.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**********************************************************************
 * SoC information and retrieval of soc_sram_info
 **********************************************************************/
#include "soc_info.h"

#include <stdio.h>
#include <string.h>

/*
 * D1 seems to have no IRQ stack, and the main stack is at high address
 * (the SP in FEL mode is 0x43c2c).
 * Looks like there's nothing to keep.
 */
sram_swap_buffers d1_sram_swap_buffers[] = {
	{ .size = 0 }  /* End of the table */
};

const watchdog_info wd_d1_compat = {
	.reg_mode = 0x020500b8,
	.reg_mode_value = 1,
};

soc_info_t soc_info_table[] = {
	{
		.soc_id       = 0x1859, /* Allwinner D1 */
		.name         = "D1",
		.spl_addr     = 0x20000,
		.scratch_addr = 0x21000,
		.thunk_addr   = 0x42a00, .thunk_size = 0x200,
		.swap_buffers = d1_sram_swap_buffers,
		.sram_size    = 0X22a00,
		.sid_base     = 0x03006000,
		.sid_offset   = 0x200,
		.watchdog     = &wd_d1_compat,
	},{
		.swap_buffers = NULL /* End of the table */
	}
};

/*
 * This generic record assumes BROM with similar properties to A10/A13/A20/A31,
 * but no extra SRAM sections beyond 0x8000. It also assumes that the IRQ
 * handler stack usage never exceeds 0x400 bytes.
 *
 * The users may or may not hope that the 0x7000-0x8000 area is also unused
 * by the BROM and re-purpose it for the SPL stack.
 *
 * The size limit for the ".text + .data" sections is ~21 KiB.
 */
sram_swap_buffers generic_sram_swap_buffers[] = {
	{ .buf1 = 0x1C00, .buf2 = 0x5800, .size = 0x400 },
	{ .size = 0 }  /* End of the table */
};

soc_info_t generic_soc_info = {
	.scratch_addr = 0x1000,
	.thunk_addr   = 0x5680, .thunk_size = 0x180,
	.swap_buffers = generic_sram_swap_buffers,
};

/* functions to retrieve SoC information */

soc_info_t *get_soc_info_from_id(uint32_t soc_id)
{
	soc_info_t *soc, *result = NULL;

	for (soc = soc_info_table; soc->swap_buffers; soc++)
		if (soc->soc_id == soc_id) {
			result = soc;
			break;
		}

	if (!result) {
		printf("Warning: no 'soc_sram_info' data for your SoC (id=%04X)\n",
		       soc_id);
		result = &generic_soc_info;
	}
	return result;
}

soc_info_t *get_soc_info_from_version(struct aw_fel_version *buf)
{
	return get_soc_info_from_id(buf->soc_id);
}

void get_soc_name_from_id(soc_name_t buffer, uint32_t soc_id)
{
	soc_info_t *soc;
	for (soc = soc_info_table; soc->swap_buffers; soc++)
		if (soc->soc_id == soc_id && soc->name != NULL) {
			strncpy(buffer, soc->name, sizeof(soc_name_t) - 1);
			return;
		}

	/* unknown SoC (or name string missing), use the hexadecimal ID */
	snprintf(buffer, sizeof(soc_name_t) - 1, "0x%04X", soc_id);
}
