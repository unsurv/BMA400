/* 10/16/2018 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 *  The BMA400 is an inexpensive (~$2), three-axis, medium-resolution (12-bit), ultra-low power (800 nA low power mode) accelerometer 
 *  in a tiny 2 mm x 2 mm LGA12 package with 1024-byte FIFO, 
 *  two multifunction interrupts and widely configurable sample rate (15 - 800 Hz), full range (2 - 16 g), low power modes, 
 *  and interrupt detection behaviors. This accelerometer is nice choice for motion-based wake/sleep,
 *  tap detection, step counting, and simple orientation estimation.
 *  
 *  Library may be used freely and without limit with attribution.
 *  
 */
 
#ifndef BMA400_h
#define BMA400_h

#include "Arduino.h"
#include <Wire.h>

/* Register Map BMA400
// https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA400-DS000-02.pdf
*/
#define BMA400_CHIPID          0x00

#define BMA400_ERR_REG         0x02
#define BMA400_STATUS          0x03
#define BMA400_ACCD_X_LSB      0x04
#define BMA400_ACCD_X_MSB      0x05
#define BMA400_ACCD_Y_LSB      0x06
#define BMA400_ACCD_Y_MSB      0x07
#define BMA400_ACCD_Z_LSB      0x08
#define BMA400_ACCD_Z_MSB      0x09
#define BMA400_SENSOR_TIME_0   0x0A
#define BMA400_SENSOR_TIME_1   0x0B
#define BMA400_SENSOR_TIME_2   0x0C
#define BMA400_EVENT           0x0D
#define BMA400_INT_STAT_0      0x0E
#define BMA400_INT_STAT_1      0x0F
#define BMA400_INT_STAT_2      0x10
#define BMA400_TEMP_DATA       0x11
#define BMA400_FIFO_LENGTH0    0x12
#define BMA400_FIFO_LENGTH1    0x13
#define BMA400_FIFO_DATA       0x14
#define BMA400_STEP_CNT_0      0x15
#define BMA400_STEP_CNT_1      0x16
#define BMA400_STEP_CNT_2      0x17
#define BMA400_STEP_STAT       0x18
#define BMA400_ACC_CONFIG0     0x19
#define BMA400_ACC_CONFIG1     0x1A
#define BMA400_ACC_CONFIG2     0x1B

#define BMA400_INT_CONFIG0     0x1F
#define BMA400_INT_CONFIG1     0x20
#define BMA400_INT1_MAP        0x21
#define BMA400_INT2_MAP        0x22
#define BMA400_INT12_MAP       0x23
#define BMA400_INT12_IO_CTRL   0x24

#define BMA400_FIFO_CONFIG0    0x26
#define BMA400_FIFO_CONFIG1    0x27
#define BMA400_FIFO_CONFIG2    0x28
#define BMA400_FIFO_PWR_CONFIG 0x29
#define BMA400_AUTOLOWPOW_0    0x2A
#define BMA400_AUTOLOWPOW_1    0x2B
#define BMA400_AUTOWAKEUP_0    0x2C
#define BMA400_AUTOWAKEUP_1    0x2D

#define BMA400_WKUP_INT_CONFIG0 0x2F
#define BMA400_WKUP_INT_CONFIG1 0x30
#define BMA400_WKUP_INT_CONFIG2 0x31
#define BMA400_WKUP_INT_CONFIG3 0x32
#define BMA400_WKUP_INT_CONFIG4 0x33

#define BMA400_ORIENTCH_CONFIG0 0x35
#define BMA400_ORIENTCH_CONFIG1 0x36
#define BMA400_ORIENTCH_CONFIG2 0x37
#define BMA400_ORIENTCH_CONFIG3 0x38
#define BMA400_ORIENTCH_CONFIG4 0x39
#define BMA400_ORIENTCH_CONFIG5 0x3A
#define BMA400_ORIENTCH_CONFIG6 0x3B
#define BMA400_ORIENTCH_CONFIG7 0x3C
#define BMA400_ORIENTCH_CONFIG8 0x3D
#define BMA400_ORIENTCH_CONFIG9 0x3E

#define BMA400_GEN1INT_CONFIG0  0x3F
#define BMA400_GEN1INT_CONFIG1  0x40
#define BMA400_GEN1INT_CONFIG2  0x41
#define BMA400_GEN1INT_CONFIG3  0x42
#define BMA400_GEN1INT_CONFIG31 0x43
#define BMA400_GEN1INT_CONFIG4  0x44
#define BMA400_GEN1INT_CONFIG5  0x45
#define BMA400_GEN1INT_CONFIG6  0x46
#define BMA400_GEN1INT_CONFIG7  0x47
#define BMA400_GEN1INT_CONFIG8  0x48
#define BMA400_GEN1INT_CONFIG9  0x49
#define BMA400_GEN2INT_CONFIG0  0x4A
#define BMA400_GEN2INT_CONFIG1  0x4B
#define BMA400_GEN2INT_CONFIG2  0x4C
#define BMA400_GEN2INT_CONFIG3  0x4D
#define BMA400_GEN2INT_CONFIG31 0x4E
#define BMA400_GEN2INT_CONFIG4  0x4F
#define BMA400_GEN2INT_CONFIG5  0x50
#define BMA400_GEN2INT_CONFIG6  0x51
#define BMA400_GEN2INT_CONFIG7  0x52
#define BMA400_GEN2INT_CONFIG8  0x53
#define BMA400_GEN2INT_CONFIG9  0x54
#define BMA400_ACTCH_CONFIG0    0x55
#define BMA400_ACTCH_CONFIG1    0x56
#define BMA400_TAP_CONFIG       0x57
#define BMA400_TAP_CONFIG1      0x58

#define BMA400_STEP_COUNTERCONFIG0    0x59
#define BMA400_STEP_COUNTERCONFIG1    0x5A 
#define BMA400_STEP_COUNTERCONFIG2    0x5B
#define BMA400_STEP_COUNTERCONFIG3    0x5C
#define BMA400_STEP_COUNTERCONFIG4    0x5D
#define BMA400_STEP_COUNTERCONFIG5    0x5E
#define BMA400_STEP_COUNTERCONFIG6    0x5F
#define BMA400_STEP_COUNTERCONFIG7    0x60
#define BMA400_STEP_COUNTERCONFIG8    0x61
#define BMA400_STEP_COUNTERCONFIG9    0x62
#define BMA400_STEP_COUNTERCONFIG10   0x63
#define BMA400_STEP_COUNTERCONFIG11   0x64
#define BMA400_STEP_COUNTERCONFIG12   0x65
#define BMA400_STEP_COUNTERCONFIG13   0x66
#define BMA400_STEP_COUNTERCONFIG14   0x67
#define BMA400_STEP_COUNTERCONFIG15   0x68
#define BMA400_STEP_COUNTERCONFIG16   0x69
#define BMA400_STEP_COUNTERCONFIG17   0x6A
#define BMA400_STEP_COUNTERCONFIG18   0x6B
#define BMA400_STEP_COUNTERCONFIG19   0x6C
#define BMA400_STEP_COUNTERCONFIG20   0x6D
#define BMA400_STEP_COUNTERCONFIG21   0x6E
#define BMA400_STEP_COUNTERCONFIG22   0x6F
#define BMA400_STEP_COUNTERCONFIG23   0x70

#define BMA400_STEP_CNT0  0x15
#define BMA400_STEP_CNT1  0x16
#define BMA400_STEP_CNT2  0x17

#define BMA400_STEP_STAT  0x18

#define BMA400_STEP_STAT_IDLE     0x00
#define BMA400_STEP_STAT_WALKING  0x01
#define BMA400_STEP_STAT_RUNNING  0x02



#define BMA400_IF_CONF          0x7C
#define BMA400_SELF_TEST        0x7D
#define BMA400_CMD              0x7E


#define BMA400_ADDRESS  0x14  // 0x 14 if ADO is 0 (default)


#define AFS_2G           0x00
#define AFS_4G           0x01
#define AFS_8G           0x02
#define AFS_16G          0x03

#define SR_12_5Hz        0x05  // 12.5 Hz sample rate, etc
#define SR_25Hz          0x06
#define SR_50Hz          0x07
#define SR_100Hz         0x08
#define SR_200Hz         0x09  // 200 Hz sample rate
#define SR_400Hz         0x0A
#define SR_800Hz         0x0B  // 800 Hz sample rate  

#define sleep_Mode       0x00  // define power modes
#define lowpower_Mode    0x01
#define normal_Mode      0x02

// define oversampling
#define osr0             0x00  // lowest power, lowest oversampling, lowest accuracy
#define osr1             0x01
#define osr2             0x02
#define osr3             0x03 // highest oversampling, highest power, highest accuracy

#define acc_filt1        0x00 // variable ODR filter
#define acc_filt2        0x01 // fixed 100 Hz ODR filter
#define acc_filt_lp      0x02 // fixed 100 Hz ODR filter, 1 Hz BW

// define tap configs

#define INT_STAT1_SINGLE_TAP 0x04
#define INT_STAT1_DOUBLE_TAP 0x0c // 0x08 for non latching interrupts, 0x0c for latching

#define tap_sens_0       0x00 // highest tap sensitivity
#define tap_sens_1       0x01
#define tap_sens_2       0x02
#define tap_sens_3       0x03
#define tap_sens_4       0x04
#define tap_sens_5       0x05
#define tap_sens_6       0x06 // lowest tap sensitivity


#define tics_th_6        0x00 // 6 data samples for high-low tap signal change time
#define tics_th_9        0x01
#define tics_th_12       0x02
#define tics_th_18       0x03

#define quiet_60         0x00 // 60 data samples quiet time between single or doube taps 
#define quiet_80         0x01
#define quiet_100        0x02
#define quiet_120        0x03

#define quiet_dt_4       0x00 // 4 data samples minimum time between double taps
#define quiet_dt_8       0x01
#define quiet_dt_12      0x02
#define quiet_dt_16      0x03


class BMA400
{
  public: 
  BMA400(uint8_t intPin1, uint8_t intPin2);
  float getAres(uint8_t Ascale);
  uint8_t getChipID();
  void initBMA400(uint8_t Ascale, uint8_t SR, uint8_t power_Mode, uint8_t OSR, uint8_t acc_filter);
  void initBMA400forTapping(uint8_t tap_sensitivity);
  void enableStepCountNotWrist();
  void CompensationBMA400(uint8_t Ascale, uint8_t SR, uint8_t power_Mode, uint8_t OSR, uint8_t acc_filter, float * offset);
  void resetBMA400();
  void selfTestBMA400();
  void readBMA400AccelData(int16_t * destination);
  int16_t readBMA400TempData();
  void activateNoMotionInterrupt();
  void deactivateNoMotionInterrupt();
  uint8_t getStatus();
  void I2Cscan();
  void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
  uint8_t readByte(uint8_t address, uint8_t subAddress);
  void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
  private:
  uint8_t _intPin1;
  uint8_t _intPin2;
  float _aRes;
};

#endif
