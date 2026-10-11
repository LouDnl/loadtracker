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

#ifndef SOUND_H
#define SOUND_H

#define DEFAULTMIXRATE 48000

struct Settings;

bool sound_init(bool writer, const Settings &cfg);
void sound_uninit();

// USBSID-Pico board events reported by sound_usbsidpoll()
enum UsbsidEvent
{
  USBSID_EVENT_NONE,
  USBSID_EVENT_LOST,
  USBSID_EVENT_RECONNECTED
};

/**
 * @brief: Check the USBSID-Pico boards, call from the main thread.
 *         Close lost boards, reopen them once every one is attached again.
 *         Call sound_init() on an event to switch the output.
 * @return: UsbsidEvent
 */
int sound_usbsidpoll();

/**
 * @brief: Close and reopen the USBSID-Pico boards from the settings.
 *         Play on reSIDfp and wait for the boards if none opens.
 * @param writer: write sound output to a file
 * @param cfg: settings
 * @return: true if USBSID-Pico plays
 */
bool sound_usbsidreconnect(bool writer, const Settings &cfg);

/**
 * @brief: Return true while reSIDfp plays in place of lost USBSID-Pico boards.
 */
bool sound_usbsidlost();

#endif
