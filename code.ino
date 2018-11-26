#include <DHT.h>
#define DHTPIN 8   
#include <LiquidCrystal.h>
#define DHTTYPE DHT11  
#include <DS3231.h>

DHT dht(DHTPIN, DHTTYPE);
DS3231  rtc(SDA, SCL);
LiquidCrystal lcd(12, 11, 4, 5, 6,7);//initialisation de l'ecran lcd 
char temp[11] ={'t','e','m','p','e','r','a','t','u','r','e'};
char hum[8]={'h','u','m','i','d','i','t','e'};

void setup()
{
  Serial.begin(115200);
 for(int i=0;i<=11;i++){
  Serial.print(temp[i]);
  } 
lcd.begin(16,2);
rtc.begin();
//reglage du temps et de l'heure et du jours
  rtc.setDOW(THURSDAY);     // reglage rouge de la semaine  to SUNDAY
  rtc.setTime(12, 47, 0);     // temps  12:00:00 (24hr format)
  rtc.setDate(26, 11, 2018);   //  date to January 1st, 2014
  }

void loop()
{
  //detection de temperatureet d'humiditer
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
 //   Serial.println("Failed to read from DHT sensor!");
    return;
  }
 float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
//affichage de la date,l'heure,et le jour.

for(int i=16;i>=0;i--){
  lcd.setCursor(i,0);
lcd.print("WELCOME to DAKAR");
delay(100);
}

for(int j=16;j>=0;j-=2){
  lcd.setCursor(j,1);
  lcd.print("BIENVENU A DAKAR ");
  delay(100);
  }
  delay(2000);
  lcd.clear();
 
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("DATE:");
  lcd.setCursor(6,0);
   lcd.print(rtc.getDateStr());
   lcd.setCursor(0,1);
   lcd.print("HEURE:");
   lcd.setCursor(7,1);
   lcd.print(rtc.getTimeStr()); 
  delay (5000);
  lcd.clear();
 for(int i=0;i<11;i++){
     lcd.print(temp[i]);
      delay(100);
}
lcd.setCursor(0,1);
for(int v=0;v<8;v++){
  lcd.print(hum[v]);
  delay(100);
    }
//lcd.setCursor(16,1);
lcd.autoscroll(); 
delay(100);
lcd.noAutoscroll();
lcd.setCursor(12,0);
lcd.print(t);
lcd.setCursor(15,0);
lcd.print("C");
lcd.setCursor(0,1);
lcd.setCursor(8,1);
lcd.print(":");
lcd.print(h);
lcd.setCursor(14,1);
lcd.print("%");
delay(5000);
}
