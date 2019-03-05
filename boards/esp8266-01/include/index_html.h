const char CONFIG_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>Sensor</title>
  <meta charset="UTF-8">
</head>
<body>

<p>Enter your WiFi credentials in the form below and click the button</p>

<form id="config_form" action="\save" required>
  SSID(nome della rete): <input type="text" name="ssid"><br>
  Password: <input type="text" name="psw"><br><br>
  <input type="button" onclick="myFunction()" value="Configure network">
</form>

<script>

	function myFunction() {
	  document.getElementById("config_form").submit();
	}

</script>

</body>
</html>
)=====";


const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>Sensor</title>
  <meta charset="UTF-8">
</head>
<body>

<p>Delay Time Settings:</p>

<form id="config_form" action="\" required>
  Delay Time: <input type="text" name="dt"><br>
  <input type="button" onclick="myFunction()" value="Set delay.">
</form>

<script>

	function myFunction() {
	  document.getElementById("config_form").submit();
	}

</script>

</body>
</html>
)=====";
