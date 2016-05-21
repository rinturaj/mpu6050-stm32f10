
#include "mpu6050.h"

mpudata Acce_Gyro_Value(void)
{
  mpudata mpu;
  u8 buffer[14];

  I2C_BufferRead(MPU6050_DEFAULT_ADDRESS, buffer, MPU6050_RA_ACCEL_XOUT_H, 14);
  mpu.acc_x  =(s16)((u16)buffer[0]  << 8)  | buffer[1];  
  mpu.acc_y  =(s16)((u16)buffer[2]  << 8)  | buffer[3];
  mpu.acc_z  =(s16)((u16)buffer[4]  << 8)  | buffer[5];
  mpu.temp   =(s16)((u16)buffer[6]  << 8)  | buffer[7];
  mpu.gyro_x =(s16)((u16)buffer[8]  << 8)  | buffer[9];
  mpu.gyro_y =(s16)((u16)buffer[10]  << 8) | buffer[11];
  mpu.gyro_z =(s16)((u16)buffer[12]  << 8) | buffer[13];
  mpu.temperature = (float)(mpu.temp/340 +  36.53);
  return(mpu);
}

void mpu6050_init(void)
{
  
 // Set clock source setting.
  I2C_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1,
                MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO);
// gyro range
   I2C_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG,
                MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_250);
// acce range
  I2C_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG,
                MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH,MPU6050_ACCEL_FS_2);
//sleep mode disable
  I2C_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT,1, DISABLE);
}
