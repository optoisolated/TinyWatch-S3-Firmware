#pragma once

#include "tw_faces/tw_face.h"

class FaceWatch_CustomBIOS : public tw_face
{
	public:
		void setup(void);
		void draw(bool force);

		bool process_touch(touch_event_t touch_event);

	private:
		struct BIOSClockSettings
		{
				uint32_t width = display.width - 50;
				uint32_t height = display.height - 50;
				uint32_t color_background = RGB(0x00, 0x00, 0x00);		// Black
				uint32_t color_text = RGB(0xFF, 0xFF, 0xFF);			// White
				uint32_t color_title_bkg = RGB(0x92, 0xc5, 0xf9);		// Black				
		};

		const String months[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

		// Settings
		bool cursorblink = false;
		bool wifi_isStarting = false;
		uint8_t BIOSmode = 0;

		// Kept for Caching
		uint8_t hours = 0;
		uint8_t mins = 0;
		uint16_t day = 0;
		uint16_t month = 0;
		uint16_t year = 0;
		String dow = "";
		int8_t day_offset = -16;
		float bat_perc = 0.0;

		// BIOS Clock Stuff
		bool cachedTrig = false;

		// Window Positioning
		int center_x = 120;
		int center_y;
		int center_y_wtoolbar = 157; // Clock Position with Toolbar
		int center_y_ntoolbar = 137; // Clock Position without Toolbar

		float face_radius = 100;

		bool show_toolbars = true;
};

extern FaceWatch_CustomBIOS face_watch_custom_bios;
