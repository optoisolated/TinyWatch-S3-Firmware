#pragma once

const char index_settings_widgets_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html data-bs-theme="%THEME%">
	<head>
		<title>TinyWATCH S3 | Web Settings | Widgets</title>
		%META%
	</head>
	<body>
		<div class="content" style="margin-top:12px;">
			<h2 class="center">TinyWATCH S3 | Web Settings | Widgets</h2>

			<div class="content" style="margin:30px;">
				<div class="row">
					<div class='col-3'>&nbsp;</div>
					<div class='col-2 center'><a href='/index.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>WATCH</button></a></div>
					<div class='col-2 center'><button class='btn btn-sm btn-primary' style='width:130px;'>WIDGETS</button></div>
					<div class='col-2 center'><a href='/web_settings_apps.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>APPS</button></a></div>
					<div class='col-3'>&nbsp;</div>
				</div>
			</div>

			<div class="content">

				%WIDGET_OPTIONS%

			</div>

		%FOOTER%

)rawliteral";

/*
				<div hx-get="/widgets_form_ow" hx-trigger="load">
				</div>
*/

const char index_settings_widgets_form_ow[] PROGMEM = R"rawliteral(

	<form hx-post="/update_widget_ow" hx-swap="innerHTML settle:1s" hx-target="#widget_ow_form_result">

		<div class="container">

			<span class="settings_heading">Open Weather</span>
			<div class="settings_frame" style="margin-bottom:5px; padding-bottom:5px;">

				<div class="row">
					<div class="col-6">

						<div class="input-group input-group-sm mb-1">
							<span class="input-group-text" id="inputGroup-sizing-sm">Enabled</span>
							<select class="form-select form-select-sm" id="_set_widget_ow_enable" name="_set_widget_ow_enable"  onchange="set_input_states();">
								<option value="1" %SET_WID_OW_ENABLE_YES%>YES</option>
								<option value="0" %SET_WID_OW_ENABLE_NO%>NO</option>
							</select>
						</div>
						
					</div>
					<div class="col-6">

						<div class="input-group input-group-sm mb-1">
							<span class="input-group-text" id="inputGroup-sizing-sm">API KEY</span>
							<input type="text" class="form-control form-control-sm" name="_set_widget_ow_api_key" id="_set_widget_ow_api_key" value="%SET_WID_OW_API_KEY%" required onchange="" />
						</div>

					</div>
				</div>
				<div class="row">

					<div class="col-6">

						<div class="input-group input-group-sm mb-1 flex-nowrap">
							<span class="input-group-text" id="inputGroup-sizing-sm">Poll Frequency</span>
							<input type="number" class="form-control form-control-sm" name="_set_widget_ow_poll_frequency" id="_set_widget_ow_poll_frequency" value="%SET_WID_OW_POLL_FREQ%" required onchange="" />
						</div>

					</div>

					<div class="col-6 form_save text-end" id="widget_ow_form_result">
						<button type="submit" class="btn btn-sm btn-primary">UPDATE</button>
					</div>
						
				</div>
			</div>
		</div>
	</form>

)rawliteral";