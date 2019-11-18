/****************************************************************************
* �� �� ��: main.c
* ��    ��: ��˼ͨ�� QQ:2357481431
* ��    վ: ��˾��վ: http://www.csgsm.com/  ����: https://csic.taobao.com/
* ��    ��: 2016-06-08
* ��    ��: 1.0
* ��    ��: �̵����ӿ�����P9�����ϣ�ʹ��P1.3�ڿ��Ƽ̵�������Ϣ�ˣ�ͨ��������������ѹ������������
*           �ߵ�ƽ�̵������ϣ� ���Ҽ̵�������ָʾ���� ; �͵�ƽ�̵����Ͽ���
*���Ŀ���: A-B-A1-B1-A
*���Ŀ��ƣ�A-AB-B-A1B-A1-A1B1-B1-AB1-A

*ʣ�๦����ƣ�
*1.ȷ���ڵ�����ߵ�ʱ��
*Extra:����ȷ����λ�õı�������Ҫͨ����Ĵ��������ȷ����̨��λ�á�
****************************************************************************/
#include <ioCC2540.h>

#define uchar unsigned char
#define uint unsigned int

//#define DATA_PIN P1_3        //����P1.3����Ϊ�����
//relay init port ���Ŀ���
#define Coil_A {A=1;A1=0;B=0;B1=0;} //A��ͨ�磬������ϵ�
#define Coil_B {A=0;A1=0;B=1;B1=0;} //B��ͨ�磬������ϵ�
#define Coil_A1 {A=0;A1=1;B=0;B1=0;} //A-��ͨ�磬������ϵ�
#define Coil_B1 {A=0;A1=0;B=0;B1=1;} //B-��ͨ�磬������ϵ�
//���Ŀ���
#define Coil_AB {A=1;A1=0;B=1;B1=0;} //AB��ͨ��
#define Coil_A1B {A=0;A1=1;B=1;B1=0;}//A-B��ͨ��
#define Coil_A1B1 {A=0;A1=1;B=0;B1=1;}//A-B-��ͨ��
#define Coil_AB1 {A=1;A1=0;B=0;B1=1;}//AB-��ͨ��
#define Coil_OFF {A=0;A1=0;B=0;B1=0;} //ȫ���ϵ�

#define LED1 P1_0       //����P1.0��ΪLED1���ƶ�
#define LED2 P1_1


//ȷ���ĸ�û�����ù��ܵ�I/O
#define A P0_0
#define A1 P0_2
#define B P0_4
#define B1 P0_6

/////////////////****function****//////////////////////
unsigned char Speed;
/****************************************************************************
* ��    ��: DelayMs()
* ��    ��: �Ժ���Ϊ��λ��ʱ 16MʱԼΪ535,ϵͳʱ�Ӳ��޸�Ĭ��Ϊ16M
* ��ڲ���: msec ��ʱ������ֵԽ����ʱԽ��
* ���ڲ���: ��
****************************************************************************/
//void DelayMs(uint len)
//{ 
//   while(len--)
//        for (int i=0; i<535; i++);
//}


unsigned char Speed;
/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
//ΪɶΪUs2x
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

///////���Ĳ��Խ���
//��ת
void Forward_Four ()
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
void Reverse_Four ()
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


/*
8�Ĳ���
A-AB-B-A1B-A1-A1B1-B1-AB1-A
*/
void Forward_Eight ()
{
    Coil_OFF;
    
    Coil_A               //����Coil_A1  ��{A1=1;B1=0;C1=0;D1=0;}����
        DelayMs(Speed);         //�ı�����������Ե������ת�� ,
                             //����ԽС��ת��Խ��,����ԽС
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

//�ڵ�������ƣ����������ȷ��ѭ��������ʱ��
//������תΪ�ڵ�
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
   // P1DIR |= 0x08;           //P1.3����Ϊ�����    
    P0DIR |= 0x55;//�����ĸ�����˿�
   // uint i = 512;
    Speed = 3;
    Coil_OFF
      
  while(1)//����
  {
     Coil_A              //����Coil_A1  ��{A1=1;B1=0;C1=0;D1=0;}����
     DelayMs(Speed);         //�ı�����������Ե������ת�� ,
	                         //����ԽС��ת��Խ��,����ԽС
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
  while(i--)//����
  {
     Coil_B1                //����Coil_A1  ��{A1=1;B1=0;C1=0;D1=0;}����
     DelayMs(Speed);         //�ı�����������Ե������ת�� ,
	                         //����ԽС��ת��Խ��,����ԽС
     Coil_A1
     DelayMs(Speed);
     Coil_B
     DelayMs(Speed);
     Coil_A
     DelayMs(Speed);
  }   
}
*/