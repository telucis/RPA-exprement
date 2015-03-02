#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define ALS  XBYTE[0x4000]
#define AMS  XBYTE[0x4001]
#define adstart XBYTE[0x8000]
#define adouth XBYTE[0X8002]
#define adoutl XBYTE[0x8003]

uint receivedata;
uint SendFlag;

sbit RS485=P1^0;   //定义485的使能脚
sbit LED=P1^1;
sbit dog=P1^2;

//sbit LDAC=P3^5;
uint scan_enable;

uint temp1=0x0000;
uint temp2=0x0000;
uint second=0;
uint t0t1=0;
uint t0t2=0;
uint i=0;

uint addatah;
uint addatal;
uint zjs=0;

void adsample()
{
uchar temp,i;
for(i=0;i<25;i=i+1)
{
   ;
}
adstart=0x00;  //通过写IO使得写信号有效，写时WR变低，AD片子的使能端有效，同时A0=0,AD转换开始,使ADCS有效,AD的CE信号有效
for(i=0;i<25;i=i+1)
{
   ;       //等待AD转换完成
}

addatah=adouth;
addatal=adoutl; //只是对数据总线进行操作，同时A0=1，A/D片子数据
addatal=addatal/16;
//addatal=addatal&0x0f;


}

void send(uint meg)
{
	RS485=1;
    SBUF=meg;
    while(TI==0);      //等待发送完毕
    TI=0;
	RS485=0;
}

void time()
{
	/*if(i%10==0 & i<1000)
	{
		h506=0x00;			//MS
		adsample();
		send(addatah);
		send(addatal);
	}*/
	if(i<250)
	{
		i=i+1;
	}
	else
	{
		i=0;
		second =second +1;
	}
}

void RPA_scan_8()
{
		LED=0;

       if(t0t2<2000)
       {
			if(temp1!=0xFA)
			{
			 ALS=temp1;
			 AMS=temp2;
			 temp1=temp1+2;
			}
			else
			{
			 ALS=temp1;
			 AMS=temp2;
			 temp1=0x00;
			 temp2=temp2+1;
			}
			adsample();
			send(addatah);
			send(addatal);
			t0t2=t0t2+1;
       }
       else
       {
        t0t2=0;
		temp1=0;
        temp2=0;
        ALS=0x00;                        //分层值0.0024414
        AMS=0x00;
		second = second +1;
       }
}
/*
void RPA_scan_10()
{
		LED=0;

       if(t0t2<1000)
       {
			if(t0t2%5==0)
			{
				adsample();
				send(addatah);
				send(addatal);				
				if(temp1!=0xF0)
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=temp1+20;
				}
				else
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=0x00;
				 temp2=temp2+1;
				}
			}
       }
       else
       {
        t0t2=0;
		temp1=0;
        temp2=0;
        ALS=0x00;                        //分层值0.0024414
        AMS=0x00;
		second = second +1;
       }
       t0t2=t0t2+1;

}

void RPA_scan_12()
{
		LED=0;

       if(t0t2<1200)
       {
			if(t0t2%6==0)
			{
				adsample();
				send(addatah);
				send(addatal);
				if(temp1!=0xF0)
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=temp1+20;
				}
				else
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=0x00;
				 temp2=temp2+1;
				}
			}
       }
       else
       {
        t0t2=0;
		temp1=0;
        temp2=0;
        ALS=0x00;                        //分层值0.0024414
        AMS=0x00;
		second = second +1;
       }
       t0t2=t0t2+1;

}

void RPA_scan_14()
{
		LED=0;

       if(t0t2<1400)
       {
			if(t0t2%7==0)
			{
				adsample();
				send(addatah);
				send(addatal);				
				if(temp1!=0xF0)
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=temp1+20;
				}
				else
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=0x00;
				 temp2=temp2+1;
				}
			}
       }
       else
       {
        t0t2=0;
		temp1=0;
        temp2=0;
        ALS=0x00;                        //分层值0.0024414
        AMS=0x00;
		second = second +1;
       }
       t0t2=t0t2+1;

}

void RPA_scan_16()
{
		LED=0;

       if(t0t2<1600)
       {
			if(t0t2%8==0)
			{
				adsample();
				send(addatah);
				send(addatal);				
				if(temp1!=0xF0)
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=temp1+20;
				}
				else
				{
				 ALS=temp1;
				 AMS=temp2;
				 temp1=0x00;
				 temp2=temp2+1;
				}
			}
       }
       else
       {
        t0t2=0;
		temp1=0;
        temp2=0;
        ALS=0x00;                        //分层值0.0024414
        AMS=0x00;
		second = second +1;
       }
       t0t2=t0t2+1;

}
*/

void ini_serial(void)
{
   TMOD=TMOD&0x0f;
   TMOD=TMOD|0x20;   //方式2
   TH1=0xff;         //bps 4800
   TL1=0xff;
   //SCON=0x50;
   SM0=0;
   SM1=1;
   REN=1;
   PCON=0x80;
   TR1=1;        //定时器运行控制位，T1开始计时
}

void service_series() interrupt 4 using 2
{

 if(RI==1)
 {
  RI=0;
  receivedata=SBUF;
//  SendFlag=0;
  switch(receivedata)
  {
        case 0x01:
             scan_enable=1;
			 temp1=0;
			 temp2=0;
			 zjs=0;
             break;
		case 0x02:
             scan_enable=2;
			 temp1=0;
			 temp2=0;
			 zjs=0;
             break;
		case 0x03:
             scan_enable=3;
			 temp1=0;
			 temp2=0;
			 zjs=0;
             break;
		case 0x04:
             scan_enable=4;
			 temp1=0;
			 temp2=0;
			 zjs=0;
             break;
		case 0x05:
             scan_enable=5;
			 temp1=0;
			 temp2=0;
			 zjs=0;
             break;
        case 0x00:
             scan_enable=0;
             break;
  }
 }

}


void service_timer0() interrupt 1 using 2
{
	ET0=0;
	TH0=0xE3;                    //4ms  方式2，8位定时器，定时器0为采样设置
    TL0=0x33;
	if (scan_enable==1)
	{
		if (second==0)
		{
			LED=1;
			time();
		}
		else if(second==1)
		{
			RPA_scan_8();
		}
		else
		{
			LED=1;
			send(zjs);
			zjs=zjs+1;
			second=0;
			t0t1=0;
			t0t2=0;
		}
	}

	else if (scan_enable==2)
	{
		if (second==0)
		{
			LED=1;
			time();
		}
		else if(second==1)
		{
			RPA_scan_10();
		}
		else
		{
			LED=1;
			send(zjs);
			zjs=zjs+1;
			second=0;
			t0t1=0;
			t0t2=0;
		}
	}

	else if (scan_enable==3)
	{
		if (second==0)
		{
			LED=1;
			time();
		}
		else if(second==1)
		{
			RPA_scan_12();
		}
		else
		{
			LED=1;
			send(zjs);
			zjs=zjs+1;
			second=0;
			t0t1=0;
			t0t2=0;
		}
	}

	else if (scan_enable==4)
	{
		if (second==0)
		{
			LED=1;
			time();
		}
		else if(second==1)
		{
			RPA_scan_14();
		}
		else
		{
			LED=1;
			send(zjs);
			zjs=zjs+1;
			second=0;
			t0t1=0;
			t0t2=0;
		}
	}

	else if (scan_enable==5)
	{
		if (second==0)
		{
			LED=1;
			time();
		}
		else if(second==1)
		{
			RPA_scan_16();
		}
		else
		{
			LED=1;
			send(zjs);
			zjs=zjs+1;
			second=0;
			t0t1=0;
			t0t2=0;
		}
	}

	else if (scan_enable==0)
	{
		LED=1;
		temp1=0x00;
		temp2=0x00;
		ALS=temp1;
        AMS=temp2;
		t0t1=0;
		t0t2=0;
		second=0;
	}
	ET0=1;
}


main()
{
        EA=1;
        ES=1;
        TMOD=TMOD&0xf0;
        TMOD=TMOD|0x01;
        TH0=0xE3;                   //1ms  方式2，8位定时器，定时器0为采样设置
        TL0=0x33;

        ini_serial();
        ET0=1;
        TR0=1;
        ALS=0x00;
        AMS=0x00;
//        LDAC=0;
        while(1)
        {
			RS485=0;	      //接收状态

	    }
}
