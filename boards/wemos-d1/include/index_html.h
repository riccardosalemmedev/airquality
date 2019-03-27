const char CONFIG_HTML[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <head>
    <title>Sensor</title>
    <meta charset="UTF-8">
  </head>
  <body>

  <p>Enter your WiFi credentials in the form below and click the button</p>

  <form id="wifi_form" action="\save" required>
    SSID(nome della rete): <input type="text" name="ssid"><br>
    Password: <input type="text" name="psw"><br><br>
    <input type="button" onclick="wifi_form()" value="Configure network">
  </form>


  <p>Enter your ThingSpeak credentials in the form below and click the button</p>

  <form id="ts_form" action="\save" required>
    ThingSpeak API Key: <input type="text" name="ts_key"><br><br>
    <input type="button" onclick="ts_form()" value="Set Credentials!">
  </form>


  <p>Delay Time Settings:</p>

  <form id="delay_form" action="\save" required>
    Delay Time between values: <input type="text" name="dt"><br>
    <input type="button" onclick="delay_form()" value="Set delay.">
  </form>

  <script>

  	function wifi_form() {
  	  document.getElementById("wifi_form").submit();
  	}
    function ts_form() {
  	  document.getElementById("ts_form").submit();
  	}
    function delay_form() {
  	  document.getElementById("delay_form").submit();
  	}


  </script>

  </body>
  </html>

)=====";
