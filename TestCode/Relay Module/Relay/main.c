/****************************************************************************
* 文 件 名: main.c
* 作    者: 创思通信 QQ:2357481431
* 网    站: 公司网站: http://www.csgsm.com/  店铺: https://csic.taobao.com/
* 修    订: 2016-06-08
* 版    本: 1.0
* 描    述: 继电器接开发板P9座子上，使用P1.3口控制继电器的信息端，通过三极管提升电压并反相驱动。
*           高电平继电器吸合， 并且继电器吸合指示灯亮 ; 低电平继电器断开，
*四拍控制: A-B-A1-B1-A
*八拍控制：A-AB-B-A1B-A1-A1B1-B1-AB1-A

*剩余功能设计：
*1.确定遮挡与否走的时间
*Extra:传递确定其位置的变量，需要通过别的传感器配合确定滑台的位置。
****************************************************************************/
#include <ioCC2540.h>

#define uchar unsigned char
#define uint unsigned int

//#define DATA_PIN P1_3        //定义P1.3定义为输入口
//relay init port 四拍控制
#define Coil_A {A=1;A1=0;B=0;B1=0;} //A相通电，其他相断电
#define Coil_B {A=0;A1=0;B=1;B1=0;} //B相通电，其他相断电
#define Coil_A1 {A=0;A1=1;B=0;B1=0;} //A-相通电，其他相断电
#define Coil_B1 {A=0;A1=0;B=0;B1=1;} //B-相通电，其他相断电
//八拍控制
#define Coil_AB {A=1;A1=0;B=1;B1=0;} //AB相通电
#define Coil_A1B {A=0;A1=1;B=1;B1=0;}//A-B相通电
#define Coil_A1B1 {A=0;A1=1;B=0;B1=1;}//A-B-相通电
#define Coil_AB1 {A=1;A1=0;B=0;B1=1;}//AB-相通电
#define Coil_OFF {A=0;A1=0;B=0;B1=0;} //全部断电

#define LED1 P1_0       //定义P1.0口为LED1控制端
#define LED2 P1_1


//确定四个没有重用功能的I/O
#define A P0_0
#define A1 P0_2
#define B P0_4
#define B1 P0_6

/////////////////****function****//////////////////////
unsigned char Speed;
/****************************************************************************
* 名    称: DelayMs()
* 功    能: 以毫秒为单位延时 16M时约为535,系统时钟不修改默认为16M
* 入口参数: msec 延时参数，值越大，延时越久
* 出口参数: 无
****************************************************************************/
//void DelayMs(uint len)
//{ 
//   while(len--)
//        for (int i=0; i<535; i++);
//}


unsigned char Speed;
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
//为啥为Us2x
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

///////四拍测试节奏
//正转
void Forward_Four ()
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
void Reverse_Four ()
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


/*
8拍测试
A-AB-B-A1B-A1-A1B1-B1-AB1-A
*/
void Forward_Eight ()
{
    Coil_OFF;
    
    Coil_A               //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
        DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
                             //数字越小，转速越大,力矩越小
    Coil_AB
       DelayMs(Speed);
    Coil_B
        DelayMs(Speed);
    Coli_A1B
        DelayMs(Speed);
    Coil_A1
        DelayMs(Speed);
    Coil_A1B1
        Delay_Ms(Speed);
    Coil_B1
        DelayMs(Speed);
    Coil_AB1
        Delay_Ms(Speed);
  
}

void Reverse_Eight ()
{
    Coil_OFF;
    
    Coil_AB1
       DelayMs(Speed); 
    Coil_B1
       DelayMs(Speed); 
    Coil_A1B1
      DelayMs(Speed); 
    Coil_A1
       DelayMs(Speed); 
    Coil_A1B
       DelayMs(Speed); 
    Coil_B
       DelayMs(Speed); 
    Coil_AB
       DelayMs(Speed); 
    Coil_A
       DelayMs(Speed); 
}

//遮挡函数设计，所需参数：确定循环内运行时间
//假设正转为遮挡
void Shade ( int Times)
{
  while(Times--)
  {
    //DelayMs()
    Reverse_Eight();
  }
}

void Open (int Times)
{
  while(Times--)
  {
    Forward_Eight();
  }
}

void main(void)
{      
   // P1DIR |= 0x08;           //P1.3定义为输出口    
    P0DIR |= 0x55;//开启四个输出端口
   // uint i = 512;
    Speed = 3;
    Coil_OFF
      
  while(1)//反向
  {
     Coil_A              //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
     DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
	                         //数字越小，转速越大,力矩越小
     Coil_B
     DelayMs(Speed);
     Coil_A1
     DelayMs(Speed);
     Coil_B1
     DelayMs(Speed);
     Coil_OFF
     DelayMs(Speed);
  }
}



  
/**
  Coil_OFF
  i=512;
  while(i--)//反向
  {
     Coil_B1                //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
     DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
	                         //数字越小，转速越大,力矩越小
     Coil_A1
     DelayMs(Speed);
     Coil_B
     DelayMs(Speed);
     Coil_A
     DelayMs(Speed);
  }   
}
*/