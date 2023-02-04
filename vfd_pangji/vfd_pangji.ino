#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>               // Include NTPClient library
#include <TimeLib.h>                 // Include Arduino time library

WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "cn.ntp.org.cn", 8*3600, 60000);
NTPClient timeClient(ntpUDP, "ntp.ntsc.ac.cn", 8 * 3600, 60000);
// 'cn.ntp.org.cn' is used (default server) with +1 hour offset (3600 seconds) 60 seconds (60000 milliseconds) update interval
const char *ssid     = "MIWIFI8";
const char *password = "12345678";


//uint8_t din   = 9; // DA
//uint8_t clk   = 10; // CK
//uint8_t cs    = 11; // CS
//uint8_t Reset = 12; // RS
//uint8_t VFD_EN = 13; // RS


// self.spi = SPI(1, 1000000,sck=Pin(12),mosi=Pin(13),miso=Pin(14))  #sck-clk mosi-din
// self.en = Pin(4)
// self.rst = Pin(5)
// self.cs = Pin(26)

uint8_t din   = 3; // DA
uint8_t clk   = 2; // CK
uint8_t cs    = 7; // CS
uint8_t Reset = 5; // RS
uint8_t VFD_EN = 4; // EN

char *str_time = "00:00:00";
String format_time = "00:00:00";

void write_6302(unsigned char w_data)
{
  unsigned char i;
  for (i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
    if ( (w_data & 0x01) == 0x01)
    {
      digitalWrite(din, HIGH);
    }
    else
    {
      digitalWrite(din, LOW);
    }
    w_data >>= 1;
    digitalWrite(clk, HIGH);
  }
  Serial.printf("write_6302");
}

void VFD_cmd(unsigned char command)
{
  digitalWrite(cs, LOW);
  write_6302(command);
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
  Serial.printf("S1201_show\n");
}

void S1201_show(void)
{
  digitalWrite(cs, LOW);//开始传输
  write_6302(0xe8);     //地址寄存器起始位置
  digitalWrite(cs, HIGH); //停止传输
  Serial.printf("VFD_cmd\n");
}

void VFD_init()
{
  //SET HOW MANY digtal numbers
  digitalWrite(cs, LOW);
  write_6302(0xe0);
  delayMicroseconds(5);
  write_6302(0x07);//8 digtal
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);

  //set bright
  digitalWrite(cs, LOW);
  write_6302(0xe4);
  delayMicroseconds(5);
  write_6302(0x33);//leve 255 max
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
  Serial.printf("VFD_init\n");
}

/******************************
  在指定位置打印一个字符(用户自定义,所有CG-ROM中的)
  x:0~11;chr:要显示的字符编码
*******************************/
void S1201_WriteOneChar(unsigned char x, unsigned char chr)
{
  digitalWrite(cs, LOW);  //开始传输
  write_6302(0x20 + x); //地址寄存器起始位置
  write_6302(chr + 0x30);
  digitalWrite(cs, HIGH); //停止传输
  S1201_show();
  Serial.printf("S1201_WriteOneChar\n");
}
/******************************
  在指定位置打印字符串
  (仅适用于英文,标点,数字)
  x:0~11;str:要显示的字符串
*******************************/
void S1201_WriteStr(unsigned char x, char *str)
{
  digitalWrite(cs, LOW);  //开始传输
  write_6302(0x20 + x); //地址寄存器起始位置
  while (*str)
  {
    write_6302(*str); //ascii与对应字符表转换
    str++;
  }
  digitalWrite(cs, HIGH); //停止传输
  S1201_show();
  Serial.printf("S1201_WriteStr\n");
}

void setup() {
  pinMode(clk, OUTPUT);
  pinMode(din, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(Reset, OUTPUT);

  pinMode(VFD_EN, OUTPUT);
  digitalWrite(VFD_EN, HIGH);
  delayMicroseconds(5);

  digitalWrite(Reset, LOW);
  delayMicroseconds(5);
  digitalWrite(Reset, HIGH);
  VFD_init();
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  Serial.print("Connecting.");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
    S1201_WriteStr(0, "__WIFI__");
  }
  Serial.println("connected");
  S1201_WriteStr(0, "__DONE__");
  delay(500);

  timeClient.begin();

  S1201_WriteStr(0, "________");
  delay(200);
  S1201_WriteStr(0, "_______@");
  delay(200);
  S1201_WriteStr(0, "______@U");
  delay(200);
  S1201_WriteStr(0, "_____@UN");
  delay(200);
  S1201_WriteStr(0, "____@UNP");
  delay(200);
  S1201_WriteStr(0, "___@UNPZ");
  delay(200);
  S1201_WriteStr(0, "__@UNPZZ");
  delay(200);
  S1201_WriteStr(0, "_@UNPZZS");
  delay(200);
  S1201_WriteStr(0, "@UNPZZST");
  delay(200);
  S1201_WriteStr(0, "UNPZZSTU");
  delay(200);
  S1201_WriteStr(0, "NPZZSTUD");
  delay(200);
  S1201_WriteStr(0, "PZZSTUDI");
  delay(200);
  S1201_WriteStr(0, "ZZSTUDIO");
  delay(200);
  S1201_WriteStr(0, "ZSTUDIO_");
  delay(200);
  S1201_WriteStr(0, "STUDIO__");
  delay(200);
  S1201_WriteStr(0, "TUDIO___");
  delay(200);
  S1201_WriteStr(0, "UDIO____");
  delay(200);
  S1201_WriteStr(0, "DIO_____");
  delay(200);
  S1201_WriteStr(0, "IO______");
  delay(200);
  S1201_WriteStr(0, "O_______");
  delay(200);
  S1201_WriteStr(0, "________");
  delay(1000);
  Serial.println("Initialized");
}

void loop() {
  timeClient.update();
  format_time = timeClient.getFormattedTime();
  char *str_time = &format_time[0];
  S1201_WriteStr(0, str_time);
  Serial.println(timeClient.getFormattedTime());
  delay(1000);
}
