#include "Gazzali.h"

#define STM32F429_439xx
#include "stm32f4xx.h"


#define STM32F4XX_GPIO
#ifdef STM32F4XX_GPIO
static struct fileOperations GPIO;
static int GPIO_open(struct file *file)
{
	file->f_op=&GPIO;
	return 1;
}

static int GPIO_write(struct file *file, const char *buf, int count)
{
	RCC->AHB1ENR|=0x00000040;          // GPIOD donanımının clock sinyalini uygulayalım
	GPIOG->MODER=0x14000000;           // GPIOD nin 15, 14, 13, 12 pinleri cikis tanimlandi (Ledler bu pinlerde)
	GPIOG->OSPEEDR= 0xFFFFFFFF;        // GPIOD nin tum cikislari en yuksek hizda kullanacagiz
	GPIOG->ODR= 0x00006000;     // Ledler yansin

}

static int GPIO_read(struct file *file, char *buf, int count)
{

}

static struct fileOperations GPIO = {
	.read=GPIO_read,
	.write=GPIO_write,
	.open=GPIO_open
};


#endif

#ifdef USART

unsigned char WAdr,RAdr;
char RxBuf[128];

 
void SystemInit()
{
unsigned int i;
      (*((int*)0xE000ED88))|=0x0F00000;  
      for (i=0;i<0x00100000;i++);     // OSC oturtma ve kurtarma rutini
      RCC->CFGR |= 0x00009400;        // AHB ve APB hizlarini max degerlere set edelim
      RCC->CR |= 0x00010000;          // HSE Xtal osc calismaya baslasin        
      while (!(RCC->CR & 0x00020000));// Xtal osc stabil hale gelsin
      RCC->PLLCFGR = 0x07402A04;      // PLL katsayilarini M=4, N=168, P=2 ve Q=7 yapalim   168 Mhz 
      RCC->CR |= 0x01000000;          // PLL calismaya baslasin  (Rehber Sayfa 95)
      while(!(RCC->CR & 0x02000000)); // Pll hazir oluncaya kadar bekle
      FLASH->ACR = 0x00000605;        // Flash ROM icin 5 Wait state secelim ve ART yi aktif edelim (Rehber Sayfa 55)
      RCC->CFGR |= 0x00000002;        // Sistem Clk u PLL uzerinden besleyelim
      while ((RCC->CFGR & 0x0000000F) != 0x0000000A); // Besleninceye kadar bekle
      RCC->AHB1ENR |= 0x0000001F;     // GPIO A,B,C,D,E clock'u aktif edelim 
      GPIOD->MODER  = 0x55550000;     // GPIOD nin 15, 14, 13, 12, 11, 10, 9, 8 pinleri cikis tanimlandi (LEDler icin)
      GPIOD->OSPEEDR= 0xFFFFFFFF;     // GPIOD nin tum cikislari en yuksek hizda kullanacagiz 
} 

 
void USART3_IRQHandler()
{
volatile int Sts;
     Sts=USART3->SR;
     RxBuf[WAdr]=USART3->DR;
     WAdr=(WAdr+1)&0x7F;
}
 
void UsartInit()
{
     WAdr=0;RAdr=0;
 
// USART3 MODULUNU AKTIF HALE GETIRELIM
 
      RCC->APB1ENR|=0x00040000;  // USART3 Clk Enable (Rehber Sayfa 113)
      RCC->APB1RSTR|=0x00040000;  // USART3 Resetlendi
      GPIOB->AFR[1]=0x07777700;  // PB10..PB14 pinleri USART3 ile alakalandirildi (Hard Sayfa 49)
      GPIOB->MODER|=0x2AA00000;  // GPIOB 10..14 icin alternatif fonksiyon tanimi (Rehber Sayfa 148)
 
// USART3 MODULUNU AYARLAYALIM  // 1 Start, 8 Data, 1 Stop, No parity (Default degerler)
 
      RCC->APB1RSTR&=~0x00040000;  // USART3 Reseti kaldiralim
//      USART3->SR&=~0X03FF;   // Status registeri silelim
      USART3->BRR=0X1112;    // 9600 Baud
 
      USART3->CR1|=0x0000202C;  // USART3 enable
      NVIC->ISER[1]|=0x80;         // NVIC da USART3 interrupta izin verelim
}
 
void SendChar(char Tx) 
{
      while(!(USART3->SR&0x80));  // TX Buffer dolu ise bekle (Rehber Sayfa 646)
      USART3->DR=Tx;
}
 
void SendTxt(char *Adr)
{
      while(*Adr) 
        {
          SendChar(*Adr);
          Adr++;
        }  
}
 
char DataReady()
{
       return(WAdr-RAdr);
} 
 
char ReadChar()
{
char Dat;
    
      Dat=RxBuf[RAdr];
      RAdr=(RAdr+1)&0x7F;
      return(Dat);
}
 
// Rx ve TX pinlerini (GPIOB10 ve GPIOB11) birbirine baglarsaniz gonderdiginiz datalar geri gelecektir
 
static struct fileOperations uart= {
		.read=uart_read,
}
#endif

void stm32_init ()
{
	dev_register(4,&GPIO);
	dev_t aygit = {.major=4,.minor=0};
	char deneme[]="HelloWorld";
	struct file * f= dev_open(aygit);
	if(f) f->f_op->write(f,deneme,5);
}

