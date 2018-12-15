var WLAN_NAME = "...";
var WLAN_KEY = "...";
var WEATHER_URL = "http://open.live.bbc.co.uk/weather/feeds/en/2647937/observations.rss";

var wifi;
var g;

A5.write(0); // LCD GND
A7.write(1); // LCD VCC

// This gets the weather out of the XML and writes it to the LCD
function parseWeather(xml, date) {
  // No XML parser, so we have to be nasty
  var item = xml.indexOf("<item>");
  var descStart = xml.indexOf("<description>", item);
  var descEnd= xml.indexOf("</description>", descStart);
  var desc = xml.substring(descStart+13,descEnd);
  // replace the degrees symbol with a quote - built in font only does first 128 chars
  desc = desc.replace("°","'").replace("°","'");
  // make sure things fit on the tiny screen!
  desc = desc.replace("Wind Direction","Wind").replace("Temperature:","Temp:");
  // draw one item per line
  var weather = desc.split(", ");
  g.clear();
  weather.forEach(function(s,i) {
    g.drawString(s,0,i*6);
  });
  // Finally print the time from the HTTP request (so we know it's up to date!)
  var d = new Date(date);
  var timeStr = d.getHours()+":"+("0"+d.getMinutes()).substr(-2);
  g.drawString(timeStr, g.getWidth()-g.stringWidth(timeStr), g.getHeight()-5);
  // Now send this to the LCD
  g.flip();
}

// Actually get weather off the net and display it
function getWeather() {
  // do an HTTP request
  require("http").get(WEATHER_URL, function(res) {
    // console.log("Response: ",res);

    // read the whole response into a variable
    // note: this works here but isn't a great idea - big responses can
    // easily use up all the available memory
    var xml = "";
    res.on('data', function(d) { xml += d; });
    // when the connection closes, parse the weather and write to the LCD
    res.on('close', function(d) { parseWeather(xml, res.headers.Date); });
  });
}

// When we start up...
function onInit() {
  // if we save()d to flash after we'd already run onInit() we need to clear existing intervals
  clearInterval();
  // Set up the ESP8266
  Serial2.setup(9600, { rx: A3, tx : A2 });
  console.log("Init ESP8266...");
  wifi = require("ESP8266WiFi").connect(Serial2, function(err) {
    if (err) throw err;
    wifi.reset(function(err) {
      if (err) throw err;
      console.log("Connecting to WiFi");
      wifi.connect(WLAN_NAME, WLAN_KEY, function(err) {
        if (err) throw err;
        console.log("Connected");
        // Now start getting weather...
        setInterval(getWeather, 60000); // every 60s
        getWeather(); // do the first one right away
      });
    });
  });
  // Setup SPI for LCD
  var spi = new SPI();
  spi.setup({ sck:B1, mosi:B10 });
  // Initialise the LCD
  g = require("PCD8544").connect(spi,B13,B14,B15, function() {
    g.drawString("Please wait...",0,0);
    g.flip();
  });
}

onInit();
