//Se descomentar as linhas abaixo, habilita o debugging
#define DEBUGGING(...) Serial.println( __VA_ARGS__ )
#define DEBUGGING_L(...) Serial.print( __VA_ARGS__ )

//#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h> //Biblioteca que permite chamar o seu modulo ESP8266 na sua rede pelo nome ao inves do IP.
#include <ESP8266HTTPUpdateServer.h> //Biblioteca que cria o servico de atualizacão via wifi (ou Over The Air - OTA)
#include <Wire.h>
#include <VL53L0X.h>
#include <WiFiUdp.h>
#include <time.h>
#include <sys/time.h>
#include <coredecls.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = -10800;
int hora;
int minuto;
int segundo;
float medida;
float peso;
char week;
String troca[5][3];
int ntroca;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

VL53L0X sensor;

//Habilitando a saída serial com as mensagens de debugging
#ifndef DEBUGGING
#define DEBUGGING(...)
#endif
#ifndef DEBUGGING_L
#define DEBUGGING_L(...)
#endif

const char* host      = "sealerv1"; //Nome que seu ESP8266 (ou NodeMCU) tera na rede
const char* ssid      = "vsantos"; //Nome da rede wifi da sua casa
const char* password  = "nosrednav21"; //Senha da rede wifi da sua casa
ESP8266HTTPUpdateServer atualizadorOTA; //Este e o objeto que permite atualizacao do programa via wifi (OTA)
ESP8266WebServer servidorWeb(80); //Servidor Web na porta 80


//Esta e a pagina enviada para o navegador de internet


//String paginaWeb = ""
String getWebPage(){
String page = "<html>";
page += "<head>";
page += "<meta http-equiv='Content-Type'";
page += "content='text/html; charset=iso-8859-1'>";
page += "<meta name='GENERATOR' content='Microsoft FrontPage Express 2.0'>";
page += "<title>SealerV1</title>";
page += "<style>";
page +=     " body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }" ;
page +=    "</style>";
page += "</head>";
//page += ;
page += "<body bgcolor='#FFFFFF'>";
page += "<div align='center'><center>";
//
page +="<table border='0' cellpadding='0' cellspacing='0' width='650'>";
page +="    <tr>";
page +="        <td width='100%'><div align='center'><center><table";
page +="        border='0' cellpadding='0' cellspacing='0' width='100%'>";
page +="            <tr>";
page +="                <td width='50%'><div align='center'><font size='7'><strong>HMB</strong></font></td>";
page +="                <td width='50%'><div align='center'><font size='7'><strong>IOT PAINT - SEALER</strong></font>";
page +="                 </td>";
page +="            </tr>";
page +="        </table>";
page +="        </center></div></td>";
page +="    </tr>";
page +="    <tr>";
page +="        <td width='100%'><div align='center'><center><table";
page +="        border='0' cellpadding='0' cellspacing='1' width='100%'>";
page +="            <tr>";
page +="                <td width='50%' bgcolor='#000080'><p align='center'>";
page +="               <font color='#FFFFFF'><strong>Time & Space</strong>";
page +="                </font></p>";
page +="                </td>";
page +="                <td width='50%' bgcolor='#000080'><p align='center'>";
page +="                <font color='#FFFFFF'><strong>Sealer use</strong>";
page +="                </font></p>";
page +="                </td>";
page +="            </tr>";
page +="           <tr>";
page +="                <td width='40%'><p align='left'><font color='#000080'><strong>";
page +="<div align='center'><font size='5'>";
page +=daysOfTheWeek[timeClient.getDay()];
page +="";
page +="";
page +="</p>";
//page +="
page +=hora ;
page +=" :";
page +=minuto;
page +="<p>";
page +="</p>";
page +="";
page +=medida;
page +="cm            </strong></font>  ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                </p>";
page +="                </td>";
page +="                <td width='50%'>";
page +="                ";
page +="                ";
page +="<div align='center'><font size='5'>";
page +=peso;
page +="kg";
page +="";
page +="</p>";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="               ";
page +="                ";
page +="                 </td>";
page +="            </tr>";
page +="            <tr>";
page +="                <td width='50%' bgcolor='#000080'><p align='center'>";
page +="                <font color='#FFFFFF'><strong>.</strong>";
page +="                </font></p>";
page +="                </td>";
page +="                <td width='50%' bgcolor='#000080'><p align='center'>";
page +="                ";
page +="                <font color='#FFFFFF'><strong>.</strong>";
page +="                </font></p>";  
page +="</td>";
page += "           </tr>";
page +=  "          <tr>";
page +=   "             ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                 </td>";
page +="                <td width='50%'>";
page +="               ";
page +="               ";
page +="              ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                ";
page +="                 </td>";
page +="            </tr>";
page +="            <tr>";
page +="                <td colspan='2' bgcolor='#000080'><p align='center'>";
page +="                <font color='FFFFFF'><strong>copyright 2019<br>";
page +="                <a href='mailto:vandersonbr@email.com?Subject=Hello%20again' target='_top'><font color='white'>Design by Vanderson dos Santos</a></strong></font></p>";
page +="                </td>";
page +="            </tr>";
page +="        </table>";
page +="        </center></div></td>";
page +="    </tr>";
page +="</table>";
page +="</center></div>";
page +="</body>";
page +="</html>";
page+="<meta http-equiv='refresh' content='5'>";
page += "</body></html>";
  return page;
};
//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  //Se vc ativou o debugging, devera descomentar esta linha abaixo tambem.
  Serial.begin(9600);

  InicializaWifi();
  InicializaMDNS();
  InicializaServicoAtualizacao();
   Wire.begin();
   sensor.init();
   sensor.setTimeout(500);
   sensor.startContinuous();
   timeClient.begin();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    InicializaWifi();
    InicializaMDNS();
  
  //Serial.println(timeClient.getFormattedTime());
//  timeClient.update();

//  Serial.print(daysOfTheWeek[timeClient.getDay()]);
 // Serial.print(", ");
//  Serial.print(timeClient.getHours());
//  Serial.print(":");
 // Serial.print(timeClient.getMinutes());
 // Serial.print(":");
 // Serial.println(timeClient.getSeconds());
// hora=(timeClient.getFormattedTime());
 
// dist=(sensor.readRangeContinuousMillimeters()*0.1);
  
  
  }
  
  timeClient.update();
  servidorWeb.handleClient();
   DEBUGGING(sensor.readRangeContinuousMillimeters()*0.1);


  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
   
//  week=(daysOfTheWeek[timeClient.getDay()]);
  hora=(timeClient.getHours());
  minuto=(timeClient.getMinutes());
  segundo=(timeClient.getSeconds());
  medida=(sensor.readRangeContinuousMillimeters()*0.1);
  
peso=medida-7;//distencia 0
peso=peso*55.30;//relacao peso distancia

//17 = 1620 x17=0  
//129 = 0 x 129=1620
//73 = 810
// 38,4 = 1310,48 
//1 = 95,29
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
Serial.println(peso);
   delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////////////////


void RecepcaoClienteWeb() {

    servidorWeb.send(200, "text/html", getWebPage());
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void InicializaServicoAtualizacao() {
  atualizadorOTA.setup(&servidorWeb);
  servidorWeb.begin();
  DEBUGGING_L("O servico de atualizacao remota (OTA) Foi iniciado com sucesso! Abra http://");
  DEBUGGING_L(host);
  DEBUGGING(".local/update no seu browser para iniciar a atualizacao\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void InicializaWifi() {
  //WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
  }
  servidorWeb.on("/", RecepcaoClienteWeb);
  
  DEBUGGING("Conectado!");
  DEBUGGING(WiFi.localIP());
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void InicializaMDNS() {
  if (!MDNS.begin(host)) {
   DEBUGGING("Erro ao iniciar o servico mDNS!");
    while (1) {
      delay(1000);
    }
  }
  DEBUGGING("O servico mDNS foi iniciado com sucesso!");
  MDNS.addService("http", "tcp", 80);
 
}
