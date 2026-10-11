/*
 * LoadTracker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//
// USBSID-Pico output
//

#ifndef GUSBSID_H
#define GUSBSID_H

#ifdef __cplusplus
extern "C" {
#endif

#define USBSID_MAXSIDS 4

typedef void (*USBSID_FRAMEFUNC)(void);

/**
 * @brief: Open USBSID-Pico boards.
 * @param serials: comma separated board serials in SID order, NULL or empty opens every board
 * @return: 1 on success, 0 if no board with a SID could be opened
 */
int usbsid_open(const char *serials);

/**
 * @brief: Stop the frame thread, silence every SID and close the boards.
 */
void usbsid_close(void);

/**
 * @brief: Return 1 if boards are open.
 */
int usbsid_isopen(void);

/**
 * @brief: Return the number of SIDs on the open boards.
 */
int usbsid_totalsids(void);

/**
 * @brief: Set the board clock and the frame rate, not callable from framefunc.
 * @param ntsc: 0 = PAL clock, 1 = NTSC clock
 * @param framerate: player calls per second
 */
void usbsid_settiming(unsigned ntsc, unsigned framerate);

/**
 * @brief: Set the number of SIDs the song plays on, SIDs past it are silenced.
 *         Applied by the frame thread at frame start, callable from framefunc.
 * @param count: 1 to USBSID_MAXSIDS
 */
void usbsid_setsidcount(unsigned count);

/**
 * @brief: Start the frame thread, it calls framefunc once per frame paced on the wall clock.
 * @param framefunc: runs the player and calls usbsid_write() for the frame
 * @return: 1 on success
 */
int usbsid_start(USBSID_FRAMEFUNC framefunc);

/**
 * @brief: Stop the frame thread and silence every SID.
 */
void usbsid_stop(void);

/**
 * @brief: Queue a register write, call from framefunc only.
 * @param sid: song SID, 0 based
 * @param reg: SID register 0x00 to 0x18
 * @param value: register value
 * @param cycle: cycle offset from the start of the frame
 */
void usbsid_write(unsigned sid, unsigned char reg, unsigned char value, unsigned cycle);

/**
 * @brief: Restart the write timeline at the following frame, keep queued writes.
 */
void usbsid_resync(void);

/**
 * @brief: Return 1 if an open board is unplugged or no longer accepts writes.
 *         Close and open again to recover.
 */
int usbsid_lost(void);

/**
 * @brief: Write the serials of the open boards, comma separated, in SID order.
 * @param buffer: output, empty string when no board is open
 * @param size: buffer size in bytes
 * @return: number of open boards
 */
int usbsid_openserials(char *buffer, int size);

/**
 * @brief: List the attached boards without opening them.
 * @param buffer: output, comma separated serials in USB bus and port order, may be NULL
 * @param size: buffer size in bytes
 * @return: number of attached boards
 */
int usbsid_attached(char *buffer, int size);

/**
 * @brief: Return 1 if every board in serials is attached, without opening any.
 * @param serials: comma separated board serials, NULL or empty means any board
 */
int usbsid_allattached(const char *serials);

#ifdef __cplusplus
}
#endif

#endif
