#include "tw_faces/face_Watch_CustomBIOS.h"
#include "bitmaps/bitmaps_general.h"
#include "peripherals/battery.h"
#include "peripherals/imu.h"
#include "settings/settings.h"
#include "tinywatch.h"
#include "fonts/AcPlus_IBM_VGA_9x1612pt7b.h"
#include "fonts/AcPlus_IBM_VGA_9x1616pt7b.h"
#include "web/webserver.h"
#include "wifi.h"

void FaceWatch_CustomBIOS::setup()
{
	if (!is_setup)
	{
		is_setup = true;
	}
}

void FaceWatch_CustomBIOS::draw(bool force)
{
	if (force || millis() - next_update > update_period)
	{
		setup();

		next_update = millis();

		if (!is_dragging || !is_cached)
		{
			if (is_dragging)
				is_cached = true;

			// Clock Face Starts Here
			BIOSClockSettings biosclock;

			// Update Y centering before checking cached_trig invalidation
			if (show_toolbars)
			{
				biosclock.height = display.height - 50;
				center_y = center_y_wtoolbar;
			}
			else
			{
				biosclock.height = display.width - 50; // keep it square
				center_y = center_y_ntoolbar;
			}

			if (!cachedTrig)
			{
				cachedTrig = true;
				// init stuff
			}

			uint8_t secs = rtc.get_seconds();

			// Only fetch the mins, hrs, and date once a minute.
			// Also do it for first run (year cant be 0, or 2000)
			if (secs == 0 || year == 0 || year == 2000)
			{
				mins = rtc.get_mins();
				hours = rtc.get_hours();
				day = rtc.get_day();
				month = rtc.get_month();
				year = rtc.get_year();
				dow = rtc.get_day_of_week();
				bat_perc = (int)battery.get_percent(false);

				// Offset the Date for single/multiple digits
				if (day > 9)
					day_offset = 0;
			}

			// Blank the display
			canvas[canvasid].fillSprite(biosclock.color_background);
			canvas[canvasid].setTextColor(TFT_WHITE);
			canvas[canvasid].setTextDatum(TL_DATUM);
			canvas[canvasid].setFreeFont(&AcPlus_IBM_VGA_9x1612pt7b);

			// Title Bar
			canvas[canvasid].fillRect(0,0,240,30, TFT_SKYBLUE);
			canvas[canvasid].setTextColor(TFT_BLUE, TFT_SKYBLUE);
			canvas[canvasid].drawString("TW BIOS Utility", 45, 4);

			// Menu Bar
			canvas[canvasid].fillRect(0,30,240,25, TFT_BLUE);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
			if (BIOSmode == 0) {	// MAIN
				canvas[canvasid].fillRect(15,30,50,25, TFT_WHITE);
				canvas[canvasid].setTextColor(TFT_BLUE, TFT_WHITE);
				canvas[canvasid].drawString("MAIN", 20, 30);
				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLUE);
				canvas[canvasid].drawString("Advanced", 85, 30);
				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLUE);
				canvas[canvasid].drawString("Boot", 185, 30);

				// Create Date Buffer
				char dbuffer[15]; // Buffer for DD/MM/YYYY or MM/DD/YYYY
				sprintf(dbuffer, "%s %02d/%02d/%04d", dow.c_str(), day, month, year);
				String bios_date = String(dbuffer);
				if (settings.config.time_dateformat == true)
					sprintf(dbuffer, "%s %02d/%02d/%04d", dow.c_str(), month, day, year);
					bios_date = String(dbuffer);

				// Create Time Buffer
				char tbuffer[8]; // Buffer for HH:MM:SS_
				sprintf(tbuffer, "%02d:%02d:%02d", hours, mins, secs);
				String bios_time = String(tbuffer) + "_";
				if (cursorblink)
					bios_time = String(tbuffer);

				// Create Battery Status Buffer
				int batpc = (int)battery.get_percent(false);
				char bat_buffer[17]; 
				sprintf(bat_buffer, "Bat [      ] %02d%%", batpc);
				String bios_batt = String(bat_buffer); 
				
				// Create Battery Bar Buffer
				char battbar[7] = "      "; // 6 spaces + null terminator
				bool isVBUS = tinywatch.vbus_present();
				if (batpc == 0) {
					printf("%s", battbar);
					return;
				}		
				if (batpc == 100) {
					sprintf(battbar, isVBUS ? ">>>>>>" : "<<<<<<");
				} else {
					int bars = (batpc + 19) / 20;
					for (int i = 0; i < bars; i++) {
						battbar[i] = isVBUS ? '>' : '<';
					}
				}
				
				canvas[canvasid].setFreeFont(&AcPlus_IBM_VGA_9x1616pt7b);
				canvas[canvasid].setTextColor(biosclock.color_text, biosclock.color_background);

				// Fake Prompt
				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLACK);
				canvas[canvasid].drawString("C:\\> tw_home", 5, 60);
				canvas[canvasid].drawString(bios_batt, 5, 90);

				// Set Battery Bar Status & Colour
				uint32_t chgColour = TFT_RED;
				if (isVBUS) { chgColour = TFT_GREEN;}
				canvas[canvasid].setTextColor(chgColour, TFT_BLACK);
				canvas[canvasid].drawString(battbar, 70, 90);

				// Do Step Counter
				uint32_t currentsteps = imu.get_steps(day, month, year);

				char sbuffer[6]; // 5 Digits + terminator
					sprintf(sbuffer, "%d", currentsteps);
					String imuSteps = String(sbuffer);

				uint32_t stepsColour = TFT_YELLOW;
				if (currentsteps > 10000) {stepsColour = TFT_GREEN;}

				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLACK);
				canvas[canvasid].drawString("Steps: ", 5, 120);
				canvas[canvasid].setTextColor(stepsColour, TFT_BLACK);
				canvas[canvasid].drawString(imuSteps, 100, 120);
				
				// Draw Clock Border
				canvas[canvasid].drawRect(5, 167, 230, 80, TFT_WHITE);
				canvas[canvasid].drawRect(2, 164, 236, 86, TFT_WHITE);

				// Draw Clock
				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLACK);
				canvas[canvasid].drawString(bios_date, (display.width - (bios_date.length() * 13 )) / 2, 178);
				canvas[canvasid].drawString(bios_time , (display.width - ((bios_time.length() + cursorblink) * 13 )) / 2, 208);
			}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------
			if (BIOSmode == 1) {	// ADVANCED
				canvas[canvasid].fillRect(75,30,100,25, TFT_WHITE);

				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLUE);
				canvas[canvasid].drawString("Main", 20, 30);
				canvas[canvasid].setTextColor(TFT_BLUE, TFT_WHITE);
				canvas[canvasid].drawString("ADVANCED", 85, 30);
				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLUE);
				canvas[canvasid].drawString("Boot", 185, 30);

				// Create WiFi Status Buffer
				int wifisig = constrain(map(WiFi.RSSI(), -90, -60, 0, 9), 0, 9);
				char wifi_buffer[17]; 
				sprintf(wifi_buffer, "WiFi [         ]");
				String bios_wifisignal = String(wifi_buffer); 

				// Create Battery Bar Buffer
				char wifibar[10] = "      "; // 6 spaces + null terminator
				bool isWiFi = WiFi.isConnected();
				if (isWiFi) {
					for (int i = 0; i < wifisig; i++) {
						wifibar[i] = ')' ;
					}
				}

				// Show WiFi Bar
				canvas[canvasid].setFreeFont(&AcPlus_IBM_VGA_9x1616pt7b);
				canvas[canvasid].setTextColor(biosclock.color_text, biosclock.color_background);
				canvas[canvasid].drawString(bios_wifisignal, 5, 90);

				// Set WiFi Bar Status & Colour		
				if (isWiFi) {
					uint32_t wifiColor = TFT_RED;
					if (wifisig > 2) { wifiColor = TFT_YELLOW;}
					if (wifisig > 5) { wifiColor = TFT_GREEN;}
					canvas[canvasid].setTextColor(wifiColor, TFT_BLACK);
					canvas[canvasid].drawString(wifibar, 80, 90);
					wifi_isStarting = false;

					canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLACK);
					canvas[canvasid].drawString("IP:", 5, 120);
					canvas[canvasid].setTextColor(TFT_GREEN, TFT_BLACK);
					canvas[canvasid].drawString(WiFi.localIP().toString(), 45, 120);
					

				} else  {
					if (!wifi_isStarting)
					{
						canvas[canvasid].setTextColor(TFT_RED, TFT_BLACK);
						canvas[canvasid].drawString("WiFi Off", 90, 90);
					}
					else 
					{
						canvas[canvasid].setTextColor(TFT_ORANGE, TFT_BLACK);
						canvas[canvasid].drawString("Starting", 90, 90);						
					}
				}

			}

			// ---------------------------------------------------------------------------------------------------------------------------------------------------------

			if (BIOSmode == 2) {	// BOOT
				canvas[canvasid].fillRect(175,30,60,25, TFT_WHITE);

				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLUE);
				canvas[canvasid].drawString("Main", 20, 30);
				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLUE);
				canvas[canvasid].drawString("Advanced", 85, 30);
				canvas[canvasid].setTextColor(TFT_BLUE, TFT_WHITE);
				canvas[canvasid].drawString("BOOT", 185, 30);
				
				// Heap Info
				int percfree = constrain(map(ESP.getFreeHeap(), 0, ESP.getHeapSize(), 0, 100), 0, 100);
				char heap_buffer[17]; 
				sprintf(heap_buffer, "%d/%d (%d%%)",ESP.getFreeHeap(), ESP.getHeapSize(), percfree);
				String bios_heap = String(heap_buffer); 

				canvas[canvasid].setTextColor(TFT_WHITE, TFT_BLACK);
				canvas[canvasid].drawString("Heap Free:", (display.width - 120) / 2, 70);
				canvas[canvasid].drawString(bios_heap, (display.width - (bios_heap.length() * 12)) / 2, 100);
			}

			// Bottom Version Bar
			canvas[canvasid].setFreeFont(&AcPlus_IBM_VGA_9x1612pt7b);
			canvas[canvasid].fillRect(0,259,240,30, TFT_SKYBLUE);
			canvas[canvasid].setTextColor(TFT_BLUE, TFT_SKYBLUE);
			canvas[canvasid].drawString(tinywatch.version_firmware, 100, 259);

			// Clock Face Ends Here
			draw_children(false, 0);
			draw_navigation(canvasid);
		}

		cursorblink = !cursorblink;
		update_screen();
	}
}

bool FaceWatch_CustomBIOS::process_touch(touch_event_t touch_event)
{
	if (touch_event.type == TOUCH_TAP && touch_event.y <= 80) // Toolbar Touch
	{
		BIOSmode = touch_event.x / 80; // 3 Touch Areas of 90px width each

		// Cycle through the colour pallette, after one full cycle, switch the style (square/circle)
		show_toolbars = !show_toolbars; // Turn the toolbar on and off
		cachedTrig = false;
		draw(true);
		return true;
	} 
	else if (touch_event.type == TOUCH_TAP && touch_event.y >= 81 && touch_event.y <= 140 && BIOSmode == 1) // WiFi On/Off
	{
		if (!web_server.is_running()) {
			web_server.start();
			wifi_isStarting = true; }
		else {
			web_server.stop(false);
			wifi_isStarting = false; }
		return true;
	}

	else if (touch_event.type == TOUCH_DOUBLE)
	{
		display.cycle_clock_face();
		is_dragging = false;
		// draw(true);
		return true;
	}
	else if (touch_event.type == TOUCH_LONG)
	{
		// TODO: Add display of watch specific settings here when the user long presses
	}

	return false;
}

FaceWatch_CustomBIOS face_watch_custom_bios;