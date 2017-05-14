#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


const char *ssid = "Prueba";
const char *password = "123abcde";

ESP8266WebServer server(80);

  String pagina;
  int ledPin = 2;
   
void handle_led() {
  
  int estado = server.arg("estado").toInt(); 
  
  if(estado==1){
    digitalWrite(ledPin, LOW); 
    Serial.println("Encendido"); 
  }
  else{
    digitalWrite(ledPin, HIGH);
    Serial.println("Apagado");
  }
  server.send(200, "text/html", pagina);
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  pagina="<!DOCTYPE HTML>";
  pagina+="<html>";
  pagina+="<head>";
  pagina+="<title>Manejo de un LED</title>";
  pagina+="</head>";
 
  pagina+="<body>";
  pagina+="<div align='center' style='position:absolute; top:30px; left:30px; width:200px; height:200px;";
      pagina+="background-color:blue; border-radius: 10px '>";
      pagina+="<h3 style='color: white'>LED</h3>";
      pagina+="<form action='led' ><input type='radio' name='estado' value='1' checked>Encender<br>";
                       pagina+="<input type='radio' name='estado' value='0' top='100'>Apagar<br><br>";
                       pagina+="<input type='submit' value='Enviar'><br >";
      pagina+="</form>";
  pagina+="</body>";
  pagina+="</html>";


  pagina="<script type='text/javascript'>";
  pagina+="var new_bottom=-380;var aux_new_bot=-380;var new_height=20;var aux_new_he=20;var myvar;var myvar2;";
  pagina+="function iniciar(){";
    pagina+="document.getElementById('iniciar_but').disabled=true;document.getElementById('vaciar_but').disabled=true;";
    pagina+="if(aux_new_he<=400){";
      pagina+="var cam=document.getElementById('liquido'); cam.setAttribute('style','background-color:#4169E1; position: relative; width: 400px; height:'+new_height+'px; bottom:'+new_bottom+'px;');";
      pagina+="if(new_height!=400){ new_bottom=new_bottom+20; new_height=new_height+20;}aux_new_he+=20;}";
    pagina+="else{clearInterval(myvar); document.getElementById('vaciar_but').disabled=false; alert('El tanque ha llegado a su maxima capacidad');} }";
  pagina+="function vaciar(){document.getElementById('vaciar_but').disabled=true; aux_new_bot=new_bottom;";
    pagina+="if(aux_new_bot>=-400){var cam=document.getElementById('liquido'); cam.setAttribute('style','background-color:#4169E1; position: relative; width: 400px; height:'+new_height+'px; bottom:'+new_bottom+'px;');";
      pagina+="if(new_bottom!=-420){new_bottom=new_bottom-20; new_height=new_height-20;} aux_new_bot=aux_new_bot-20;}";
    pagina+="else{clearInterval(myvar2);document.getElementById('iniciar_but').disabled=false;alert('El tanque se ha vaciado');new_bottom=-380;aux_new_bot=-380;new_height=20;aux_new_he=20;}}</script>";
pagina+="<style type='text/css'>";
  pagina+=".tanque{width: 400px;height:400px;border-radius: 0px 0px 0px 0px ;background-color:#00000;border-color:black;border-style:solid;boder-width:15px;position: relative;top:80px;}";
  pagina+="#choco{background-color:brown;width: 400px;height:50px;}";
  pagina+=".botones{position: relative;top:0px;left:0px;}";
  pagina+="#iniciar_but{position: relative;top:-300px;left:350px;width: 100px;background-color: #40E0D0;border: 2px #00000 solid; border-radius: 5px;font-size: 18px;font-family:Lucida Sans Unicode;color: #2F4F4F;}";
  pagina+="#vaciar_but{position: relative;top:40px;left:800px;width: 100px;background-color: #FF6347;border: 2px #00000 solid; border-radius: 5px;font-size: 18px;font-family:Lucida Sans Unicode;color: #2F4F4F;}";
  pagina+="#titulo{positio:absolute;top: 0px;background-color: #20B2AA;font-family:Lucida Sans Unicode;color: #00000;}</style>";
pagina+="<html><head></head><body style='background-color:#FAF0E6'><center><h1 id:'titulo' style='background-color:#008080; width: 500px; height: 90px; border:dotted; font-family: Lucida Sans Unicode;";
  pagina+="color:#FFFAFA;'>Proceso de llenado y vaciado de un tanque</h1></center><form method='GET'><center><div class='tanque'><div id='liquido' style='background-color:#4169E1; position: relative; width: 400px; height:0px; bottom:0px;'></div>";
    pagina+="</div></center><div class='botones' method='GET'><button type='button' id='iniciar_but' onclick="; 
    pagina+="myvar=setInterval('iniciar()',500)"; 
    pagina+=">Iniciar</button>";
          pagina+="<button type='button' id='vaciar_but'  onclick=";
          pagina+="myvar2=setInterval('vaciar()',500)";
          pagina+="disabled='true'>Vaciar</button></div></form></body></html>";

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.print("Ingrese la siguiente dieccion IP en su navegador: ");
  Serial.println(myIP);
  
  server.on("/", [](){
   server.send(200, "text/html",  pagina);
  });
  server.on("/led", handle_led);
  server.begin();
}

void loop() {
  server.handleClient();
}
