#pragma once

const char index_settings_themes_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html data-bs-theme="%THEME%">
	<head>
		<title>TinyWATCH S3 | Web Settings | Themes</title>
		%META%
	</head>
	<body>
		<div class="content" style="margin-top:12px;">
			<h2 class="center">TinyWATCH S3 | Web Portal | Themes</h2>

			<div class="content" style="margin:30px;">
				<div class="row">
					<div class='col-1'>&nbsp;</div>
					<div class='col-2 center'><a href='/index.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>WATCH</button></a></div>
					<div class='col-2 center'><a href='/web_settings_web.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>WIFI&nbsp;&&nbsp;WEB</button></a></div>
					<div class='col-2 center'><a href='/web_settings_widgets.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>WIDGETS</button></a></div>
					<div class='col-2 center'><a href='/web_settings_apps.html'><button class='btn btn-sm btn-outline-primary' style='width:130px;'>APPS</button></a></div>
					<div class='col-2 center'><button class='btn btn-sm btn-primary' style='width:130px;'>THEMES</button></div>
					<div class='col-1'>&nbsp;</div>
				</div>
			</div>

			<div class="content">

				%SETTING_OPTIONS_THEMES%

			</div>

		%FOOTER%



		 	%WEBFORM_DYNAMIC_JS%

		<script>
			function toggle_new_theme(state)
			{
			    var elem = document.getElementById('add_new_theme');
				elem.style.display = (state ? 'block' : 'none');

				var elem2 = document.getElementById('add_new_theme_button');
				elem2.style.display = (state ? 'none' : 'block');

				
			}
		</script>

)rawliteral";
