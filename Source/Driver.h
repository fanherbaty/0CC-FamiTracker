/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2014  Jonathan Liss
**
** 0CC-FamiTracker is (C) 2014-2018 HertzDevil
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.  To obtain a
** copy of the GNU Library General Public License, write to the Free
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/


#pragma once

#include <iterator>		// // // std::size

//
// The NSF driver binaries
//

// Change this for new versions
const char DRIVER_ID[] = "NSF-driver v2.11";

#pragma warning( disable : 4309 ) // disable warning 4309: 'initializing' : truncation of constant value
#pragma warning( disable : 4838 ) // 4838: conversion from 'int' to 'const char' requires a narrowing conversion

// NES program for running a NSF
const char NSF_CALLER_BIN[] = {
	0x78,0xD8,0xAD,0x02,0x20,0x10,0xFB,0xAD,0x02,0x20,0x10,0xFB,0xA2,0x00,0x8A,0x9D,
	0x00,0x02,0xE8,0xD0,0xFA,0xA9,0x0F,0x8D,0x15,0x40,0xA9,0x0A,0x8D,0x10,0x40,0xA9,
	0x00,0xA2,0x00,0xA0,0x00,0x20,0x08,0x80,0xA9,0x80,0x8D,0x00,0x20,0xA9,0x00,0x8D,
	0x01,0x20,0x4C,0xB2,0xFF,0x20,0x0B,0x80,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB5,0xFF,0x80,0xFF,0xB8,0xFF,
};

const char NSF_CALLER_BIN_VRC6[] = {
	0x78,0xD8,0xAD,0x02,0x20,0x10,0xFB,0xAD,0x02,0x20,0x10,0xFB,0xA2,0x00,0x8A,0x9D,
	0x00,0x02,0xE8,0xD0,0xFA,0xA9,0x00,0x8D,0x00,0x80,0xA9,0x02,0x8D,0x00,0xC0,0xA9,
	0x0F,0x8D,0x15,0x40,0xA9,0x0A,0x8D,0x10,0x40,0xA9,0x00,0xA2,0x00,0xA0,0x00,0x20,
	0x00,0x80,0xA9,0x80,0x8D,0x00,0x20,0xA9,0x00,0x8D,0x01,0x20,0x4C,0xBC,0xFF,0x20,
	0x03,0x80,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xFF,0x80,0xFF,0xC2,0xFF,
};

const unsigned short NSF_CALLER_SIZE = std::size(NSF_CALLER_BIN);	// bytes

#include "DetuneTable.h"		// // //
//
// The driver binaries
//
// created with a binary->c-array program
//
#include "drivers/drv_2a03.h"
#include "drivers/drv_vrc6.h"
#include "drivers/drv_vrc7.h"
#include "drivers/drv_mmc5.h"
#include "drivers/drv_fds.h"
#include "drivers/drv_n163.h"
#include "drivers/drv_s5b.h"		// // //
#include "drivers/drv_all.h"		// // //

struct driver_t {
	const unsigned char *driver;
	const unsigned int driver_size;
	const int *word_reloc;
	const size_t word_reloc_size;
	const int *freq_table;		// // //
	const size_t freq_table_size;	// // //
	const int *adr_reloc;		// // //
	const size_t adr_reloc_size;	// // //
};

const driver_t DRIVER_PACK_2A03 = {
	DRIVER_2A03,
	std::size(DRIVER_2A03),
	DRIVER_RELOC_WORD_2A03,
	std::size(DRIVER_RELOC_WORD_2A03),
	DRIVER_FREQ_TABLE_2A03,				// // //
	std::size(DRIVER_FREQ_TABLE_2A03),
	DRIVER_RELOC_ADR_2A03,
	std::size(DRIVER_RELOC_ADR_2A03),
};

const driver_t DRIVER_PACK_VRC6 = {
	DRIVER_VRC6,
	std::size(DRIVER_VRC6),
	DRIVER_RELOC_WORD_VRC6,
	std::size(DRIVER_RELOC_WORD_VRC6),
	DRIVER_FREQ_TABLE_VRC6,				// // //
	std::size(DRIVER_FREQ_TABLE_VRC6),
	DRIVER_RELOC_ADR_VRC6,
	std::size(DRIVER_RELOC_ADR_VRC6),
};

const driver_t DRIVER_PACK_VRC7 = {
	DRIVER_VRC7,
	std::size(DRIVER_VRC7),
	DRIVER_RELOC_WORD_VRC7,
	std::size(DRIVER_RELOC_WORD_VRC7),
	DRIVER_FREQ_TABLE_VRC7,				// // //
	std::size(DRIVER_FREQ_TABLE_VRC7),
	DRIVER_RELOC_ADR_VRC7,
	std::size(DRIVER_RELOC_ADR_VRC7),
};

const driver_t DRIVER_PACK_MMC5 = {
	DRIVER_MMC5,
	std::size(DRIVER_MMC5),
	DRIVER_RELOC_WORD_MMC5,
	std::size(DRIVER_RELOC_WORD_MMC5),
	DRIVER_FREQ_TABLE_MMC5,				// // //
	std::size(DRIVER_FREQ_TABLE_MMC5),
	DRIVER_RELOC_ADR_MMC5,
	std::size(DRIVER_RELOC_ADR_MMC5),
};

const driver_t DRIVER_PACK_FDS = {
	DRIVER_FDS,
	std::size(DRIVER_FDS),
	DRIVER_RELOC_WORD_FDS,
	std::size(DRIVER_RELOC_WORD_FDS),
	DRIVER_FREQ_TABLE_FDS,				// // //
	std::size(DRIVER_FREQ_TABLE_FDS),
	DRIVER_RELOC_ADR_FDS,
	std::size(DRIVER_RELOC_ADR_FDS),
};

const driver_t DRIVER_PACK_N163 = {
	DRIVER_N163,
	std::size(DRIVER_N163),
	DRIVER_RELOC_WORD_N163,
	std::size(DRIVER_RELOC_WORD_N163),
	DRIVER_FREQ_TABLE_N163,				// // //
	std::size(DRIVER_FREQ_TABLE_N163),
	DRIVER_RELOC_ADR_N163,
	std::size(DRIVER_RELOC_ADR_N163),
};

const driver_t DRIVER_PACK_S5B = {		// // //
	DRIVER_S5B,
	std::size(DRIVER_S5B),
	DRIVER_RELOC_WORD_S5B,
	std::size(DRIVER_RELOC_WORD_S5B),
	DRIVER_FREQ_TABLE_S5B,				// // //
	std::size(DRIVER_FREQ_TABLE_S5B),
	DRIVER_RELOC_ADR_S5B,
	std::size(DRIVER_RELOC_ADR_S5B),
};

const driver_t DRIVER_PACK_ALL = {		// // //
	DRIVER_ALL,
	std::size(DRIVER_ALL),
	DRIVER_RELOC_WORD_ALL,
	std::size(DRIVER_RELOC_WORD_ALL),
	DRIVER_FREQ_TABLE_ALL,				// // //
	std::size(DRIVER_FREQ_TABLE_ALL),
	DRIVER_RELOC_ADR_ALL,
	std::size(DRIVER_RELOC_ADR_ALL),
};
