
//reading data
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

/********************************************************************************/
//Things to change
const char * ssid = "M20";
const char * password = "12345678";

const int sendInterval = 5000; 
String GOOGLE_SCRIPT_ID = "";
int httpCode = 0;
/********************************************************************************/

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Started");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
Serial.println("Ready to go");
//testdrawstyles();
}

void loop() {
  print_consti();
 //print_candi(2);
//fetch_constid(45678);
//voting();

  delay(sendInterval);
}
int fetch_constid(int votid){

  for(int i = 2;i<=6;i++)
  {
    GOOGLE_SCRIPT_ID = "AKfycbx_qhNihhGPChpDxig906358GO8z0iSyW96couRLfOVqOuvxJWUXTkF_2XMLXmzs3cR";
  HTTPClient http;
   String checkurl2="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=A"+i;
	http.begin(checkurl2.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	httpCode = http.GET();
  String vp;
  String returning;
    if (httpCode > 0) { //Check for the returning code
        vp = http.getString();
      }
    int vpi = vp.toInt();
    http.end();
    if(vpi == votid){
      Serial.print("Voter id: ");
      Serial.println(votid);

      String url001="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=B"+i;
	    Serial.print("Voter Name: ");
	    http.begin(url001.c_str()); //Specify the URL and certificate
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	    httpCode = http.GET();
      String payload001;
      if (httpCode > 0) { //Check for the returning code
          payload001 = http.getString();
          Serial.println(payload001);
        }
	  http.end();

    String url002="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=C"+i;
	    Serial.print("Constituency ID: ");
	    http.begin(url002.c_str()); //Specify the URL and certificate
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	    httpCode = http.GET();
      String payload002;
      if (httpCode > 0) { //Check for the returning code
          payload002 = http.getString();
          Serial.println(payload002);
          returning = payload002;
        }
	  http.end();
    
    break;
    }
    return returning.toInt();

  }
}

void print_consti(void) {

  GOOGLE_SCRIPT_ID = "AKfycbzMhV8UToGBk-AFXkouLUwgM3hp_gdLo1emB9r4vfzLko5N-uZsY64coBb8CN62ZNXyLA";
lcd.setCursor(0,0);
  //--------------------------------------------------------------- 1st column read
  for(int i =2;i<=3;i++){
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=A"+i;
//   Serial.print(url);
	lcd.print("Co no: ");
  
  //Serial.print(i);
	http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	httpCode = http.GET();
  String payload1;
    if (httpCode > 0) { //Check for the returning code
        payload1 = http.getString();
        //Serial.println(httpCode1);
        lcd.println(payload1);
      }
    else {
      Serial.println("Error on HTTP request");
    }
	http.end();
  //---------------------------------------------------------------------2nd column read
  lcd.setCursor(0,1);
   String url2="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=B"+i;
//   Serial.print(url);
	lcd.print("Co name: ");
	http.begin(url2.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	httpCode = http.GET();
  String payload2;
    if (httpCode > 0) { //Check for the returning code
        payload2 = http.getString();
        //Serial.println(httpCode2);
        lcd.println(payload2);
      }
    else {
      Serial.println("Error on HTTP request");
    }
	http.end();
  delay(2000);
  lcd.clear();
}
}
void print_candi(int constid)
{
  
  for(int i =2;i<=5;i++){
  GOOGLE_SCRIPT_ID = "AKfycbzUpl60D6neLKEyYtDFYiwrV8wnq1Sl-2FYASpZqXT1hwKf-QUOg0076D1A9N1m03MIEg";
  HTTPClient http;
   String checkurl="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=C"+i;
	http.begin(checkurl.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	httpCode = http.GET();
  String cp;
    if (httpCode > 0) { //Check for the returning code
        cp = http.getString();
      }
    int cpi = cp.toInt();
    http.end();
   if(cpi == constid)//user input here please
    {
      lcd.clear();
      lcd.setCursor(0,0);
      String url01="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=A"+i;
	    lcd.print("Can ID: ");
	    http.begin(url01.c_str()); //Specify the URL and certificate
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	    httpCode = http.GET();
      String payload01;
      if (httpCode > 0) { //Check for the returning code
          payload01 = http.getString();
          lcd.print(payload01);
        }
	  http.end();
lcd.setCursor(0,1);
    String url02="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=B"+i;
	    lcd.print("CanName: ");
	    http.begin(url02.c_str()); //Specify the URL and certificate
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	    httpCode = http.GET();
      String payload02;
      if (httpCode > 0) { //Check for the returning code
          payload02 = http.getString();
          lcd.print("Chris");
        }
	  http.end();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ConID : ");
    lcd.print(constid);


   }
  }
}
void voting(){
  //show qr code then corresponding constituency voting happens
  //getting qr code value
  GOOGLE_SCRIPT_ID = "AKfycbxM3IT9djo8YzgN-E4ARgPUdLg4jwlwRzG4qV4wpcGw_xroPKDSa1UI-FpnM2tAVgTR";
  HTTPClient http;
  String urlqr="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read=A2";
	    Serial.print("Fetched data: ");
	    http.begin(urlqr.c_str()); //Specify the URL and certificate
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	    httpCode = http.GET();
      String payload02;
      if (httpCode > 0) { //Check for the returning code
          payload02 = http.getString();
          Serial.println(payload02);
        }
	  http.end();
    int fetched = payload02.toInt();
}

