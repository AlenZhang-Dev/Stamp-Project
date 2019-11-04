/****************************************************************************
* 文 件 名: main.c
* 作    者: 创思通信 QQ:2357481431
* 网    站: 公司网站: http://www.csgsm.com/  店铺: https://csic.taobao.com/
* 修    订: 2016-06-08
* 版    本: 1.0
* 描    述: 继电器接开发板P9座子上，使用P1.3口控制继电器的信息端，通过三极管提升电压并反相驱动。
*           高电平继电器吸合， 并且继电器吸合指示灯亮 ; 低电平继电器断开，
****************************************************************************/
#include <ioCC2540.h>

#define uchar unsigned char
#define uint unsigned int

//#define DATA_PIN P1_3        //定义P1.3定义为输入口
//relay init port 四拍控制
#define Coil_A {A=1;A1=0;B=0;B1=0;} //A1相通电，其他相断电
#define Coil_B {A=0;A1=0;B=1;B1=0;} //B相通电，其他相断电
#define Coil_A1 {A=0;A1=1;B=0;B1=0;} //A-相通电，其他相断电
#define Coil_B1 {A=0;A1=0;B=0;B1=1;} //B-相通电，其他相断电
#define Coil_OFF {A=0;A1=0;B=0;B1=0;} //全部断电

#define LED1 P1_0       //定义P1.0口为LED1控制端

#define A P0_0
#define A1 P0_2
#define B P0_4
#define B1 P0_6
#define Speed 500
/****************************************************************************
* 名    称: DelayMs()
* 功    能: 以毫秒为单位延时 16M时约为535,系统时钟不修改默认为16M
* 入口参数: msec 延时参数，值越大，延时越久
* 出口参数: 无
****************************************************************************/
void DelayMs(uint len)
{ 
    while(len--)
        for (int i=0; i<535; i++);
}

//正转
void Forward ()
{
    Coil_OFF;
    
    Coil_A               //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
    DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
                             //数字越小，转速越大,力矩越小
    Coil_B
    DelayMs(Speed);
    Coil_A1
    DelayMs(Speed);
    Coil_B1
    DelayMs(Speed);
  
}

//反转
void Reverse ()
{
    Coil_OFF;
    
    Coil_B1                 //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
    DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
                             //数字越小，转速越大,力矩越小
    Coil_A1
    DelayMs(Speed);
    Coil_B
    DelayMs(Speed);
    Coil_A
    DelayMs(Speed);
}



void main(void)
{      
   // P1DIR |= 0x08;           //P1.3定义为输出口    
    P0DIR |= 0x55;//开启四个输出端口
    uint i = 512;
    
    while(1)                 //死循环,继电器间隔3秒开关一次
    {
    // while(i--)
     //{
      //  Forward();
      //}
      //i = 512;
      while(i--)
      {
        Reverse();
      }
      i = 512;
    }    
}



/**
void direct1(int i)
{
  if(i)//通电
  {
    IN1 = 1;
    IN2 = 0;
  }
  else//关电
  {
    IN1 = 0;
    IN2 = 0;
  }
}

void direct2(int i)
{
 if(i)
 {
  IN3 = 1;
  IN4 = 1;
 }
 else
 {
   IN3 = 0;
   IN4 = 0;
 }
}
*/