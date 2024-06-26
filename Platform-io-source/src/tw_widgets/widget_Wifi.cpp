#include "tw_widgets/widget_Wifi.h"
#include "bitmaps/bitmaps_general.h"
#include "fonts/RobotoMono_Light_All.h"
#include "web/webserver.h"
#include "wifi.h"

void WidgetWifi::draw(uint canvasid, uint8_t style_hint)
{
	if (WiFi.status() == WL_CONNECTED)
	{
		canvas[canvasid].fillSmoothRoundRect(pos_x, pos_y, 130, 14, 6, RGB(0x33, 0x33, 0x33));
		canvas[canvasid].setFreeFont(RobotoMono_Light[6]);
		if (web_server.is_running())
			canvas[canvasid].drawString(WiFi.localIP().toString(), pos_x + 70, pos_y + 5);
		canvas[canvasid].fillSmoothCircle(pos_x, pos_y + 23, 18, 0);
		canvas[canvasid].pushImage(pos_x - 16, pos_y + 8, 32, 32, icon_wifi_on);
		canvas[canvasid].drawSmoothArc(pos_x, pos_y + 23, 23, 19, 0, 360, col_on, 0);
	}
	else
	{
		canvas[canvasid].pushImage(pos_x - 16, pos_y + 8, 32, 32, icon_wifi_off);

		if (style_hint == 0)
		{
			canvas[canvasid].drawSmoothArc(pos_x, pos_y + 23, 23, 19, 0, 360, col_off, 0);
		}
		else
		{
			canvas[canvasid].drawSmoothRoundRect(pos_x - 23, pos_y, 5, 1, 46, 46, col_off, 0);
		}
	}
}

bool WidgetWifi::process_touch(touch_event_t touch_event)
{
	if (touch_event.type == TOUCH_TAP)
	{
		if (bounds_check(touch_event.x, touch_event.y))
		{
			if (!web_server.is_running())
				web_server.start();
			else
				web_server.stop(false);

			return true;
		}
	}

	return false;
}
