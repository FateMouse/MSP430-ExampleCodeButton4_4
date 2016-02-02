/*#include  <msp430x14x.h>

unsigned char key_value;

void Keyget(void)
{
   unsigned char key_temp1,key_temp2;
   unsigned char i;
   key_temp1=0x10;
   for(i=0;i<4;i++)
   {

     P5OUT=0xf0&(~key_temp1);          // 对应的IO 输出低电平
     key_temp1<<=1;
     key_temp2=P5IN&0x0f;             // 读取P50~P5.3 的电平，低电平有按键按下；
     switch(key_temp2)
     {
       case 0x0e:
                  key_value=0x01+key_temp1;
                  P4OUT=~(0x01+key_temp1);      // LED 指示灯指示键值
                  break;
       case 0x0d:
                  key_value=0x02+key_temp1;
                  P4OUT=~(0x02+key_temp1);
                  break;
       case 0x0b:
                  key_value=0x04+key_temp1;
                  P4OUT=~(0x04+key_temp1);
                  break;
       case 0x07:
                  key_value=0x08+key_temp1;
                  P4OUT=~(0x08+key_temp1);
                  break;
       default:break;
     }
   }
}

void main( void )
{
                               // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P4DIR=0xff;
  P4SEL=0;
  P4OUT=0xff;                   //LED 指示
  
  P5DIR=(P5DIR&0x00)|0xf0;      // P5.4~P5.7 为输出口  P5.0~P5.3 为输入口
  P5OUT=0xf0;                   //初始化输出高电平
  
  while(1)
  {
     Keyget();                  // 按键扫描
  }
   
}*/
#include<msp430x14x.h>

#define uchar unsigned char
#define uint  unsigned int

uchar key_scan(void)
{
  uchar key_v=0,key=0;
  P5DIR = 0x10;
  if((P5IN&0x0f)!=0x0f)
  {
    for(uint x=100;x;x--);
    if((P5IN&0x0f)!=0x0f)
    {
      key_v=P5IN&0x0f;
      switch(key_v)
      {
        case 0x0e:return key=0;
        case 0x0d:return key=4;
        case 0x0b:return key=8;
        case 0x07:return key=12;
      }
    }
  }
  P5DIR = 0x20;
  if((P5IN&0x0f)!=0x0f)
  {
    for(uint x=100;x;x--);
    if((P5IN&0x0f)!=0x0f)
    {
      key_v=P5IN&0x0f;
      switch(key_v)
      {
        case 0x0e:return key=1;
        case 0x0d:return key=5;
        case 0x0b:return key=9;
        case 0x07:return key=13;
      }
    }
  }

  P5DIR = 0x40;
  if((P5IN&0x0f)!=0x0f)
  {
    for(uint x=100;x;x--);
    if((P5IN&0x0f)!=0x0f)
    {
      key_v=P5IN&0x0f;
      switch(key_v)
      {
        case 0x0e:return key=2;
        case 0x0d:return key=6;
        case 0x0b:return key=10;
        case 0x07:return key=14;
      }
    }
  }

  P5DIR = 0x80;
  if((P5IN&0x0f)!=0x0f)
  {
    for(uint x=100;x;x--);
    if((P5IN&0x0f)!=0x0f)
    {
      key_v=P5IN&0x0f;
      switch(key_v)
      {
        case 0x0e:return key=3;
        case 0x0d:return key=7;
        case 0x0b:return key=11;
        case 0x07:return key=15;
      }
    }
  }
  if((P5IN&0x0f)==0x0f)
  {
       for(uint x=100;x;x--);
       if((P5IN&0x0f)==0x0f)
       return key=100;
  }
  return key;
}

void main(void)
{
  uchar x=0;
  WDTCTL = WDTPW+WDTHOLD;
  P4DIR=0xff;
  P4OUT=0xff;
  P5OUT=0x00;  
  for(;;)
  {
    if((x=key_scan())!=100)
    {
       P4OUT=~x;
    }
  }
}