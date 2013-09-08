/* Linux driver for Philips webcam
   (C) 2004-2006 Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modified) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/* This tables contains entries for the 730/740/750 (Kiara) camera, with
   4 different qualities (no compression, low, medium, high).
   It lists the bandwidth requirements for said mode by its alternate interface
   number. An alternate of 0 means that the mode is unavailable.

   There are 6 * 4 * 4 entries:
     6 different resolutions subqcif, qsif, qcif, sif, cif, vga
     6 framerates: 5, 10, 15, 20, 25, 30
     4 compression modi: none, low, medium, high

   When an uncompressed mode is not available, the next available compressed mode
   will be chosen (unless the decompressor is absent). Sometimes there are only
   1 or 2 compressed modes available; in that case entries are duplicated.
*/


#include "pwc-kiara.h"
<<<<<<< HEAD
=======
#include "pwc-uncompress.h"
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

const unsigned int Kiara_fps_vector[PWC_FPS_MAX_KIARA] = { 5, 10, 15, 20, 25, 30 };

const struct Kiara_table_entry Kiara_table[PSZ_MAX][6][4] =
{
   /* SQCIF */
   {
      /* 5 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 10 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 15 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 20 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 25 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 30 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
   },
   /* QSIF */
   {
      /* 5 fps */
      {
	 {1, 146,    0, {0x1D, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x92, 0x00, 0x80}},
	 {1, 146,    0, {0x1D, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x92, 0x00, 0x80}},
	 {1, 146,    0, {0x1D, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x92, 0x00, 0x80}},
	 {1, 146,    0, {0x1D, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x92, 0x00, 0x80}},
      },
      /* 10 fps */
      {
	 {2, 291,    0, {0x1C, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x23, 0x01, 0x80}},
	 {1, 192,  630, {0x14, 0xF4, 0x30, 0x13, 0xA9, 0x12, 0xE1, 0x17, 0x08, 0xC0, 0x00, 0x80}},
	 {1, 192,  630, {0x14, 0xF4, 0x30, 0x13, 0xA9, 0x12, 0xE1, 0x17, 0x08, 0xC0, 0x00, 0x80}},
	 {1, 192,  630, {0x14, 0xF4, 0x30, 0x13, 0xA9, 0x12, 0xE1, 0x17, 0x08, 0xC0, 0x00, 0x80}},
      },
      /* 15 fps */
      {
	 {3, 437,    0, {0x1B, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xB5, 0x01, 0x80}},
	 {2, 292,  640, {0x13, 0xF4, 0x30, 0x13, 0xF7, 0x13, 0x2F, 0x13, 0x20, 0x24, 0x01, 0x80}},
	 {2, 292,  640, {0x13, 0xF4, 0x30, 0x13, 0xF7, 0x13, 0x2F, 0x13, 0x20, 0x24, 0x01, 0x80}},
	 {1, 192,  420, {0x13, 0xF4, 0x30, 0x0D, 0x1B, 0x0C, 0x53, 0x1E, 0x18, 0xC0, 0x00, 0x80}},
      },
      /* 20 fps */
      {
	 {4, 589,    0, {0x1A, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x4D, 0x02, 0x80}},
	 {3, 448,  730, {0x12, 0xF4, 0x30, 0x16, 0xC9, 0x16, 0x01, 0x0E, 0x18, 0xC0, 0x01, 0x80}},
	 {2, 292,  476, {0x12, 0xF4, 0x30, 0x0E, 0xD8, 0x0E, 0x10, 0x19, 0x18, 0x24, 0x01, 0x80}},
	 {1, 192,  312, {0x12, 0xF4, 0x50, 0x09, 0xB3, 0x08, 0xEB, 0x1E, 0x18, 0xC0, 0x00, 0x80}},
      },
      /* 25 fps */
      {
	 {5, 703,    0, {0x19, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xBF, 0x02, 0x80}},
	 {3, 447,  610, {0x11, 0xF4, 0x30, 0x13, 0x0B, 0x12, 0x43, 0x14, 0x28, 0xBF, 0x01, 0x80}},
	 {2, 292,  398, {0x11, 0xF4, 0x50, 0x0C, 0x6C, 0x0B, 0xA4, 0x1E, 0x28, 0x24, 0x01, 0x80}},
	 {1, 193,  262, {0x11, 0xF4, 0x50, 0x08, 0x23, 0x07, 0x5B, 0x1E, 0x28, 0xC1, 0x00, 0x80}},
      },
      /* 30 fps */
      {
	 {8, 874,    0, {0x18, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x6A, 0x03, 0x80}},
	 {5, 704,  730, {0x10, 0xF4, 0x30, 0x16, 0xC9, 0x16, 0x01, 0x0E, 0x28, 0xC0, 0x02, 0x80}},
	 {3, 448,  492, {0x10, 0xF4, 0x30, 0x0F, 0x5D, 0x0E, 0x95, 0x15, 0x28, 0xC0, 0x01, 0x80}},
	 {2, 292,  320, {0x10, 0xF4, 0x50, 0x09, 0xFB, 0x09, 0x33, 0x1E, 0x28, 0x24, 0x01, 0x80}},
      },
   },
   /* QCIF */
   {
      /* 5 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 10 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 15 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 20 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 25 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 30 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
   },
   /* SIF */
   {
      /* 5 fps */
      {
	 {4, 582,    0, {0x0D, 0xF4, 0x30, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x46, 0x02, 0x80}},
	 {3, 387, 1276, {0x05, 0xF4, 0x30, 0x27, 0xD8, 0x26, 0x48, 0x03, 0x10, 0x83, 0x01, 0x80}},
	 {2, 291,  960, {0x05, 0xF4, 0x30, 0x1D, 0xF2, 0x1C, 0x62, 0x04, 0x10, 0x23, 0x01, 0x80}},
	 {1, 191,  630, {0x05, 0xF4, 0x50, 0x13, 0xA9, 0x12, 0x19, 0x05, 0x18, 0xBF, 0x00, 0x80}},
      },
      /* 10 fps */
      {
	 {0, },
	 {6, 775, 1278, {0x04, 0xF4, 0x30, 0x27, 0xE8, 0x26, 0x58, 0x05, 0x30, 0x07, 0x03, 0x80}},
	 {3, 447,  736, {0x04, 0xF4, 0x30, 0x16, 0xFB, 0x15, 0x6B, 0x05, 0x28, 0xBF, 0x01, 0x80}},
	 {2, 292,  480, {0x04, 0xF4, 0x70, 0x0E, 0xF9, 0x0D, 0x69, 0x09, 0x28, 0x24, 0x01, 0x80}},
      },
      /* 15 fps */
      {
	 {0, },
	 {9, 955, 1050, {0x03, 0xF4, 0x30, 0x20, 0xCF, 0x1F, 0x3F, 0x06, 0x48, 0xBB, 0x03, 0x80}},
	 {4, 592,  650, {0x03, 0xF4, 0x30, 0x14, 0x44, 0x12, 0xB4, 0x08, 0x30, 0x50, 0x02, 0x80}},
	 {3, 448,  492, {0x03, 0xF4, 0x50, 0x0F, 0x52, 0x0D, 0xC2, 0x09, 0x38, 0xC0, 0x01, 0x80}},
      },
      /* 20 fps */
      {
	 {0, },
	 {9, 958,  782, {0x02, 0xF4, 0x30, 0x18, 0x6A, 0x16, 0xDA, 0x0B, 0x58, 0xBE, 0x03, 0x80}},
	 {5, 703,  574, {0x02, 0xF4, 0x50, 0x11, 0xE7, 0x10, 0x57, 0x0B, 0x40, 0xBF, 0x02, 0x80}},
	 {3, 446,  364, {0x02, 0xF4, 0x90, 0x0B, 0x5C, 0x09, 0xCC, 0x0E, 0x38, 0xBE, 0x01, 0x80}},
      },
      /* 25 fps */
      {
	 {0, },
	 {9, 958,  654, {0x01, 0xF4, 0x30, 0x14, 0x66, 0x12, 0xD6, 0x0B, 0x50, 0xBE, 0x03, 0x80}},
	 {6, 776,  530, {0x01, 0xF4, 0x50, 0x10, 0x8C, 0x0E, 0xFC, 0x0C, 0x48, 0x08, 0x03, 0x80}},
	 {4, 592,  404, {0x01, 0xF4, 0x70, 0x0C, 0x96, 0x0B, 0x06, 0x0B, 0x48, 0x50, 0x02, 0x80}},
      },
      /* 30 fps */
      {
	 {0, },
	 {9, 957,  526, {0x00, 0xF4, 0x50, 0x10, 0x68, 0x0E, 0xD8, 0x0D, 0x58, 0xBD, 0x03, 0x80}},
	 {6, 775,  426, {0x00, 0xF4, 0x70, 0x0D, 0x48, 0x0B, 0xB8, 0x0F, 0x50, 0x07, 0x03, 0x80}},
	 {4, 590,  324, {0x00, 0x7A, 0x88, 0x0A, 0x1C, 0x08, 0xB4, 0x0E, 0x50, 0x4E, 0x02, 0x80}},
      },
   },
   /* CIF */
   {
      /* 5 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 10 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 15 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 20 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 25 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 30 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
   },
   /* VGA */
   {
      /* 5 fps */
      {
	 {0, },
	 {6, 773, 1272, {0x25, 0xF4, 0x30, 0x27, 0xB6, 0x24, 0x96, 0x02, 0x30, 0x05, 0x03, 0x80}},
	 {4, 592,  976, {0x25, 0xF4, 0x50, 0x1E, 0x78, 0x1B, 0x58, 0x03, 0x30, 0x50, 0x02, 0x80}},
	 {3, 448,  738, {0x25, 0xF4, 0x90, 0x17, 0x0C, 0x13, 0xEC, 0x04, 0x30, 0xC0, 0x01, 0x80}},
      },
      /* 10 fps */
      {
	 {0, },
	 {9, 956,  788, {0x24, 0xF4, 0x70, 0x18, 0x9C, 0x15, 0x7C, 0x03, 0x48, 0xBC, 0x03, 0x80}},
	 {6, 776,  640, {0x24, 0xF4, 0xB0, 0x13, 0xFC, 0x11, 0x2C, 0x04, 0x48, 0x08, 0x03, 0x80}},
	 {4, 592,  488, {0x24, 0x7A, 0xE8, 0x0F, 0x3C, 0x0C, 0x6C, 0x06, 0x48, 0x50, 0x02, 0x80}},
      },
      /* 15 fps */
      {
	 {0, },
	 {9, 957,  526, {0x23, 0x7A, 0xE8, 0x10, 0x68, 0x0D, 0x98, 0x06, 0x58, 0xBD, 0x03, 0x80}},
	 {9, 957,  526, {0x23, 0x7A, 0xE8, 0x10, 0x68, 0x0D, 0x98, 0x06, 0x58, 0xBD, 0x03, 0x80}},
	 {8, 895,  492, {0x23, 0x7A, 0xE8, 0x0F, 0x5D, 0x0C, 0x8D, 0x06, 0x58, 0x7F, 0x03, 0x80}},
      },
      /* 20 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 25 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
      /* 30 fps */
      {
	 {0, },
	 {0, },
	 {0, },
	 {0, },
      },
   },
};


/*
 * Rom table for kiara chips
 *
 * 32 roms tables (one for each resolution ?)
 *  2 tables per roms (one for each passes) (Y, and U&V)
 * 128 bytes per passes
 */

const unsigned int KiaraRomTable [8][2][16][8] =
{
 { /* version 0 */
  { /* version 0, passes 0 */
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000001,0x00000001},
   {0x00000000,0x00000000,0x00000009,0x00000009,
    0x00000009,0x00000009,0x00000009,0x00000009},
   {0x00000000,0x00000000,0x00000009,0x00000049,
    0x00000049,0x00000049,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000249,0x0000024a,0x00000049},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000249,0x00000249,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00000049,0x00000249,
    0x00000249,0x0000124a,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00000049,0x00000249,
    0x0000124a,0x00009252,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00009252,0x00009292,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x00009292,0x00009292,0x00009493,0x000124db},
   {0x00000000,0x00000000,0x00000249,0x0000924a,
    0x00009492,0x0000a49b,0x0000a49b,0x000124db},
   {0x00000000,0x00000000,0x00001249,0x00009252,
    0x0000a493,0x000124db,0x000124db,0x000126dc},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x000124db,0x000126dc,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000124db,0x000136e4,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x0001b724,0x0001b92d,0x0001b925},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000136e4,0x0001b925,0x0001c96e,0x0001c92d},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 0, passes 1 */
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000},
   {0x00000000,0x00000000,0x00000001,0x00000009,
    0x00000009,0x00000009,0x00000009,0x00000001},
   {0x00000000,0x00000000,0x00000009,0x00000009,
    0x00000049,0x00000049,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000049,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000249,0x00000249,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00000049,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x00001252},
   {0x00000000,0x00000000,0x00000049,0x00001249,
    0x0000124a,0x0000124a,0x00001252,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x00009252,0x00009252,0x00009292,0x00009493},
   {0x00000000,0x00000000,0x00000249,0x0000924a,
    0x00009292,0x00009292,0x00009292,0x00009493},
   {0x00000000,0x00000000,0x00000249,0x00009292,
    0x00009492,0x00009493,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x0000a493,0x000124db,0x000126dc,0x000126dc},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000126dc,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x00009252,0x00009493,
    0x000126dc,0x000126dc,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000136e4,0x000136e4,0x0001b725,0x0001b724},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 1 */
  { /* version 1, passes 0 */
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000001},
   {0x00000000,0x00000000,0x00000009,0x00000009,
    0x00000009,0x00000009,0x00000009,0x00000009},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000049,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000249,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00000049,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x00001252},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x0000124a,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x0000124a,0x0000124a,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x0000124a,0x00009252,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x00009252,0x00009292,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x00009252,0x00009292,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x00000249,0x0000924a,
    0x00009252,0x00009493,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x00000249,0x0000924a,
    0x00009292,0x00009493,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x00000249,0x00009252,
    0x00009492,0x00009493,0x0000a49b,0x0000a49b},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x000124db,0x000124db,0x000124db},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000126dc,0x000126dc,0x000126dc},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 1, passes 1 */
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000},
   {0x00000000,0x00000000,0x00000049,0x00000009,
    0x00000049,0x00000009,0x00000001,0x00000000},
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000049,0x00000049,0x00000000},
   {0x00000000,0x00000000,0x00000249,0x00000049,
    0x00000249,0x00000049,0x0000024a,0x00000001},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x00000001},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x00000001},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x00000009},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x0000124a,0x0000124a,0x0000024a,0x00000009},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x0000124a,0x0000124a,0x0000024a,0x00000009},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x00009252,0x00001252,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x00009292,0x00001252,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x00009292,0x00001252,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00001252,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009292,0x00009292,0x00001252,0x0000024a},
   {0x00000000,0x00000000,0x0000924a,0x0000924a,
    0x00009492,0x00009493,0x00009292,0x00001252},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 2 */
  { /* version 2, passes 0 */
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000049,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x0000124a,0x00001252,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x0000124a,0x00009252,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x0000124a,0x00009292,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x00000249,0x00001249,
    0x00009252,0x00009493,0x00009493,0x0000a49b},
   {0x00000000,0x00000000,0x00000249,0x0000924a,
    0x00009292,0x00009493,0x0000a49b,0x0000a49b},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009292,0x00009493,0x0000a49b,0x000124db},
   {0x00000000,0x00000000,0x00001249,0x00009252,
    0x00009492,0x0000a49b,0x0000a49b,0x000124db},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x000124db,0x000124db,0x000126dc},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x0000a493,0x000124db,0x000126dc,0x000126dc},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x000136e4},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000126dc,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0001249b,0x000126dc,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000124db,0x000136e4,0x000136e4,0x0001b724},
   {0x00000000,0x00000000,0x00009252,0x000124db,
    0x000126dc,0x0001b724,0x0001b725,0x0001b925},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 2, passes 1 */
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000049,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00000249,
    0x0000124a,0x0000124a,0x00001252,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x0000124a,0x00009292,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00009292,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x0000a49b,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009292,0x00009493,0x0000a49b,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009292,0x00009493,0x0000a49b,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009492,0x0000a49b,0x0000a49b,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00009252,
    0x00009492,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x0000a49b,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000124db,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x00009252,0x0000a49b,
    0x0001249b,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 3 */
  { /* version 3, passes 0 */
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x0000124a,0x0000124a,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009292,0x00009493,0x0000a49b,0x0000a49b},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009492,0x0000a49b,0x0000a49b,0x000124db},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x000124db,0x000126dc,0x000126dc},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x000126dc},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000126dc,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000126dc,0x000136e4,0x0001b724},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0001249b,0x000126dc,0x000136e4,0x0001b724},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000126dc,0x000136e4,0x0001b724},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000136e4,0x0001b725,0x0001b724},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000124db,0x000136e4,0x0001b725,0x0001b925},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x000136e4,0x0001b92d,0x0001b925},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x0001b724,0x0001b92d,0x0001c92d},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000126dc,0x0001b724,0x0001c96e,0x0001c92d},
   {0x00000000,0x00000000,0x0000a492,0x000126db,
    0x000136e4,0x0001b925,0x00025bb6,0x00024b77},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 3, passes 1 */
   {0x00000000,0x00000000,0x00001249,0x00000249,
    0x0000124a,0x0000124a,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00009292,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009492,0x00009493,0x0000a49b,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00009252,
    0x00009492,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x0000a49b,0x000126dc,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x0000a49b,0x000126dc,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x0000a49b,0x000126dc,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x000124db,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000126dc,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000124db,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x00009492,0x0000a49b,
    0x000136e4,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x0000a492,0x000124db,
    0x0001b724,0x0001b724,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 4 */
  { /* version 4, passes 0 */
   {0x00000000,0x00000000,0x00000049,0x00000049,
    0x00000049,0x00000049,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00000249,0x00000049,
    0x00000249,0x00000249,0x0000024a,0x00000049},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x0000124a,0x00009252,0x00001252,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00009493,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009292,0x00009493,0x00009493,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000124db,0x000124db,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0001249b,0x000126dc,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x00009252,0x00009493,
    0x000124db,0x000136e4,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00009252,0x0000a49b,
    0x000124db,0x000136e4,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x000136e4,0x000136e4,0x000136e4},
   {0x00000000,0x00000000,0x00009492,0x0000a49b,
    0x000126dc,0x0001b724,0x0001b725,0x0001b724},
   {0x00000000,0x00000000,0x0000a492,0x000124db,
    0x000136e4,0x0001b925,0x0001b92d,0x0001b925},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 4, passes 1 */
   {0x00000000,0x00000000,0x00000249,0x00000049,
    0x00000009,0x00000009,0x00000009,0x00000009},
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000049,0x00000049,0x00000009,0x00000009},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x00000249,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x0000124a,0x00000049,0x00000049},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x0000124a,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009252,0x0000124a,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x00009252,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x00009292,0x00009292,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x00009292,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x00009493,0x00009493,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000124db,0x0000a49b,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000136e4,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00009252,0x000124db,
    0x0001b724,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 5 */
  { /* version 5, passes 0 */
   {0x00000000,0x00000000,0x00000249,0x00000249,
    0x00000249,0x00000249,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00009292,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009492,0x0000a49b,0x0000a49b,0x00009292},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x0000a49b,0x000124db,0x00009493},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000126dc,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000126dc,0x000136e4,0x000124db},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000126dc,0x000136e4,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x000136e4,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x0001b724,0x0001b725,0x000136e4},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000136e4,0x0001b724,0x0001b92d,0x0001b724},
   {0x00000000,0x00000000,0x00009492,0x0000a49b,
    0x000136e4,0x0001b724,0x0001b92d,0x0001b724},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000136e4,0x0001b925,0x0001c96e,0x0001b925},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x0001b724,0x0001b925,0x0001c96e,0x0001c92d},
   {0x00000000,0x00000000,0x0000a492,0x000126db,
    0x0001c924,0x0002496d,0x00025bb6,0x00024b77},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 5, passes 1 */
   {0x00000000,0x00000000,0x00001249,0x00000249,
    0x00000249,0x00000249,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x0000124a,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x0000924a,
    0x00009252,0x00009252,0x0000024a,0x0000024a},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x0000a49b,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x0000a49b,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x0000a49b,0x00009292,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009493,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000124db,0x00009493,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000124db,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000124db,0x000124db,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000126dc,0x000126dc,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000136e4,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00009292,0x000124db,
    0x000136e4,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00009492,0x000126db,
    0x0001b724,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 6 */
  { /* version 6, passes 0 */
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x0000a493,0x0000a49b,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000124db,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x000126dc,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000126dc,0x000136e4,0x000124db},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000126dc,0x000136e4,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000126dc,0x0001b724,0x0001b725,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000136e4,0x0001b724,0x0001b92d,0x000136e4},
   {0x00000000,0x00000000,0x00009492,0x0000a49b,
    0x000136e4,0x0001b724,0x0001b92d,0x0001b724},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000136e4,0x0001b724,0x0001b92d,0x0001b724},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000136e4,0x0001b925,0x0001b92d,0x0001b925},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x0001b724,0x0001b925,0x0001c96e,0x0001c92d},
   {0x00000000,0x00000000,0x0000a492,0x000124db,
    0x0001b724,0x0001c92d,0x0001c96e,0x0001c92d},
   {0x00000000,0x00000000,0x0000a492,0x000124db,
    0x0001b724,0x0001c92d,0x00024b76,0x0002496e},
   {0x00000000,0x00000000,0x00012492,0x000126db,
    0x0001c924,0x00024b6d,0x0002ddb6,0x00025bbf},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 6, passes 1 */
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x0000124a,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x00001249,0x00009292,
    0x00009492,0x00009252,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x0000a493,0x00009292,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x0000a49b,0x00009493,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000124db,0x000124db,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000124db,0x000124db,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000126dc,0x000124db,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000126dc,0x000126dc,0x0000a49b,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000136e4,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00009492,0x000126db,
    0x000136e4,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00009492,0x000126db,
    0x0001b724,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x00009492,0x000126db,
    0x0001b724,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x0000a492,0x000136db,
    0x0001c924,0x0001b724,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 },
 { /* version 7 */
  { /* version 7, passes 0 */
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x00009252,0x00009292,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x00001249,0x00009493,
    0x0000a493,0x000124db,0x000126dc,0x00009493},
   {0x00000000,0x00000000,0x00001249,0x0000a49b,
    0x0001249b,0x000126dc,0x000126dc,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0001249b,0x000126dc,0x000136e4,0x0000a49b},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000126dc,0x000136e4,0x0001b725,0x000124db},
   {0x00000000,0x00000000,0x00009292,0x0000a49b,
    0x000136e4,0x0001b724,0x0001b725,0x000126dc},
   {0x00000000,0x00000000,0x00009292,0x000124db,
    0x000136e4,0x0001b724,0x0001b725,0x000126dc},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000136e4,0x0001b724,0x0001c96e,0x000136e4},
   {0x00000000,0x00000000,0x00009492,0x000124db,
    0x000136e4,0x0001c92d,0x0001c96e,0x0001b724},
   {0x00000000,0x00000000,0x0000a492,0x000124db,
    0x000136e4,0x0001c92d,0x0001c96e,0x0001b724},
   {0x00000000,0x00000000,0x0000a492,0x000124db,
    0x0001b724,0x0001c92d,0x0001c96e,0x0001b925},
   {0x00000000,0x00000000,0x0000a492,0x000126db,
    0x0001b724,0x0001c92d,0x00024b76,0x0001c92d},
   {0x00000000,0x00000000,0x0000a492,0x000126db,
    0x0001b924,0x0001c92d,0x00024b76,0x0001c92d},
   {0x00000000,0x00000000,0x0000a492,0x000126db,
    0x0001b924,0x0001c92d,0x00024b76,0x0002496e},
   {0x00000000,0x00000000,0x00012492,0x000136db,
    0x00024924,0x00024b6d,0x0002ddb6,0x00025bbf},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  },
  { /* version 7, passes 1 */
   {0x00000000,0x00000000,0x00001249,0x00001249,
    0x0000124a,0x0000124a,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x00009493,
    0x00009492,0x00009292,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00001252,0x00001252},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x0000a493,0x0000a49b,0x00009292,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x0000a49b,
    0x000126dc,0x0000a49b,0x00009493,0x00009292},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000126dc,0x000124db,0x00009493,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000124db,
    0x000136e4,0x000124db,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000136db,
    0x0001b724,0x000124db,0x0000a49b,0x00009493},
   {0x00000000,0x00000000,0x0000924a,0x000136db,
    0x0001b724,0x000126dc,0x0000a49b,0x0000a49b},
   {0x00000000,0x00000000,0x00009292,0x000136db,
    0x0001b724,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x00009492,0x000136db,
    0x0001b724,0x000126dc,0x000124db,0x0000a49b},
   {0x00000000,0x00000000,0x0000a492,0x000136db,
    0x0001b724,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x0000a492,0x000136db,
    0x0001b724,0x000136e4,0x000126dc,0x000124db},
   {0x00000000,0x00000000,0x00012492,0x0001b6db,
    0x0001c924,0x0001b724,0x000136e4,0x000126dc},
   {0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000}
  }
 }
};

