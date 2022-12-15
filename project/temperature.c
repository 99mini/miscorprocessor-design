 
#define F_CPU 16000000UL
#include <avr/io.h> 
#include <stdio.h>
#include <util/delay.h>
#include "temperature.h"

#define aTS75_CONFIG_REG        1
#define aTS75_TEMP_REG        0

void I2C_Init(void);
void I2C_start(void);
void I2C_write(unsigned char data);
unsigned char I2C_read(unsigned char ackVal);
void I2c_stop(void);
void temp_init(void);
int temp_read(void);

void I2C_Init(void) {
    TWBR = 12;                            // 16000000 / (16 + (2x12)) x prescaler = 400000Hz = 400kHz
    TWSR = (0<<TWPS1) | (0<<TWPS0);        // prescaler = 1
    TWCR = 0x04;
}

void I2C_start(void) {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}
 
void I2C_write(unsigned char data) {
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}
 
unsigned char I2C_read(unsigned char ackVal) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (ackVal<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}
 
void I2c_stop(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    for(int k=0; k<100; k++);                    //wait
}

/*
 * Pointer set followed by immediate write to the Configuration Register 데이터시트 참조 
 */
void temp_init(void) {
    I2C_Init();
    I2C_start();
    I2C_write(0b10011000);
    I2C_write(aTS75_CONFIG_REG);        // Configuration Register P1 = 0, P0 = 1
    I2C_write(0x00);
    I2c_stop();
}
 
 
/*
 * Pointer set followed by immediate read from a 2-byte register 데이터시트 참조
 */
int temp_read(void) {
    char high_byte, low_byte;
    I2C_start();
    I2C_write(0b10011000);
    I2C_write(aTS75_TEMP_REG);            // Temperature Register P1, P0 = 0 
    
    I2C_start();
    I2C_write(0b10011000 | 1);            // Address + write (not read)
    high_byte = I2C_read(1);            
    low_byte = I2C_read(0);
    I2c_stop();
    
    return ((high_byte<<8) | low_byte);
}
