// temperature.h

void I2C_Init(void);
void I2C_start(void);
void I2C_write(unsigned char data);
unsigned char I2C_read(unsigned char ackVal);
void I2c_stop(void);
void temp_init(void);
int temp_read(void);
