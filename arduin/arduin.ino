#include <SPI.h>
#define uchar unsigned char
#define uint unsigned int
#define MAX_LEN 16
const int chipSelectPin = 10;    //SDA引脚片选引脚
const int NRSTPD = 9;            //RST引脚
//MF522 命令位
#define PCD_IDLE 0x00             //取消当前命令不行动
#define PCD_AUTHENT 0x0E         //验证密码的钥匙
#define PCD_RECEIVE 0x08         //接收数据
#define PCD_TRANSMIT 0x04        //发送数据
#define PCD_TRANSCEIVE 0x0C        //发送和接收数据
#define PCD_RESETPHASE 0x0F        //重置
#define PCD_CALCCRC 0x03        //CRC校验和的计算
//Mifare_One卡的命令位
#define PICC_REQIDL 0x26        //在天线区域搜索不进入睡眠模式的卡 
#define PICC_REQALL 0x52         //搜索天线区域中的所有卡 
#define PICC_ANTICOLL 0x93        //防止冲突 
#define PICC_SElECTTAG 0x93     //选择卡
#define PICC_AUTHENT1A 0x60     //验证A密码密钥
#define PICC_AUTHENT1B 0x61     //验证B密码密钥
#define PICC_READ 0x30            //读
#define PICC_WRITE 0xA0            //写
#define PICC_DECREMENT 0xC0     //扣除值 
#define PICC_INCREMENT 0xC1     //装载值
#define PICC_RESTORE 0xC2         //还原数据到缓冲区
#define PICC_TRANSFER 0xB0        //保存数据到缓冲区
#define PICC_HALT 0x50             //睡眠模式
//通信时MF522的返回值
#define MI_OK 0
#define MI_NOTAGERR 1
#define MI_ERR 2
//------------------MFRC522 注册 ---------------
//Page 0:命令和状态
#define Reserved00 0x00             //保留将来之用
#define CommandReg 0x01             //启动和停止命令的执行
#define CommIEnReg 0x02             //中断请求传递的使能和禁能控制位。
#define DivlEnReg 0x03                 //中断请求传递的使能和禁能控制位。
#define CommIrqReg 0x04             //包含中断请求标志
#define DivIrqReg 0x05                //包含中断请求标志
#define ErrorReg 0x06                 //错误标志，指示执行行的上个命令的错误状态
#define Status1Reg 0x07             //包含通信的状态标志
#define Status2Reg 0x08             //包含接收器和发射器的状态标志
#define FIFODataReg 0x09            //64字节FIFO缓冲器的输入输出
#define FIFOLevelReg 0x0A            //指示FIFO中存储的字节数
#define WaterLevelReg 0x0B            //定义FIFO下溢和上溢报警的FIFO深度。
#define ControlReg 0x0C                //不同的控制寄存器
#define BitFramingReg 0x0D            //面向位的帧调节
#define CollReg 0x0E                //RF接口上检测到的第一个位冲突的位的位置
#define Reserved01 0x0F                //保留将来之用
//Page 1:控制
#define Reserved10 0x10                //保留将来之用
#define ModeReg 0x11                //定义发射和接收的常用模式
#define TxModeReg 0x12                //定义发射过程的数据传输速率
#define RxModeReg 0x13                //定义接收过程中的数据传输速率
#define TxControlReg 0x14            //控制天线驱动管脚TX1和TX2的逻辑特征
#define TxAutoReg 0x15                //控制天线驱动的设置
#define TxSelReg 0x16                //选择天线驱动器的内部源
#define RxSelReg 0x17                //选着内部的接收器设置
#define RxThresholdReg 0x18            //选择位译码器的阀值
#define DemodReg 0x19                //定义解调器的设置
#define Reserved11 0x1A                //保留将来之用
#define Reserved12 0x1B                //保留将来之用
#define MifareReg 0x1C                //控制ISO 14443/MIFARE 模式106kbit/s的通信
#define Reserved13 0x1D                //保留将来之用
#define Reserved14 0x1E                //保留将来之用
#define SerialSpeedReg 0x1F            //选择串行UART接口的速率
//Page 2:发生器
#define Reserved20 0x20                //保留将来之用
#define CRCResultRegM 0x21            //显示CRC计算的实际MSB和LSB值（MSB)
#define CRCResultRegL 0x22            //显示CRC计算的实际MSB和LSB值（LSB)
#define Reserved21 0x23                //保留将来之用
#define ModWidthReg 0x24            //控制ModWidth的设置
#define Reserved22 0x25                //保留将来之用
#define RFCfgReg 0x26                //配置接受器增益
#define GsNReg 0x27                    //选择天线驱动器管脚TX1和TX2的调制电导
#define CWGsPReg 0x28                //选择天线驱动器管脚TX1和TX2的调制电导
#define ModGsPReg 0x29                //选择天线驱动器管脚TX1和TX2的调制电导
#define TModeReg 0x2A                //定义内部定时器的设置A
#define TPrescalerReg 0x2B            //定义内部定时器的设置B
#define TReloadRegH 0x2C            //描述16位长的定时器重装值（C)
#define TReloadRegL 0x2D            //描述16位长的定时器重装值（D)
#define TCounterValueRegH 0x2E        //显示16位长的实际定时器值（E)
#define TCounterValueRegL 0x2F        //显示16位长的实际定时器值（F)
//Page 3:记录
#define Reserved30 0x30                //保留将来之用
#define TestSel1Reg 0x31            //常用测试信号的配置
#define TestSel2Reg 0x32            //常用测试信号的配置和PRBS控制
#define TestPinEnReg 0x33            //D1—D7输出驱动器的使能管脚（注：仅用于串行接口)
#define TestPinValueReg 0x34        //定义D1-D7用做I/O总线的值
#define TestBusReg 0x35                //显示内部测试总线的状态
#define AutoTestReg 0x36            //控制数字自测试
#define VersionReg 0x37                //显示版本
#define AnalogTestReg 0x38            //控制管脚AUX1和AUX2
#define TestDAC1Reg 0x39             //定义 TestDAC1的测试值
#define TestDAC2Reg 0x3A             //定义 TestDAC2的测试值
#define TestADCReg 0x3B             //显示 ADC I和 Q通道的实际值
#define Reserved31 0x3C             //保留用于产品测试
#define Reserved32 0x3D             //保留用于产品测试
#define Reserved33 0x3E             //保留用于产品测试
#define Reserved34 0x3F                //保留用于产品测试
uchar serNum[5];
int a;
int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(19200);
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);       //设置数字引脚10作为输出连接到RFID/使能引脚
  digitalWrite(chipSelectPin, LOW);    //激活RFID阅读器（片选)
  pinMode(NRSTPD, OUTPUT);            //设置数字引脚9，不复位和断电（复位引脚)
  MFRC522_Init();
}
static void (*reset_this_CPU)(void) = 0x0000;
void loop()
{
  //  a = 0;
  //  int b1 = 0;
  //  int b2 = 0;
  //  int b3 = 0;
  //  int b4 = 0;
  //  delay(500);
  //  if (Serial.available() > 0) {
  RFID();
  //  Serial.print("a= ");
  //  Serial.print(a);

  if (0 < a && a < 13) {
    b1 = a;
    Serial.print("b1=");
    Serial.println(b1);
  }
  else if (12 < a && a < 25) {
    b2 = a - 12;
    Serial.print("b2=");
    Serial.println(b2);
  }
  else if (24 < a && a < 37) {
    b3 = a - 24;
    Serial.print("b3=");
    Serial.println(b3);
  }
  else if (36 < a && a < 49) {
    b4 = a - 36;
    Serial.print("b4=");
    Serial.println(b4);
  }
  suanfa();
  //  }
}

int RFID() {
  uchar status;
  uchar str[MAX_LEN];
  status = MFRC522_Request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    return;
  }
  status = MFRC522_Anticoll(str);
  if (status == MI_OK)
  {
    memcpy(serNum, str, 5);
    uchar* id = serNum;
    if (id[0] == 0x9C && id[1] == 0x21 && id[2] == 0x2F && id[3] == 0x2) {
      a = 1;
      Serial.println("num:1");
      delay(1000);
    } else if (id[0] == 0x5C && id[1] == 0x0E && id[2] == 0x2F && id[3] == 0x2) {
      a = 2;
      Serial.println("num:2");
      delay(1000);
    } else if (id[0] == 0x3C && id[1] == 0xF1 && id[2] == 0x2E && id[3] == 0x2) {
      a = 3;
      Serial.println("num:3");
      delay(1000);
    } else if (id[0] == 0xAC && id[1] == 0xF6 && id[2] == 0x2E && id[3] == 0x2) {
      a = 3;
      Serial.println("num:3");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0x20 && id[2] == 0x2F && id[3] == 0x2) {
      a = 4;
      Serial.println("num:4");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0x20 && id[2] == 0x2F && id[3] == 0x2) {
      a = 4 ;
      Serial.println("num:4");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0xF2 && id[2] == 0x2E && id[3] == 0x2) {
      a = 5 ;
      Serial.println("num:5");
      delay(1000);
    } else if (id[0] == 0xCC && id[1] == 0xF8 && id[2] == 0x2E && id[3] == 0x2) {
      a = 5 ;
      Serial.println("num:5");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0x8 && id[2] == 0x2F && id[3] == 0x2) {
      a = 6 ;
      Serial.println("num:6");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0x17 && id[2] == 0x2F && id[3] == 0x2) {
      a = 6 ;
      Serial.println("num:6");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0x8 && id[2] == 0x2F && id[3] == 0x2) {
      a = 7 ;
      Serial.println("num:7");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0x11 && id[2] == 0x2F && id[3] == 0x2) {
      a = 7 ;
      Serial.println("num:7");
      delay(1000);
    } else if (id[0] == 0x1C && id[1] == 0x2E && id[2] == 0x2F && id[3] == 0x2) {
      a = 7 ;
      Serial.println("num:7");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0xF1 && id[2] == 0x2E && id[3] == 0x2) {
      a = 8 ;
      Serial.println("num:8");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0x18 && id[2] == 0x2F && id[3] == 0x2) {
      a = 8 ;
      Serial.println("num:8");
      delay(1000);
    } else if (id[0] == 0x6C && id[1] == 0x1E && id[2] == 0x2F && id[3] == 0x2) {
      a = 8 ;
      Serial.println("num:8");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0x29 && id[2] == 0x2F && id[3] == 0x2) {
      a = 9 ;
      Serial.println("num:9");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xFA && id[2] == 0x2E && id[3] == 0x2) {
      a = 9 ;
      Serial.println("num:9");
      delay(1000);
    } else if (id[0] == 0x7C && id[1] == 0x10 && id[2] == 0x2F && id[3] == 0x2) {
      a =  9;
      Serial.println("num:9");
      delay(1000);
    } else if (id[0] == 0x3C && id[1] == 0x27 && id[2] == 0x2F && id[3] == 0x2) {
      a =  10;
      Serial.println("num:10");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0x6 && id[2] == 0x2F && id[3] == 0x2) {
      a = 10 ;
      Serial.println("num:10");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0x1 && id[2] == 0x2F && id[3] == 0x2) {
      a = 10 ;
      Serial.println("num:10");
      delay(1000);
    } else if (id[0] == 0x5C && id[1] == 0x1 && id[2] == 0x2F && id[3] == 0x2) {
      a = 11 ;
      Serial.println("num:11");
      delay(1000);
    } else if (id[0] == 0xAC && id[1] == 0x21 && id[2] == 0x2F && id[3] == 0x2) {
      a = 11 ;
      Serial.println("num:11");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0xF4 && id[2] == 0x2E && id[3] == 0x2) {
      a = 12 ;
      Serial.println("num:12");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0x16 && id[2] == 0x2F && id[3] == 0x2) {
      a = 13 ;
      Serial.println("num:13");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0x2A && id[2] == 0x2F && id[3] == 0x2) {
      a = 14 ;
      Serial.println("num:14");
      delay(1000);
    } else if (id[0] == 0x7C && id[1] == 0x2E && id[2] == 0x2F && id[3] == 0x2) {
      a = 15 ;
      Serial.println("num:15");
      delay(1000);
    } else if (id[0] == 0xAC && id[1] == 0x1B && id[2] == 0x2F && id[3] == 0x2) {
      a = 15 ;
      Serial.println("num:15");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0x2A && id[2] == 0x2F && id[3] == 0x2) {
      a = 16 ;
      Serial.println("num:16");
      delay(1000);
    } else if (id[0] == 0x3C && id[1] == 0xFF && id[2] == 0x2E && id[3] == 0x2) {
      a = 16 ;
      Serial.println("num:16");
      delay(1000);
    } else if (id[0] == 0xBC && id[1] == 0x3 && id[2] == 0x2F && id[3] == 0x2) {
      a = 17 ;
      Serial.println("num:17");
      delay(1000);
    } else if (id[0] == 0xCC && id[1] == 0x3 && id[2] == 0x2F && id[3] == 0x2) {
      a = 17 ;
      Serial.println("num:17");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0x0A && id[2] == 0x2F && id[3] == 0x2) {
      a = 18 ;
      Serial.println("num:18");
      delay(1000);
    } else if (id[0] == 0xAC && id[1] == 0x2 && id[2] == 0x2F && id[3] == 0x2) {
      a = 18 ;
      Serial.println("num:18");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xC3 && id[2] == 0x2E && id[3] == 0x02) {
      a = 19 ;
      Serial.println("num:19");
      delay(1000);
    } else if (id[0] == 0xAC && id[1] == 0x0B && id[2] == 0x2F && id[3] == 0x02) {
      a = 19 ;
      Serial.println("num:19");
      delay(1000);
    } else if (id[0] == 0x6C && id[1] == 0x0F && id[2] == 0x2F && id[3] == 0x2) {
      a = 19 ;
      Serial.println("num:19");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0x22 && id[2] == 0x2F && id[3] == 0x2) {
      a = 20 ;
      Serial.println("num:20");
      delay(1000);
    } else if (id[0] == 0x1C && id[1] == 0x8 && id[2] == 0x2F && id[3] == 0x2) {
      a = 20 ;
      Serial.println("num:20");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0x23 && id[2] == 0x2F && id[3] == 0x2) {
      a = 20 ;
      Serial.println("num:20");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0x0B && id[2] == 0x2F && id[3] == 0x2) {
      a = 21 ;
      Serial.println("num:21");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0x12 && id[2] == 0x2F && id[3] == 0x2) {
      a =  21;
      Serial.println("num:21");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0x2E && id[2] == 0x2F && id[3] == 0x2) {
      a =  21;
      Serial.println("num:21");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0xFB && id[2] == 0x2E && id[3] == 0x2) {
      a = 22 ;
      Serial.println("num:22");
      delay(1000);
    } else if (id[0] == 0xBC && id[1] == 0x5 && id[2] == 0x2F && id[3] == 0x2) {
      a = 22 ;
      Serial.println("num:22");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0x14 && id[2] == 0x2F && id[3] == 0x2) {
      a = 22 ;
      Serial.println("num:22");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0xF2 && id[2] == 0x2E && id[3] == 0x2) {
      a = 23 ;
      Serial.println("num:23");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0xF3 && id[2] == 0x2E && id[3] == 0x2) {
      a = 23 ;
      Serial.println("num:23");
      delay(1000);
    } else if (id[0] == 0x3C && id[1] == 0x1A && id[2] == 0x2F && id[3] == 0x2) {
      a = 24 ;
      Serial.println("num:24");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0xEC && id[2] == 0x2E && id[3] == 0x2) {
      a =  25;
      Serial.println("num:25");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0xFF && id[2] == 0x2E && id[3] == 0x2) {
      a =  26;
      Serial.println("num:26");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0x0D && id[2] == 0x2F && id[3] == 0x2) {
      a =  27;
      Serial.println("num:27");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0xF7 && id[2] == 0x2E && id[3] == 0x2) {
      a =  27;
      Serial.println("num:27");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0x4 && id[2] == 0x2F && id[3] == 0x2) {
      a =  28;
      Serial.println("num:28");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0x26 && id[2] == 0x2F && id[3] == 0x2) {
      a =  28;
      Serial.println("num:28");
      delay(1000);
    } else if (id[0] == 0x5C && id[1] == 0x1D && id[2] == 0x2F && id[3] == 0x2) {
      a =  29;
      Serial.println("num:29");
      delay(1000);
    } else if (id[0] == 0x1C && id[1] == 0x26 && id[2] == 0x2F && id[3] == 0x2) {
      a =  29;
      Serial.println("num:29");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0xBD && id[2] == 0x2E && id[3] == 0x2) {
      a =  30;
      Serial.println("num:30");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0xE7 && id[2] == 0x2E && id[3] == 0x2) {
      a =  30;
      Serial.println("num:30");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0xEE && id[2] == 0x2E && id[3] == 0x2) {
      a =  31;
      Serial.println("num:31");
      delay(1000);
    } else if (id[0] == 0x6C && id[1] == 0x2C && id[2] == 0x2F && id[3] == 0x2) {
      a = 31 ;
      Serial.println("num:31");
      delay(1000);
    } else if (id[0] == 0x7C && id[1] == 0x4 && id[2] == 0x2F && id[3] == 0x2) {
      a = 31 ;
      Serial.println("num:31");
      delay(1000);
    } else if (id[0] == 0x5C && id[1] == 0x0D && id[2] == 0x2F && id[3] == 0x2) {
      a = 32 ;
      Serial.println("num:32");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0x14 && id[2] == 0x2F && id[3] == 0x2) {
      a = 32 ;
      Serial.println("num:32");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xEE && id[2] == 0x2E && id[3] == 0x2) {
      a = 32 ;
      Serial.println("num:32");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0x8 && id[2] == 0x2F && id[3] == 0x2) {
      a = 33 ;
      Serial.println("num:33");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0xC4 && id[2] == 0x2E && id[3] == 0x2) {
      a = 33 ;
      Serial.println("num:33");
      delay(1000);
    } else if (id[0] == 0xDC && id[1] == 0xF7 && id[2] == 0x2E && id[3] == 0x2) {
      a = 33 ;
      Serial.println("num:33");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0xFD && id[2] == 0x2E && id[3] == 0x2) {
      a = 34 ;
      Serial.println("num:34");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0xA6 && id[2] == 0x2E && id[3] == 0x2) {
      a = 34 ;
      Serial.println("num:34");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0x1A && id[2] == 0x2F && id[3] == 0x2) {
      a = 34 ;
      Serial.println("num:34");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xEF && id[2] == 0x2E && id[3] == 0x2) {
      a = 35 ;
      Serial.println("num:35");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0xAC && id[2] == 0x2E && id[3] == 0x2) {
      a = 35 ;
      Serial.println("num:35");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xE8 && id[2] == 0x2E && id[3] == 0x2) {
      a = 36 ;
      Serial.println("num:36");
      delay(1000);
    } else if (id[0] == 0x1C && id[1] == 0xDA && id[2] == 0x2E && id[3] == 0x2) {
      a = 37 ;
      Serial.println("num:37");
      delay(1000);
    } else if (id[0] == 0xDC && id[1] == 0xD0 && id[2] == 0x2E && id[3] == 0x2) {
      a = 38 ;
      Serial.println("num:38");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0xE2 && id[2] == 0x2E && id[3] == 0x2) {
      a = 39 ;
      Serial.println("num:39");
      delay(1000);
    } else if (id[0] == 0xBC && id[1] == 0xB9 && id[2] == 0x2E && id[3] == 0x2) {
      a = 39 ;
      Serial.println("num:39");
      delay(1000);
    } else if (id[0] == 0x8C && id[1] == 0xC9 && id[2] == 0x2E && id[3] == 0x2) {
      a = 40 ;
      Serial.println("num:40");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0xD0 && id[2] == 0x2E && id[3] == 0x2) {
      a = 40 ;
      Serial.println("num:40");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0xC1 && id[2] == 0x2E && id[3] == 0x2) {
      a = 41 ;
      Serial.println("num:41");
      delay(1000);
    } else if (id[0] == 0x5C && id[1] == 0xDB && id[2] == 0x2E && id[3] == 0x2) {
      a = 41 ;
      Serial.println("num:41");
      delay(1000);
    } else if (id[0] == 0xEC && id[1] == 0xBB && id[2] == 0x2E && id[3] == 0x2) {
      a = 42 ;
      Serial.println("num:42");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0xB4 && id[2] == 0x2E && id[3] == 0x2) {
      a = 42 ;
      Serial.println("num:42");
      delay(1000);
    } else if (id[0] == 0xAC && id[1] == 0xCB && id[2] == 0x2E && id[3] == 0x2) {
      a = 43 ;
      Serial.println("num:43");
      delay(1000);
    } else if (id[0] == 0x7C && id[1] == 0xC9 && id[2] == 0x2E && id[3] == 0x2) {
      a = 43 ;
      Serial.println("num:43");
      delay(1000);
    } else if (id[0] == 0x4C && id[1] == 0xC8 && id[2] == 0x2E && id[3] == 0x2) {
      a = 43 ;
      Serial.println("num:43");
      delay(1000);
    } else if (id[0] == 0x1C && id[1] == 0xB2 && id[2] == 0x2E && id[3] == 0x2) {
      a = 44 ;
      Serial.println("num:44");
      delay(1000);
    } else if (id[0] == 0x2C && id[1] == 0xD9 && id[2] == 0x2E && id[3] == 0x2) {
      a = 44 ;
      Serial.println("num:44");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xDA && id[2] == 0x2E && id[3] == 0x2) {
      a = 44 ;
      Serial.println("num:44");
      delay(1000);
    } else if (id[0] == 0x0C && id[1] == 0xD8 && id[2] == 0x2E && id[3] == 0x2) {
      a = 45 ;
      Serial.println("num:45");
      delay(1000);
    } else if (id[0] == 0x1C && id[1] == 0xE2 && id[2] == 0x2E && id[3] == 0x2) {
      a = 45 ;
      Serial.println("num:45");
      delay(1000);
    } else if (id[0] == 0xFC && id[1] == 0xD1 && id[2] == 0x2E && id[3] == 0x2) {
      a =  45;
      Serial.println("num:45");
      delay(1000);
    } else if (id[0] == 0x6C && id[1] == 0xCA && id[2] == 0x2E && id[3] == 0x2) {
      a =  46;
      Serial.println("num:46");
      //        Serial.println(a);
      Serial.println("1");
      delay(1000);
    } else if (id[0] == 0x9C && id[1] == 0xCB && id[2] == 0x2E && id[3] == 0x2) {
      a =  46;
      Serial.println("num:46");

      delay(1000);
    } else if (id[0] == 0xCC && id[1] == 0xD7 && id[2] == 0x2E && id[3] == 0x2) {
      a =  46;
      Serial.println("num:46");
      Serial.println(a);
      delay(1000);
    } else if (id[0] == 0xBC && id[1] == 0xD2 && id[2] == 0x2E && id[3] == 0x2) {
      a =  47;
      Serial.println("num:47");
      delay(1000);
    } else if (id[0] == 0xCC && id[1] == 0xB9 && id[2] == 0x2E && id[3] == 0x2) {
      a = 47 ;
      Serial.println("num:47");
      delay(1000);
    } else if (id[0] == 0x3C && id[1] == 0xD9 && id[2] == 0x2E && id[3] == 0x2) {
      a = 48 ;
      Serial.println("num:48");
      delay(1000);
    } else {
      Serial.println("Hello unkown guy!");
    }
  }
}
void suanfa() {
  if (b1 != 0 && b2 != 0) {
    if (b1 < 10 && b2 < 10 && b1 < b2) {
      B1_win();
    } else if (b1 < 10 && b2 < 10 && b1 > b2) {
      B2_win();
    } else if (b1 < 10 && b2 < 10 && b1 == b2) {
      NO_win();
      //吃掉军棋的情况
    } else if (b1 == 12) {
      B2_win();
    } else if (b2 == 12) {
      B1_win();
      //炸弹的情况
    } else if (b1 == 11 || b2 == 11) {
      NO_win();
      //地雷的情况
    } else if (b1 == 10) {
      if (b2 == 9) {
        B2_win();
      } else if (b2 == 11) {
        NO_win();
      } else {
        B1_win();
      }
    } else if (b2 == 10) {
      if (b1 == 9) {
        B1_win();
      } else if (b1 == 11) {
        NO_win();
      } else {
        B2_win();
      }
    }
  }
  if (b1 != 0 && b3 != 0) {
    if (b1 < 10 && b3 < 10 && b1 < b3) {
      B1_win();
    } else if (b1 < 10 && b3 < 10 && b1 > b3) {
      B3_win();
    } else if (b1 < 10 && b3 < 10 && b1 == b3) {
      NO_win();
      //吃掉军棋的情况
    } else if (b1 == 12) {
      B3_win();
    } else if (b3 == 12) {
      B1_win();
      //炸弹的情况
    } else if (b1 == 11 || b3 == 11) {
      NO_win();
      //地雷的情况
    } else if (b1 == 10) {
      if (b3 == 9) {
        B3_win();
      } else if (b3 == 11) {
        NO_win();
      } else {
        B1_win();
      }
    } else if (b3 == 10) {
      if (b1 == 9) {
        B1_win();
      } else if (b1 == 11) {
        NO_win();
      } else {
        B3_win();
      }
    }
  }
  if (b1 != 0 && b4 != 0) {
    if (b1 < 10 && b4 < 10 && b1 < b4) {
      B1_win();
    } else if (b1 < 10 && b4 < 10 && b1 > b4) {
      B4_win();
    } else if (b1 < 10 && b4 < 10 && b1 == b4) {
      NO_win();
      //吃掉军棋的情况
    } else if (b1 == 12) {
      B4_win();
    } else if (b4 == 12) {
      B1_win();
      //炸弹的情况
    } else if (b1 == 11 || b4 == 11) {
      NO_win();
      //地雷的情况
    } else if (b1 == 10) {
      if (b4 == 9) {
        B4_win();
      } else if (b4 == 11) {
        NO_win();
      } else {
        B1_win();
      }
    } else if (b4 == 10) {
      if (b1 == 9) {
        B1_win();
      } else if (b1 == 11) {
        NO_win();
      } else {
        B4_win();
      }
    }
  }
  if (b2 != 0 && b4 != 0) {
    if (b2 < 10 && b4 < 10 && b2 < b4) {
      B2_win();
    } else if (b2 < 10 && b4 < 10 && b2 > b4) {
      B4_win();
    } else if (b2 < 10 && b4 < 10 && b2 == b4) {
      NO_win();
      //吃掉军棋的情况
    } else if (b2 == 12) {
      B4_win();
    } else if (b4 == 12) {
      B2_win();
      //炸弹的情况
    } else if (b2 == 11 || b4 == 11) {
      NO_win();
      //地雷的情况
    } else if (b2 == 10) {
      if (b4 == 9) {
        B4_win();
      } else if (b4 == 11) {
        NO_win();
      } else {
        B2_win();
      }
    } else if (b4 == 10) {
      if (b2 == 9) {
        B2_win();
      } else if (b2 == 11) {
        NO_win();
      } else {
        B4_win();
      }
    }
  }
  if (b2 != 0 && b3 != 0) {
    if (b2 < 10 && b3 < 10 && b2 < b3) {
      B2_win();
    } else if (b2 < 10 && b3 < 10 && b2 > b3) {
      B3_win();
    } else if (b2 < 10 && b3 < 10 && b2 == b3) {
      NO_win();
      //吃掉军棋的情况
    } else if (b2 == 12) {
      B3_win();
    } else if (b3 == 12) {
      B2_win();
      //炸弹的情况
    } else if (b2 == 11 || b3 == 11) {
      NO_win();
      //地雷的情况
    } else if (b2 == 10) {
      if (b3 == 9) {
        B3_win();
      } else if (b3 == 11) {
        NO_win();
      } else {
        B2_win();
      }
    } else if (b3 == 10) {
      if (b2 == 9) {
        B2_win();
      } else if (b2 == 11) {
        NO_win();
      } else {
        B3_win();
      }
    }
  }
  if (b4 != 0 && b3 != 0) {
    if (b4 < 10 && b3 < 10 && b4 < b3) {
      B4_win();
    } else if (b4 < 10 && b3 < 10 && b4 > b3) {
      B3_win();
    } else if (b4 < 10 && b3 < 10 && b4 == b3) {
      NO_win();
      //吃掉军棋的情况
    } else if (b4 == 12) {
      B3_win();
    } else if (b3 == 12) {
      B4_win();
      //炸弹的情况
    } else if (b4 == 11 || b3 == 11) {
      NO_win();
      //地雷的情况
    } else if (b4 == 10) {
      if (b3 == 9) {
        B3_win();
      } else if (b3 == 11) {
        NO_win();
      } else {
        B4_win();
      }
    } else if (b3 == 10) {
      if (b4 == 9) {
        B4_win();
      } else if (b4 == 11) {
        NO_win();
      } else {
        B3_win();
      }
    }
  }

}
void led(int LED_pin) {
  digitalWrite(LED_pin, HIGH);
  delay(500);
  digitalWrite(LED_pin, LOW);
}
void B1_win() {
  led(5);
  Serial.println("RED side win!红方胜");
  delay(500);
  reset_this_CPU();
}
void B2_win() {
  led(6);
  Serial.println("YELLOW side win!黄方胜");
  delay(500);
  reset_this_CPU();
}
void B3_win() {
  led(7);
  Serial.println("BLUE side win!蓝方胜");
  delay(500);
  reset_this_CPU();
}
void B4_win() {
  led(8);
  Serial.println("GREEN side win!绿方胜");
  delay(500);
  reset_this_CPU();
}

void NO_win() {
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  Serial.println("NO one win!双发出局");
  delay(500);
  reset_this_CPU();
}
/*
   Function：Write_MFRC5200
   Description：写一个字节的数据到一个登记的MR RC522
   Input parameter：addr--register address；val--the value that need to write in
   Return：Null
*/
void Write_MFRC522(uchar addr, uchar val)
{
  digitalWrite(chipSelectPin, LOW);

  //address format：0XXXXXX0
  SPI.transfer((addr << 1) & 0x7E);
  SPI.transfer(val);

  digitalWrite(chipSelectPin, HIGH);
}

/*
   Function：Read_MFRC522
   Description：读一个字节的数据到一个登记的MR RC522
   Input parameter：addr--register address
   Return：return the read value
*/
uchar Read_MFRC522(uchar addr)
{
  uchar val;

  digitalWrite(chipSelectPin, LOW);

  //地址形式：1XXXXXX0
  SPI.transfer(((addr << 1) & 0x7E) | 0x80);
  val = SPI.transfer(0x00);

  digitalWrite(chipSelectPin, HIGH);

  return val;
}

/*
   Function：SetBitMask
   Description：设置RC522寄存器位
   Input parameter：reg--register address;mask--value
   Return：null
*/
void SetBitMask(uchar reg, uchar mask)
{
  uchar tmp;
  tmp = Read_MFRC522(reg);
  Write_MFRC522(reg, tmp | mask); //设置掩码位
}


/*
   Function：ClearBitMask
   Description：清除RC522寄存器位
   Input parameter：reg--register address;mask--value
   Return：null
*/
void ClearBitMask(uchar reg, uchar mask)
{
  uchar tmp;
  tmp = Read_MFRC522(reg);
  Write_MFRC522(reg, tmp & (~mask)); //清除掩码
}

/*
   Function：AntennaOn
   Description：打开天线,每一次打开的天线所需要至少1ms
   Input parameter：null
   Return：null
*/
void AntennaOn(void)
{
  uchar temp;

  temp = Read_MFRC522(TxControlReg);
  if (!(temp & 0x03))
  {
    SetBitMask(TxControlReg, 0x03);
  }
}

void MFRC522_Reset(void)
{
  Write_MFRC522(CommandReg, PCD_RESETPHASE);        //重置RC522
}

/*
   Function：InitMFRC522
   Description：初始化RC522
   Input parameter：null
   Return：null
*/
void MFRC522_Init(void)
{
  digitalWrite(NRSTPD, HIGH);               //复位引脚

  MFRC522_Reset();                //重置RC522

  //定时器: TPrescaler*TreloadVal/6.78MHz = 24ms
  Write_MFRC522(TModeReg, 0x8D);            //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  Write_MFRC522(TPrescalerReg, 0x3E);        //TModeReg[3..0] + TPrescalerReg
  Write_MFRC522(TReloadRegL, 30);
  Write_MFRC522(TReloadRegH, 0);

  Write_MFRC522(TxAutoReg, 0x40);            //100%ASK
  Write_MFRC522(ModeReg, 0x3D);            //CRC效验值0x6363 ???

  //ClearBitMask(Status2Reg, 0x08); //MFCrypto1On=0
  //Write_MFRC522(RxSelReg, 0x86); //RxWait = RxSelReg[5..0]
  //Write_MFRC522(RFCfgReg, 0x7F); //RxGain = 48dB

  AntennaOn();                    //打开天线
}

/*
   Function：MFRC522_Request
   Description：搜寻卡,读取卡的类型
   Input parameter：reqMode--搜寻方法，
       TagType--返回卡的类型
       0x4400 = Mifare_UltraLight
       0x0400 = Mifare_One(S50)
       0x0200 = Mifare_One(S70)
       0x0800 = Mifare_Pro(X)
       0x4403 = Mifare_DESFire
   return：return MI_OK if successed
*/
uchar MFRC522_Request(uchar reqMode, uchar * TagType)
{
  uchar status;
  uint backBits;                                //接收到的数据比特

  Write_MFRC522(BitFramingReg, 0x07);         //TxLastBists = BitFramingReg[2..0] ???

  TagType[0] = reqMode;
  status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

  if ((status != MI_OK) || (backBits != 0x10))
  {
    status = MI_ERR;
  }

  return status;
}


uchar MFRC522_ToCard(uchar command, uchar * sendData, uchar sendLen, uchar * backData, uint * backLen)
{
  uchar status = MI_ERR;
  uchar irqEn = 0x00;
  uchar waitIRq = 0x00;
  uchar lastBits;
  uchar n;
  uint i;

  switch (command)
  {
    case PCD_AUTHENT:            //密码验证
      {
        irqEn = 0x12;
        waitIRq = 0x10;
        break;
      }
    case PCD_TRANSCEIVE:         //在FIFO发送数据
      {
        irqEn = 0x77;
        waitIRq = 0x30;
        break;
      }
    default:
      break;
  }

  Write_MFRC522(CommIEnReg, irqEn | 0x80);   //允许中断
  ClearBitMask(CommIrqReg, 0x80);            //清除所有的中断标志位
  SetBitMask(FIFOLevelReg, 0x80);         //FlushBuffer=1, FIFO 初始化大部分

  Write_MFRC522(CommandReg, PCD_IDLE); //没有行动;取消现在的命令

  //把数据持续写入FIFO
  for (i = 0; i < sendLen; i++)
  {
    Write_MFRC522(FIFODataReg, sendData[i]);
  }

  //进行下面
  Write_MFRC522(CommandReg, command);
  if (command == PCD_TRANSCEIVE)
  {
    SetBitMask(BitFramingReg, 0x80);     //StartSend=1,开始传送数据
  }

  //等待接收数据完成
  i = 2000;         //i 应根据时钟调整,等待的时间最大应该是25毫秒
  do
  {
    //CommIrqReg[7..0]
    //Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
    n = Read_MFRC522(CommIrqReg);
    i--;
  }
  while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

  ClearBitMask(BitFramingReg, 0x80); //StartSend=0

  if (i != 0)
  {
    if (!(Read_MFRC522(ErrorReg) & 0x1B)) //BufferOvfl Collerr CRCErr ProtecolErr
    {
      status = MI_OK;
      if (n & irqEn & 0x01)
      {
        status = MI_NOTAGERR; //??
      }

      if (command == PCD_TRANSCEIVE)
      {
        n = Read_MFRC522(FIFOLevelReg);
        lastBits = Read_MFRC522(ControlReg) & 0x07;
        if (lastBits)
        {
          *backLen = (n - 1) * 8 + lastBits;
        }
        else
        {
          *backLen = n * 8;
        }

        if (n == 0)
        {
          n = 1;
        }
        if (n > MAX_LEN)
        {
          n = MAX_LEN;
        }

        //读取FIFO数据
        for (i = 0; i < n; i++)
        {
          backData[i] = Read_MFRC522(FIFODataReg);
        }
      }
    }
    else
    {
      status = MI_ERR;
    }

  }

  //SetBitMask(ControlReg,0x80);            //关闭定时器
  //Write_MFRC522(CommandReg, PCD_IDLE);

  return status;
}


/*
   Function：MFRC522_Anticoll
   Description：防冲撞,读取卡的连续数据
   Input parameter：serNum--return the 4 bytes card serial number, the 5th byte is recheck byte
   return：return MI_OK if successed
*/
uchar MFRC522_Anticoll(uchar * serNum)
{
  uchar status;
  uchar i;
  uchar serNumCheck = 0;
  uint unLen;

  //ClearBitMask(Status2Reg, 0x08);     //strSensclear
  //ClearBitMask(CollReg,0x80);         //ValuesAfterColl
  Write_MFRC522(BitFramingReg, 0x00); //TxLastBists = BitFramingReg[2..0]

  serNum[0] = PICC_ANTICOLL;
  serNum[1] = 0x20;
  status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

  if (status == MI_OK)
  {
    //验证卡的连续数据
    for (i = 0; i < 4; i++)
    {
      serNumCheck ^= serNum[i];
    }
    if (serNumCheck != serNum[i])
    {
      status = MI_ERR;
    }
  }

  //SetBitMask(CollReg, 0x80);        //ValuesAfterColl=1

  return status;
}


/*
   Function：CalulateCRC
   Description：使用mf522计算CRC
   Input parameter：pIndata--the CRC data need to be read，len--data length，pOutData-- the caculated result of CRC
   return：Null
*/
void CalulateCRC(uchar * pIndata, uchar len, uchar * pOutData)
{
  uchar i, n;

  ClearBitMask(DivIrqReg, 0x04);         //CRCIrq = 0
  SetBitMask(FIFOLevelReg, 0x80);        //清除FIFO指针

  for (i = 0; i < len; i++)
  {
    Write_MFRC522(FIFODataReg, *(pIndata + i));
  }
  Write_MFRC522(CommandReg, PCD_CALCCRC);

  i = 0xFF;
  do
  {
    n = Read_MFRC522(DivIrqReg);
    i--;
  }
  while ((i != 0) && !(n & 0x04)); //CRCIrq = 1
  pOutData[0] = Read_MFRC522(CRCResultRegL);
  pOutData[1] = Read_MFRC522(CRCResultRegM);
}

uchar MFRC522_Write(uchar blockAddr, uchar * writeData)
{
  uchar status;
  uint recvBits;
  uchar i;
  uchar buff[18];

  buff[0] = PICC_WRITE;
  buff[1] = blockAddr;
  CalulateCRC(buff, 2, &buff[2]);
  status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

  if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
  {
    status = MI_ERR;
  }

  if (status == MI_OK)
  {
    for (i = 0; i < 16; i++) //16字节的数据写入到FIFO
    {
      buff[i] = *(writeData + i);
    }
    CalulateCRC(buff, 16, &buff[16]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {
      status = MI_ERR;
    }
  }

  return status;
}
