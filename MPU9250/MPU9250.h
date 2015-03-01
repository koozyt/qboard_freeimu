#ifndef _MPU9250_H_
#define _MPU9250_H_

#include "SPIdev.h"
#include <avr/pgmspace.h>

#define MPU9250_ADDRESS_AD0_LOW         0x68
#define MPU9250_ADDRESS_AD0_HIGH        0x69
#define MPU9250_DEFAULT_ADDRESS         MPU9250_ADDRESS_AD0_LOW
#define MPU9250_DEFAULT_SS_PIN          15

// register address
#define MPU9250_RA_SELF_TEST_X_GYRO     0x00
#define MPU9250_RA_SELF_TEST_Y_GYRO     0x01
#define MPU9250_RA_SELF_TEST_Z_GYRO     0x02
#define MPU9250_RA_SELF_TEST_X_ACCEL    0x0D
#define MPU9250_RA_SELF_TEST_Y_ACCEL    0x0E
#define MPU9250_RA_SELF_TEST_Z_ACCEL    0x0F
#define MPU9250_RA_XG_OFFS_H            0x13
#define MPU9250_RA_XG_OFFS_L            0x14
#define MPU9250_RA_YG_OFFS_H            0x15
#define MPU9250_RA_YG_OFFS_L            0x16
#define MPU9250_RA_ZG_OFFS_H            0x17
#define MPU9250_RA_ZG_OFFS_L            0x18
#define MPU9250_RA_SMPLRT_DIV           0x19
#define MPU9250_RA_CONFIG               0x1A
#define MPU9250_RA_GYRO_CONFIG          0x1B
#define MPU9250_RA_ACCEL_CONFIG         0x1C
#define MPU9250_RA_ACCEL_CONFIG2        0x1D
#define MPU9250_RA_LP_ACCEL_ODR         0x1E
#define MPU9250_RA_WOM_THR              0x1F
#define MPU9250_RA_FIFO_EN              0x23
#define MPU9250_RA_I2C_MST_CTRL         0x24
#define MPU9250_RA_I2C_SLV0_ADDR        0x25
#define MPU9250_RA_I2C_SLV0_REG         0x26
#define MPU9250_RA_I2C_SLV0_CTRL        0x27
#define MPU9250_RA_I2C_SLV1_ADDR        0x28
#define MPU9250_RA_I2C_SLV1_REG         0x29
#define MPU9250_RA_I2C_SLV1_CTRL        0x2A
#define MPU9250_RA_I2C_SLV2_ADDR        0x2B
#define MPU9250_RA_I2C_SLV2_REG         0x2C
#define MPU9250_RA_I2C_SLV2_CTRL        0x2D
#define MPU9250_RA_I2C_SLV3_ADDR        0x2E
#define MPU9250_RA_I2C_SLV3_REG         0x2F
#define MPU9250_RA_I2C_SLV3_CTRL        0x30
#define MPU9250_RA_I2C_SLV4_ADDR        0x31
#define MPU9250_RA_I2C_SLV4_REG         0x32
#define MPU9250_RA_I2C_SLV4_DO          0x33
#define MPU9250_RA_I2C_SLV4_CTRL        0x34
#define MPU9250_RA_I2C_SLV4_DI          0x35
#define MPU9250_RA_I2C_MST_STATUS       0x36
#define MPU9250_RA_INT_PIN_CFG          0x37
#define MPU9250_RA_INT_ENABLE           0x38
#define MPU9250_RA_INT_STATUS           0x3A
#define MPU9250_RA_ACCEL_XOUT_H         0x3B
#define MPU9250_RA_ACCEL_XOUT_L         0x3C
#define MPU9250_RA_ACCEL_YOUT_H         0x3D
#define MPU9250_RA_ACCEL_YOUT_L         0x3E
#define MPU9250_RA_ACCEL_ZOUT_H         0x3F
#define MPU9250_RA_ACCEL_ZOUT_L         0x40
#define MPU9250_RA_TEMP_OUT_H           0x41
#define MPU9250_RA_TEMP_OUT_L           0x42
#define MPU9250_RA_GYRO_XOUT_H          0x43
#define MPU9250_RA_GYRO_XOUT_L          0x44
#define MPU9250_RA_GYRO_YOUT_H          0x45
#define MPU9250_RA_GYRO_YOUT_L          0x46
#define MPU9250_RA_GYRO_ZOUT_H          0x47
#define MPU9250_RA_GYRO_ZOUT_L          0x48
#define MPU9250_RA_EXT_SENS_DATA_00     0x49
#define MPU9250_RA_EXT_SENS_DATA_01     0x4A
#define MPU9250_RA_EXT_SENS_DATA_02     0x4B
#define MPU9250_RA_EXT_SENS_DATA_03     0x4C
#define MPU9250_RA_EXT_SENS_DATA_04     0x4D
#define MPU9250_RA_EXT_SENS_DATA_05     0x4E
#define MPU9250_RA_EXT_SENS_DATA_06     0x4F
#define MPU9250_RA_EXT_SENS_DATA_07     0x50
#define MPU9250_RA_EXT_SENS_DATA_08     0x51
#define MPU9250_RA_EXT_SENS_DATA_09     0x52
#define MPU9250_RA_EXT_SENS_DATA_10     0x53
#define MPU9250_RA_EXT_SENS_DATA_11     0x54
#define MPU9250_RA_EXT_SENS_DATA_12     0x55
#define MPU9250_RA_EXT_SENS_DATA_13     0x56
#define MPU9250_RA_EXT_SENS_DATA_14     0x57
#define MPU9250_RA_EXT_SENS_DATA_15     0x58
#define MPU9250_RA_EXT_SENS_DATA_16     0x59
#define MPU9250_RA_EXT_SENS_DATA_17     0x5A
#define MPU9250_RA_EXT_SENS_DATA_18     0x5B
#define MPU9250_RA_EXT_SENS_DATA_19     0x5C
#define MPU9250_RA_EXT_SENS_DATA_20     0x5D
#define MPU9250_RA_EXT_SENS_DATA_21     0x5E
#define MPU9250_RA_EXT_SENS_DATA_22     0x5F
#define MPU9250_RA_EXT_SENS_DATA_23     0x60
#define MPU9250_RA_I2C_SLV0_DO          0x63
#define MPU9250_RA_I2C_SLV1_DO          0x64
#define MPU9250_RA_I2C_SLV2_DO          0x65
#define MPU9250_RA_I2C_SLV3_DO          0x66
#define MPU9250_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU9250_RA_SIGNAL_PATH_RESET    0x68
#define MPU9250_RA_MOT_DETECT_CTRL      0x69
#define MPU9250_RA_USER_CTRL            0x6A
#define MPU9250_RA_PWR_MGMT_1           0x6B
#define MPU9250_RA_PWR_MGMT_2           0x6C
#define MPU9250_RA_FIFO_COUNTH          0x72
#define MPU9250_RA_FIFO_COUNTL          0x73
#define MPU9250_RA_FIFO_R_W             0x74
#define MPU9250_RA_WHO_AM_I             0x75
#define MPU9250_RA_XA_OFFSET_H          0x77
#define MPU9250_RA_XA_OFFSET_L          0x78
#define MPU9250_RA_YA_OFFSET_H          0x7A
#define MPU9250_RA_YA_OFFSET_L          0x7B
#define MPU9250_RA_ZA_OFFSET_H          0x7D
#define MPU9250_RA_ZA_OFFSET_L          0x7E

#define MPU9250_CFG_FIFO_MODE_BIT       6
#define MPU9250_CFG_EXT_SYNC_SET_BIT    5
#define MPU9250_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU9250_CFG_DLPF_CFG_BIT        2
#define MPU9250_CFG_DLPF_CFG_LENGTH     3

#define MPU9250_EXT_SYNC_DISABLED       0x0
#define MPU9250_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU9250_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU9250_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU9250_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU9250_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU9250_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU9250_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU9250_DLPF_BW_250             0x00
#define MPU9250_DLPF_BW_184             0x01
#define MPU9250_DLPF_BW_92              0x02
#define MPU9250_DLPF_BW_41              0x03
#define MPU9250_DLPF_BW_20              0x04
#define MPU9250_DLPF_BW_10              0x05
#define MPU9250_DLPF_BW_5               0x06
#define MPU9250_DLPF_BW_3600            0x07

#define MPU9250_GCONFIG_FS_SEL_BIT      4
#define MPU9250_GCONFIG_FS_SEL_LENGTH   2

#define MPU9250_GYRO_FS_250             0x00
#define MPU9250_GYRO_FS_500             0x01
#define MPU9250_GYRO_FS_1000            0x02
#define MPU9250_GYRO_FS_2000            0x03

#define MPU9250_ACONFIG_XA_ST_BIT           7
#define MPU9250_ACONFIG_YA_ST_BIT           6
#define MPU9250_ACONFIG_ZA_ST_BIT           5
#define MPU9250_ACONFIG_AFS_SEL_BIT         4
#define MPU9250_ACONFIG_AFS_SEL_LENGTH      2

#define MPU9250_ACCEL_FS_2              0x00
#define MPU9250_ACCEL_FS_4              0x01
#define MPU9250_ACCEL_FS_8              0x02
#define MPU9250_ACCEL_FS_16             0x03

#define MPU9250_TEMP_FIFO_EN_BIT    7
#define MPU9250_XG_FIFO_EN_BIT      6
#define MPU9250_YG_FIFO_EN_BIT      5
#define MPU9250_ZG_FIFO_EN_BIT      4
#define MPU9250_ACCEL_FIFO_EN_BIT   3
#define MPU9250_SLV2_FIFO_EN_BIT    2
#define MPU9250_SLV1_FIFO_EN_BIT    1
#define MPU9250_SLV0_FIFO_EN_BIT    0

#define MPU9250_MULT_MST_EN_BIT     7
#define MPU9250_WAIT_FOR_ES_BIT     6
#define MPU9250_SLV_3_FIFO_EN_BIT   5
#define MPU9250_I2C_MST_P_NSR_BIT   4
#define MPU9250_I2C_MST_CLK_BIT     3
#define MPU9250_I2C_MST_CLK_LENGTH  4

#define MPU9250_CLOCK_DIV_348       0x0
#define MPU9250_CLOCK_DIV_333       0x1
#define MPU9250_CLOCK_DIV_320       0x2
#define MPU9250_CLOCK_DIV_308       0x3
#define MPU9250_CLOCK_DIV_296       0x4
#define MPU9250_CLOCK_DIV_286       0x5
#define MPU9250_CLOCK_DIV_276       0x6
#define MPU9250_CLOCK_DIV_267       0x7
#define MPU9250_CLOCK_DIV_258       0x8
#define MPU9250_CLOCK_DIV_500       0x9
#define MPU9250_CLOCK_DIV_471       0xA
#define MPU9250_CLOCK_DIV_444       0xB
#define MPU9250_CLOCK_DIV_421       0xC
#define MPU9250_CLOCK_DIV_400       0xD
#define MPU9250_CLOCK_DIV_381       0xE
#define MPU9250_CLOCK_DIV_364       0xF

#define MPU9250_I2C_SLV_RW_BIT      7
#define MPU9250_I2C_SLV_ADDR_BIT    6
#define MPU9250_I2C_SLV_ADDR_LENGTH 7
#define MPU9250_I2C_SLV_EN_BIT      7
#define MPU9250_I2C_SLV_BYTE_SW_BIT 6
#define MPU9250_I2C_SLV_REG_DIS_BIT 5
#define MPU9250_I2C_SLV_GRP_BIT     4
#define MPU9250_I2C_SLV_LEN_BIT     3
#define MPU9250_I2C_SLV_LEN_LENGTH  4

#define MPU9250_I2C_SLV4_RW_BIT         7
#define MPU9250_I2C_SLV4_ADDR_BIT       6
#define MPU9250_I2C_SLV4_ADDR_LENGTH    7
#define MPU9250_I2C_SLV4_EN_BIT         7
#define MPU9250_I2C_SLV4_INT_EN_BIT     6
#define MPU9250_I2C_SLV4_REG_DIS_BIT    5
#define MPU9250_I2C_SLV4_MST_DLY_BIT    4
#define MPU9250_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU9250_MST_PASS_THROUGH_BIT    7
#define MPU9250_MST_I2C_SLV4_DONE_BIT   6
#define MPU9250_MST_I2C_LOST_ARB_BIT    5
#define MPU9250_MST_I2C_SLV4_NACK_BIT   4
#define MPU9250_MST_I2C_SLV3_NACK_BIT   3
#define MPU9250_MST_I2C_SLV2_NACK_BIT   2
#define MPU9250_MST_I2C_SLV1_NACK_BIT   1
#define MPU9250_MST_I2C_SLV0_NACK_BIT   0

#define MPU9250_INTCFG_INT_LEVEL_BIT        7
#define MPU9250_INTCFG_INT_OPEN_BIT         6
#define MPU9250_INTCFG_LATCH_INT_EN_BIT     5
#define MPU9250_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU9250_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU9250_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU9250_INTCFG_I2C_BYPASS_EN_BIT    1

#define MPU9250_INTMODE_ACTIVEHIGH  0x00
#define MPU9250_INTMODE_ACTIVELOW   0x01

#define MPU9250_INTDRV_PUSHPULL     0x00
#define MPU9250_INTDRV_OPENDRAIN    0x01

#define MPU9250_INTLATCH_50USPULSE  0x00
#define MPU9250_INTLATCH_WAITCLEAR  0x01

#define MPU9250_INTCLEAR_STATUSREAD 0x00
#define MPU9250_INTCLEAR_ANYREAD    0x01

#define MPU9250_INTERRUPT_WOM_BIT           6
#define MPU9250_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU9250_INTERRUPT_FSYNC_INT_BIT     3
#define MPU9250_INTERRUPT_DATA_RDY_BIT      0

#define MPU9250_INTERRUPT_WOM               0x40
#define MPU9250_INTERRUPT_FIFO_OFLOW        0x10
#define MPU9250_INTERRUPT_FSYNC_INT         0x08
#define MPU9250_INTERRUPT_DATA_RDY          0x01

#define MPU9250_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU9250_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU9250_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU9250_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU9250_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU9250_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU9250_PATHRESET_GYRO_RESET_BIT    2
#define MPU9250_PATHRESET_ACCEL_RESET_BIT   1
#define MPU9250_PATHRESET_TEMP_RESET_BIT    0

#define MPU9250_USERCTRL_FIFO_EN_BIT            6
#define MPU9250_USERCTRL_I2C_MST_EN_BIT         5
#define MPU9250_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU9250_USERCTRL_FIFO_RESET_BIT         2
#define MPU9250_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU9250_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU9250_PWR1_DEVICE_RESET_BIT   7
#define MPU9250_PWR1_SLEEP_BIT          6
#define MPU9250_PWR1_CYCLE_BIT          5
#define MPU9250_PWR1_GYRO_STANDBY_BIT   4
#define MPU9250_PWR1_PD_PTAT            3
#define MPU9250_PWR1_CLKSEL_BIT         2
#define MPU9250_PWR1_CLKSEL_LENGTH      3

#define MPU9250_CLOCK_INTERNAL          0x00
#define MPU9250_CLOCK_PLL_XGYRO         0x01
#define MPU9250_CLOCK_PLL_YGYRO         0x02
#define MPU9250_CLOCK_PLL_ZGYRO         0x03
#define MPU9250_CLOCK_PLL_EXT32K        0x04
#define MPU9250_CLOCK_PLL_EXT19M        0x05
#define MPU9250_CLOCK_INTERNAL_20M      0x06
#define MPU9250_CLOCK_KEEP_RESET        0x07

#define MPU9250_PWR2_DIS_XA_BIT            5
#define MPU9250_PWR2_DIS_YA_BIT            4
#define MPU9250_PWR2_DIS_ZA_BIT            3
#define MPU9250_PWR2_DIS_XG_BIT            2
#define MPU9250_PWR2_DIS_YG_BIT            1
#define MPU9250_PWR2_DIS_ZG_BIT            0


// **magnetometer**
#define AK8963_ADDRESS              0x0c

// register address
#define AK8963_WIA                  0x00                    // who am I
#define AK8963_ST1                  0x02                    // status1
#define AK8963_HXL                  0x03                    // HXL
#define AK8963_ST2                  0x09                    // status2
#define AK8963_CNTL1                0x0a                    // control1
#define AK8963_CNTL2                0x0b                    // control2
#define AK8963_ASAX                 0x10                    // start of the fuse ROM data


class MPU9250 {
public:
    MPU9250();

    void initialize();
    bool testConnection();

    // AUX_VDDIO register
    uint8_t getAuxVDDIOLevel();
    void setAuxVDDIOLevel(uint8_t level);

    // SMPLRT_DIV register
    uint8_t getRate();
    void setRate(uint8_t rate);

    // CONFIG register
    uint8_t getExternalFrameSync();
    void setExternalFrameSync(uint8_t sync);
    uint8_t getDLPFMode();
    void setDLPFMode(uint8_t bandwidth);

    // GYRO_CONFIG register
    uint8_t getFullScaleGyroRange();
    void setFullScaleGyroRange(uint8_t range);

    // ACCEL_CONFIG register
    bool getAccelXSelfTest();
    void setAccelXSelfTest(bool enabled);
    bool getAccelYSelfTest();
    void setAccelYSelfTest(bool enabled);
    bool getAccelZSelfTest();
    void setAccelZSelfTest(bool enabled);
    uint8_t getFullScaleAccelRange();
    void setFullScaleAccelRange(uint8_t range);

    // FIFO_EN register
    bool getTempFIFOEnabled();
    void setTempFIFOEnabled(bool enabled);
    bool getXGyroFIFOEnabled();
    void setXGyroFIFOEnabled(bool enabled);
    bool getYGyroFIFOEnabled();
    void setYGyroFIFOEnabled(bool enabled);
    bool getZGyroFIFOEnabled();
    void setZGyroFIFOEnabled(bool enabled);
    bool getAccelFIFOEnabled();
    void setAccelFIFOEnabled(bool enabled);
    bool getSlave2FIFOEnabled();
    void setSlave2FIFOEnabled(bool enabled);
    bool getSlave1FIFOEnabled();
    void setSlave1FIFOEnabled(bool enabled);
    bool getSlave0FIFOEnabled();
    void setSlave0FIFOEnabled(bool enabled);

    // I2C_MST_CTRL register
    bool getMultiMasterEnabled();
    void setMultiMasterEnabled(bool enabled);
    bool getWaitForExternalSensorEnabled();
    void setWaitForExternalSensorEnabled(bool enabled);
    bool getSlave3FIFOEnabled();
    void setSlave3FIFOEnabled(bool enabled);
    bool getSlaveReadWriteTransitionEnabled();
    void setSlaveReadWriteTransitionEnabled(bool enabled);
    uint8_t getMasterClockSpeed();
    void setMasterClockSpeed(uint8_t speed);

    // I2C_SLV* registers (Slave 0-3)
    uint8_t getSlaveAddress(uint8_t num);
    void setSlaveAddress(uint8_t num, uint8_t address);
    uint8_t getSlaveRegister(uint8_t num);
    void setSlaveRegister(uint8_t num, uint8_t reg);
    bool getSlaveEnabled(uint8_t num);
    void setSlaveEnabled(uint8_t num, bool enabled);
    bool getSlaveWordByteSwap(uint8_t num);
    void setSlaveWordByteSwap(uint8_t num, bool enabled);
    bool getSlaveWriteMode(uint8_t num);
    void setSlaveWriteMode(uint8_t num, bool mode);
    bool getSlaveWordGroupOffset(uint8_t num);
    void setSlaveWordGroupOffset(uint8_t num, bool enabled);
    uint8_t getSlaveDataLength(uint8_t num);
    void setSlaveDataLength(uint8_t num, uint8_t length);

    // I2C_SLV* registers (Slave 4)
    uint8_t getSlave4Address();
    void setSlave4Address(uint8_t address);
    uint8_t getSlave4Register();
    void setSlave4Register(uint8_t reg);
    void setSlave4OutputByte(uint8_t data);
    bool getSlave4Enabled();
    void setSlave4Enabled(bool enabled);
    bool getSlave4InterruptEnabled();
    void setSlave4InterruptEnabled(bool enabled);
    bool getSlave4WriteMode();
    void setSlave4WriteMode(bool mode);
    uint8_t getSlave4MasterDelay();
    void setSlave4MasterDelay(uint8_t delay);
    uint8_t getSlate4InputByte();

    // I2C_MST_STATUS register
    bool getPassthroughStatus();
    bool getSlave4IsDone();
    bool getLostArbitration();
    bool getSlave4Nack();
    bool getSlave3Nack();
    bool getSlave2Nack();
    bool getSlave1Nack();
    bool getSlave0Nack();

    // INT_PIN_CFG register
    bool getInterruptMode();
    void setInterruptMode(bool mode);
    bool getInterruptDrive();
    void setInterruptDrive(bool drive);
    bool getInterruptLatch();
    void setInterruptLatch(bool latch);
    bool getInterruptLatchClear();
    void setInterruptLatchClear(bool clear);
    bool getFSyncInterruptLevel();
    void setFSyncInterruptLevel(bool level);
    bool getFSyncInterruptEnabled();
    void setFSyncInterruptEnabled(bool enabled);
    bool getI2CBypassEnabled();
    void setI2CBypassEnabled(bool enabled);

    // INT_ENABLE register
    uint8_t getIntEnabled();
    void setIntEnabled(uint8_t enabled);
    bool getIntFIFOBufferOverflowEnabled();
    void setIntFIFOBufferOverflowEnabled(bool enabled);
    bool getIntI2CMasterEnabled();
    void setIntI2CMasterEnabled(bool enabled);
    bool getIntDataReadyEnabled();
    void setIntDataReadyEnabled(bool enabled);

    // INT_STATUS register
    uint8_t getIntStatus();
    bool getIntFIFOBufferOverflowStatus();
    bool getIntDataReadyStatus();

    // ACCEL_*OUT_* registers
    void getMotion9(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz, int16_t* mx, int16_t* my, int16_t* mz);
    void getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
    void getAcceleration(int16_t* x, int16_t* y, int16_t* z);
    int16_t getAccelerationX();
    int16_t getAccelerationY();
    int16_t getAccelerationZ();

    // TEMP_OUT_* registers
    int16_t getTemperature();

    // GYRO_*OUT_* registers
    void getRotation(int16_t* x, int16_t* y, int16_t* z);
    int16_t getRotationX();
    int16_t getRotationY();
    int16_t getRotationZ();

    // EXT_SENS_DATA_* registers
    uint8_t getExternalSensorByte(int position);
    uint16_t getExternalSensorWord(int position);
    uint32_t getExternalSensorDWord(int position);

    // I2C_SLV*_DO register
    void setSlaveOutputByte(uint8_t num, uint8_t data);

    // I2C_MST_DELAY_CTRL register
    bool getExternalShadowDelayEnabled();
    void setExternalShadowDelayEnabled(bool enabled);
    bool getSlaveDelayEnabled(uint8_t num);
    void setSlaveDelayEnabled(uint8_t num, bool enabled);

    // SIGNAL_PATH_RESET register
    void resetGyroscopePath();
    void resetAccelerometerPath();
    void resetTemperaturePath();

    // USER_CTRL register
    bool getFIFOEnabled();
    void setFIFOEnabled(bool enabled);
    bool getI2CMasterModeEnabled();
    void setI2CMasterModeEnabled(bool enabled);
    void switchSPIEnabled(bool enabled);
    void resetFIFO();
    void resetI2CMaster();
    void resetSensors();

    // PWR_MGMT_1 register
    void reset();
    bool getSleepEnabled();
    void setSleepEnabled(bool enabled);
    bool getWakeCycleEnabled();
    void setWakeCycleEnabled(bool enabled);
    uint8_t getClockSource();
    void setClockSource(uint8_t source);

    // FIFO_COUNT_* registers
    uint16_t getFIFOCount();

    // FIFO_R_W register
    uint8_t getFIFOByte();
    void getFIFOBytes(uint8_t *data, uint8_t length);

    void setFIFOByte(uint8_t data);

    // WHO_AM_I register
    uint8_t getDeviceID();

    // ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========

    // XG_OFFS_* registers
    int16_t getXGyroOffset();
    void setXGyroOffset(int16_t offset);

    // YG_OFFS_* register
    int16_t getYGyroOffset();
    void setYGyroOffset(int16_t offset);

    // ZG_OFFS_* register
    int16_t getZGyroOffset();
    void setZGyroOffset(int16_t offset);

    // Magnetometer
    void initMgnt();
    uint8_t getMgntDeviceID();
    void getMgntValues(int16_t *mx, int16_t *my, int16_t *mz);
    uint8_t getMgntMode();
    uint8_t getMgntStatus1();
    uint8_t getMgntStatus2();
private:
    uint8_t devAddr;
    uint8_t buffer[14];
    float mgntAdjust[3];
    float lastMgnt[3];
    uint8_t mgntStatuses[2];
};


#endif /* _MPU9250_H_ */
