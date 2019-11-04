/****************************************************************************
* �� �� ��: main.c
* ��    ��: ��˼ͨ�� QQ:2357481431
* ��    վ: ��˾��վ: http://www.csgsm.com/  ����: https://csic.taobao.com/
* ��    ��: 2016-06-08
* ��    ��: 1.0
* ��    ��: �̵����ӿ�����P9�����ϣ�ʹ��P1.3�ڿ��Ƽ̵�������Ϣ�ˣ�ͨ��������������ѹ������������
*           �ߵ�ƽ�̵������ϣ� ���Ҽ̵�������ָʾ���� ; �͵�ƽ�̵����Ͽ���
****************************************************************************/
#include <ioCC2540.h>

#define uchar unsigned char
#define uint unsigned int

//#define DATA_PIN P1_3        //����P1.3����Ϊ�����
//relay init port ���Ŀ���
#define Coil_A {A=1;A1=0;B=0;B1=0;} //A1��ͨ�磬������ϵ�
#define Coil_B {A=0;A1=0;B=1;B1=0;} //B��ͨ�磬������ϵ�
#define Coil_A1 {A=0;A1=1;B=0;B1=0;} //A-��ͨ�磬������ϵ�
#define Coil_B1 {A=0;A1=0;B=0;B1=1;} //B-��ͨ�磬������ϵ�
#define Coil_OFF {A=0;A1=0;B=0;B1=0;} //ȫ���ϵ�

#define LED1 P1_0       //����P1.0��ΪLED1���ƶ�

#define A P0_0
#define A1 P0_2
#define B P0_4
#define B1 P0_6
#define Speed 500
/****************************************************************************
* ��    ��: DelayMs()
* ��    ��: �Ժ���Ϊ��λ��ʱ 16MʱԼΪ535,ϵͳʱ�Ӳ��޸�Ĭ��Ϊ16M
* ��ڲ���: msec ��ʱ������ֵԽ����ʱԽ��
* ���ڲ���: ��
****************************************************************************/
void DelayMs(uint len)
{ 
    while(len--)
        for (int i=0; i<535; i++);
}

//��ת
void Forward ()
{
    Coil_OFF;
    
    Coil_A               //����Coil_A1  ��{A1=1;B1=0;C1=0;D1=0;}����
    DelayMs(Speed);         //�ı�����������Ե������ת�� ,
                             //����ԽС��ת��Խ��,����ԽС
    Coil_B
    DelayMs(Speed);
    Coil_A1
    DelayMs(Speed);
    Coil_B1
    DelayMs(Speed);
  
}

//��ת
void Reverse ()
{
    Coil_OFF;
    
    Coil_B1                 //����Coil_A1  ��{A1=1;B1=0;C1=0;D1=0;}����
    DelayMs(Speed);         //�ı�����������Ե������ת�� ,
                             //����ԽС��ת��Խ��,����ԽС
    Coil_A1
    DelayMs(Speed);
    Coil_B
    DelayMs(Speed);
    Coil_A
    DelayMs(Speed);
}



void main(void)
{      
   // P1DIR |= 0x08;           //P1.3����Ϊ�����    
    P0DIR |= 0x55;//�����ĸ�����˿�
    uint i = 512;
    
    while(1)                 //��ѭ��,�̵������3�뿪��һ��
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
  if(i)//ͨ��
  {
    IN1 = 1;
    IN2 = 0;
  }
  else//�ص�
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