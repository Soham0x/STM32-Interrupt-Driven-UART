#include "main.h" // or #include "stm32c0xx.h"
#include "UART.h"
#define SIZE 100
#define NVIC_ISER *((volatile uint32_t*)0xE000E100)



 struct BUFFER {
  uint8_t DATA[SIZE];
  uint8_t HEAD;
  uint8_t TAIL;
  uint8_t CAPC;
  uint8_t overflow;
  
  
};
struct BUFFER1 {
  uint8_t DATA1[SIZE];
  uint8_t HEAD1;
  uint8_t TAIL1;
  uint8_t CAPC1;

  
  
};

volatile struct BUFFER a={.HEAD=0, .TAIL=0,.CAPC=100};
volatile struct BUFFER1 b={.HEAD1=0,.TAIL1=0,.CAPC1=100};

 
 
void UARTNT(uint32_t a, uint32_t b, uint16_t c){
    // 1. Enable the clock for GPIO Port A
    RCC->IOPENR |= (1 << 0); 
    
    // 2. Set PA9 and PA10 to Alternate Function mode (binary 10)
    GPIOA->MODER &= ~((3 << 18) | (3 << 20)); 
    GPIOA->MODER |= ((2 << 18) | (2 << 20));  
    
    // 3. Select AF1 (USART1) for PA9 and PA10 in the High Register (AFRH / AFR[1])
    GPIOA->AFR[1] &= ~((0xF << 4) | (0xF << 8)); 
    GPIOA->AFR[1] |= ((1 << 4) | (1 << 8));      
    
    // 4. USART Configuration
    USART1->CR1 = 0; // DISABLE USART first so hardware unlocks BRR
    USART1->BRR = c; // data transmission rate
    USART1->CR2 = b; // stop bits
    USART1->CR1 = a; // word length, data bits, UART tx and rx enable
    
    // 5. Enable RX Interrupt and NVIC
    USART1->CR1 |= (1<<5); // RX INTERRUPT ENABLE 
    NVIC_EnableIRQ(USART1_IRQn); // allows usart 1 interrupt
}

void UARTTX (char * z){

 while (*z!='\0'){
b.DATA1[b.HEAD1]=*z;
b.HEAD1=(b.HEAD1 + 1) % b.CAPC1;
 z++;
}
 USART1->CR1|=(1<<7);//TX Interrupt Enable;

}



uint8_t UARTRX( uint8_t *s){
if(a.TAIL==a.HEAD){
  return 0;
}
*s=a.DATA[a.TAIL];
a.TAIL=(a.TAIL+1) % a.CAPC;
s++;
return 1;
}



void USART1_IRQHandler(void){
if( (USART1->CR1 & USART_CR1_RXNEIE_RXFNEIE) && (USART1->ISR & USART_ISR_RXNE_RXFNE)){
 uint8_t nexth;
 nexth=(a.HEAD+1) % a.CAPC;
 if(nexth!=a.TAIL){
 a.DATA[a.HEAD]=USART1->RDR;
 a.HEAD=nexth;
 }
 else{
  a.overflow+=1;
 }
}
if((USART1->CR1 & USART_CR1_TXEIE_TXFNFIE) && (USART1->ISR & USART_ISR_TXE_TXFNF)){
if(b.TAIL1!=b.HEAD1){
USART1->TDR=b.DATA1[b.TAIL1];
b.TAIL1=(b.TAIL1 + 1) % b.CAPC1;
}
else{
USART1->CR1 &=~(1<<7); // TX INTERRUPT DISABLE
}
}
 
}


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 