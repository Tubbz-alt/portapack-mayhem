/*
 * Copyright (C) 2014 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2016 Furrtek
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __PROC_ADSBTX_H__
#define __PROC_ADSBTX_H__

#include "baseband_processor.hpp"
#include "baseband_thread.hpp"

#define TEST_F2D(f) (uint32_t)((f) * ((1ULL << 32) / 4000000))

class ADSBTXProcessor : public BasebandProcessor {
public:
	void execute(const buffer_c8_t& buffer) override;
	
	void on_message(const Message* const p) override;

private:
	bool configured = false;
	
	BasebandThread baseband_thread { 4000000, this, NORMALPRIO + 20, baseband::Direction::Transmit };
	
	const uint16_t preamble_parts = 0b1010000101000000;
	bool preamble { }, active { };
    uint16_t bit_pos { 0 };
    uint8_t cur_bit { 0 };
	uint32_t sample { 0 };
	uint32_t tone_phase { 0 };
	uint32_t fm_delta { 0 };
	uint32_t phase { 0 }, sphase { 0 };
	int32_t tone_sample { 0 }, delta { 0 };
	int8_t re { }, im { };
	
	TXDoneMessage message { };
};

#endif
