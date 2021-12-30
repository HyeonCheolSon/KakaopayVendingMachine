#include "esp_camera.h"
#include <HTTPClient.h>
#include <WiFi.h>

//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled
//

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

const char* ssid = "Galaxy Note10 5G1707";
const char* password = "12345678";

String previous_time = "";

void startCameraServer();
String* Split();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.mode(WIFI_OFF);

    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(200);
    }

  Serial.println("Connecting to WIFI");
  
  WiFi.mode(WIFI_STA);
  delay(1000);
  
  WiFi.begin(ssid, password);
  Serial.println(ssid);
  Serial.println(password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("http://3.35.98.45:8080/Kakaopay/read.jsp"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(payload);
        int time_start = payload.indexOf("<time>");
        int time_end = payload.indexOf("</time>");
        String timevalue = payload.substring(time_start + 6, time_end);
        Serial.println("timevalue: " + timevalue);
        if(!previous_time.equals(timevalue))
        {
          Serial.println("자판기 작동");
          previous_time = timevalue;
          /*******
           insert code here - 자판기 작동
           *******/
        }
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
  delay(10000);
}

//String* Split(String sData, char cSeparator)
//{  
//  int nCount = 0;
//  int nGetIndex = 0 ;
//
//  //임시저장
//  String sTemp = "";
//
//  //원본 복사
//  String sCopy = sData;
//
//  String* output = (String*)malloc(sizeof(String));
//  while(true)
//  {
//    //구분자 찾기
//    nGetIndex = sCopy.indexOf(cSeparator);
//
//    //리턴된 인덱스가 있나?
//    if(-1 != nGetIndex)
//    {
//      //있다.
//
//      //데이터 넣고
//      sTemp = sCopy.substring(0, nGetIndex);
//
//      Serial.println( sTemp );
//      output[nCount] = sTemp;
//      output = (String*)realloc(output, sizeof(String) * (nCount+2));
//      //뺀 데이터 만큼 잘라낸다.
//      sCopy = sCopy.substring(nGetIndex + 1);
//    }
//    else
//    {
//      //없으면 마무리 한다.
//      Serial.println( sCopy );
//      output[nCount] = sCopy;
//      break;
//    }
//
//    //다음 문자로~
//    ++nCount;
//  }
//  return output;
//}
