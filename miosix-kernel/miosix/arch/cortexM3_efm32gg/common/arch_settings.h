/***************************************************************************
 *   Copyright (C) 2015 by Terraneo Federico                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#ifndef ARCH_SETTINGS_H
#define	ARCH_SETTINGS_H

#define ARM_MATH_CM3

#ifdef __cplusplus
namespace miosix {

/**
 * \addtogroup Settings
 * \{
 */

/// \internal Size of vector to store registers during ctx switch (9*4=36Bytes)
/// Only sp and r4-r11 are saved here, since r0-r3,r12,lr,pc,xPSR and
/// old sp are saved by hardware on the process stack on Cortex M3 CPUs.
const unsigned char CTXSAVE_SIZE=9;

/// \internal some architectures save part of the context on their stack.
/// This constant is used to increase the stack size by the size of context
/// save frame. If zero, this architecture does not save anything on stack
/// during context save. Size is in bytes, not words.
/// MUST be divisible by 4.
const unsigned int CTXSAVE_ON_STACK=32;

/// \internal stack alignment for this specific architecture
const unsigned int CTXSAVE_STACK_ALIGNMENT=8;

/**
 * \}
 */

} //namespace miosix
#endif

#endif	/* ARCH_SETTINGS_H */
