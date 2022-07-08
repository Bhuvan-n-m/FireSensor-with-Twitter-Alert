 #include <DHT.h>  
 #include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>  
 #define DHTPIN D3  
 #define DHTTYPE DHT11  
 DHT dht(DHTPIN, DHTTYPE);  
 const char* ssid = "BHUVAN";  
 const char* password = "bhuvan1902";  
 WiFiClient client;  
 unsigned long myChannelNumber =1405109;  
 const char * myWriteAPIKey = "C2GMNIYUFHW9GX36";  
 uint8_t temperature;
 int smoke_level;
 int mq135=A0;  
 void setup()  
 {  
  Serial.begin(9600);  
  dht.begin();  
  delay(10);  
  // Connecting to my WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
 }  
 void loop()   
 {
  int check_fire=0;                           //Set to 0  
  smoke_level=analogRead(A0);                //reads output from MQ135 gas/smoke sensor as analog values   
  temperature = dht.readTemperature();        //reads temperature values using function of DHT.h header file  
  Serial.println("Uploading Values");
  Serial.println("Temperature : ");
  Serial.println(temperature);
  Serial.print("C");
  Serial.println("Smoke Level : ");
  Serial.print(smoke_level);
  if(temperature>=70&&smoke_level>=500)       //set to 1 if fire detected according to temperature and smoke_level values
  {
    check_fire=1;  
  }
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);    //Sends temperature value to field number 1 in Thingspeak channel
  ThingSpeak.writeField(myChannelNumber, 2, smoke_level, myWriteAPIKey);    //Sends smoke_level value to field number 2 in Thingspeak channel
  ThingSpeak.writeField(myChannelNumber, 3, check_fire, myWriteAPIKey);     //Sends check_fire value to field number 3 in Thingspeak channel*/  
  delay(13000);         // ThingSpeak will only accept updates every 15 seconds.  
 }  
