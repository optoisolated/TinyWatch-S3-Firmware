#pragma once

const char index_settings_web_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html data-bs-theme="%THEME%">
	<head>
		<title>TinyWATCH S3 | Web Settings | Widgets</title>
		%META%
	</head>
	<body>
		<div class="content" style="margin-top:12px;">
			<h2 class="center">TinyWATCH S3 | Web Portal| Web & WiFi</h2>

			<div class="content" style="margin:30px;">
				<div class="row">
					<div class='col-1'>&nbsp;</div>
					<div class='col-2 center'><a href='/index.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>WATCH</button></a></div>
					<div class='col-2 center'><button class='btn btn-sm btn-primary' style='width:130px;'>WIFI&nbsp;&&nbsp;WEB</button></a></div>
					<div class='col-2 center'><a href='/web_settings_widgets.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>WIDGETS</button></a></div>
					<div class='col-2 center'><a href='/web_settings_apps.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>APPS</button></a></div>
					<div class='col-2 center'><a href='/web_settings_themes.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>THEMES</button></a></div>
					<div class='col-1'>&nbsp;</div>
				</div>
			</div>

			<div class="content">

				%SETTING_OPTIONS_WEB%

			</div>

		%FOOTER%

 		%WEBFORM_DYNAMIC_JS%

)rawliteral";
