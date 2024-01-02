
#include "tw_controls/control_Toggle.h"
#include "fonts/RobotoMono_Light_All.h"

void ControlToggle::set_data(SettingsOptionBool *sett)
{
	setting_option = sett;
	value = setting_option->get() ? option2 : option1;
}


void ControlToggle::draw(uint canvasid)
{
	adjusted_pos_x = pos_x + offset_x;
	adjusted_pos_y = pos_y + offset_y;

	canvas[canvasid].fillRoundRect(adjusted_pos_x, adjusted_pos_y, width, height, 4, RGB(0x22, 0x22, 0x22));
	canvas[canvasid].setFreeFont(RobotoMono_Light[7]);
	canvas[canvasid].setTextDatum(4); // Middle, Center
	canvas[canvasid].setTextColor(TFT_WHITE);
	canvas[canvasid].drawString(name, adjusted_pos_x + (width/2), adjusted_pos_y-10);


	if (setting_option->get())
		canvas[canvasid].fillRoundRect(adjusted_pos_x+(width/2)+2, adjusted_pos_y+2, width/2-2, height-4, 4, RGB(0x99, 0xFF, 0x99));
	else
		canvas[canvasid].fillRoundRect(adjusted_pos_x+2, adjusted_pos_y+2, width/2-2, height-4, 4, RGB(0x66, 0x66, 0x66));

	canvas[canvasid].setTextColor(TFT_WHITE, RGB(0x22, 0x22, 0x22));
	canvas[canvasid].setFreeFont(RobotoMono_Light[8]);
	canvas[canvasid].drawString(value, adjusted_pos_x + (width/2), adjusted_pos_y + (height/2) -2);
}

bool ControlToggle::drag(int16_t drag_x, int16_t drag_y)
{
	return false;
}

void ControlToggle::drag_end()
{
	
}

bool ControlToggle::click(uint16_t click_pos_x, uint16_t click_pos_y)
{
	// Did we click within the bounds of this control?
	if (bounds_check(click_pos_x, click_pos_y))
	{
		// If we have bound a SettingOption to this control, fire the change method
		if (setting_option != nullptr)
			value = setting_option->change() ? option2 : option1;
		// If we have assigned a callback on this control, fire it 
		if (callbackFunction != nullptr)
			callbackFunction();
		// Yes, we did click this control
		return true;
	}

	return false;
}

bool ControlToggle::click_double(uint16_t click_pos_x, uint16_t click_pos_y)
{
	return false;
}

bool ControlToggle::click_long(uint16_t click_pos_x, uint16_t click_pos_y)
{
	return false;
}