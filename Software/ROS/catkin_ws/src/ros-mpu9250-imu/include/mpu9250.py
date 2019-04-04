#!/usr/bin/env python
# 03/2019 @MikeMakes
# Delivered as it is, without any warranty
# GPU 3.0
# This library for mpu9250 is equivalent to this one:
# https://github.com/MikeMakes/ros-mpu6050-imu
# but with the magnetometer AK8963 implemented

from i2c import read_byte, write_byte, read_word_2c

class mpu9250:
    def __init__(self, bus, i2c_adr=0x68):   # Default i2c address of imu6050 is 64(dec) = 40(hex)
        self.bus = bus  # i2c bus to be used
        self.i2c_adr=i2c_adr # i2c addres of mpu9250
        self.range_sensor('GYRO',0)
        self.range_sensor('ACCEL',0)

    # Dictionary for useful mpus6050's registers (low byte, add -1 calling read/write words)
    regs = {'SMPRT_DIV' : 0x19, # Sample Rate divider; SR = Gyro Output Rate / (1 + SMPRT_DIV[7:0])
            'CONFIG' : 0x1A,    # This  register  configures  the  external Frame  Synchronization  (FSYNC)pin  sampling [6:3] and  the Digital Low Pass Filter (DLPF)settingfor both the gyroscopes and accelerometers [2:0]
            'GYRO_CONFIG' : 0x1B,   # This register is used to trigger gyroscope self-test and configure the gyroscopes' full scale range (bits FS_SELX)
            'ACCEL_CONFIG' : 0x1C,  # This  register  is  used  to  trigger  accelerometer  self  test  and  configure  the  accelerometer  full  scale range. This register also configures the Digital High Pass Filter (DHPF)
            'FIFO_EN' : 0x23,   # This register determines which sensor measurements are loaded into the FIFO buffer
            'INT_ENABLE' : 0x38,    # This register enables interrupt generation by interrupt sources; FIFO_OFLOW_EN I2C_MST_INT_EN DATA_RDY_EN
            'INT_STATUS' : 0x3A,    # This register shows the interrupt status of each interrupt generation source. Each bit will clear after the register is read
            'PWR_MGMT_1' : 0x6b,    # This register allows the user to configure the power mode and clock source. It also provides a bit for resetting the entire device, and a bit for disabling the temperature sensor
            'PWR_MGMT_2' : 0x6c,
            'AX' : 0x3c,
            'AY' : 0x3e,
            'AZ' : 0x40,
            'GX' : 0x44,
            'GY' : 0x46,
            'GZ' : 0x48,
            }

    # Useful bits
    bits = {'DLP_CFG0' : 0x00,  # Digital Low Filter congifg (0 or 7 = disabled)
            'DLP_CFG1' : 0x01,
            'DLP_CFG2' : 0x02,
            'DLP_CFG3' : 0x03,
            'DLP_CFG4' : 0x04,
            'DLP_CFG5' : 0x05,
            'DLP_CFG6' : 0x06,
            'DLP_CFG7' : 0x07,
            'FIFO_OFLOW_EN' : 0x01,  # Set this bit in INT_ENABLE reg to enable fifo interrupts
            'I2C_MST_INT_EN' : 0b00000100,   # Set this bit in INT_ENABLE reg to enable i2c master interrupts
            'DATA_RDY_EN' : 0b00001000, # Set this bit in INT_ENABLE reg to enable data interrupts
            'DEVICE_RESET' : 0b10000000,    # Set this bit to reset all internal registers to their default values. The bit automatically clears to 0 once the reset is done
            'SLEEP' : 0b01000000,   # Set this bit in PWR_MGMT_1 to put the mpu to sleep
            'CYCLE' : 0b00100000,   # Set to 1 in PWR_MGMT_1 and SLEEP is disabled,  the  MPU-60X0  will  cycle between  sleep mode  and  waking  up  to  take a single  sample of data from active sensors
            'TEMP_DIS' : 0b00001000,    # When set to 1 in PWR_MGMT_1, this bit disables the temperature sensor.
            'CLKSEL_8MHZ' : 0x00,   # Clear 3 lsb in PWR_MGMT_1 to use the internal 8MHz oscillator as clock source
            'CLKSEL_STOP' : 0x07,   # Set the 3 lsb to 1 in PWR_MGMT_1 will stops the clock and keeps the timing generator in reset
            'FS_SEL0' : 0b00000000,    # Full scale range values for gyro (and accel)
            'FS_SEL1' : 0b00001000,
            'FS_SEL2' : 0b00010000,
            'FS_SEL3' : 0b00011000,
            }

    #scales = {'GYRO_SCALE_FS_SEL0' : 131,
            #'GYRO_SCALE_FS_SEL1' : 65.5,
            #'GYRO_SCALE_FS_SEL2' : 32.8,
            #'GYRO_SCALE_FS_SEL3' : 16.4,
            #'ACCEL_SCALE_FS_SEL0' : 16384,
            #'ACCEL_SCALE_FS_SEL1' : 8192,
            #'ACCEL_SCALE_FS_SEL2' : 4096,
            #'ACCEL_SCALE_FS_SEL3' : 2048,
            #}
    scales = {'GYRO_SCALE_FS_SEL0' : 131,
            'GYRO_SCALE_FS_SEL1' : 65.5,
            'GYRO_SCALE_FS_SEL2' : 32.8,
            'GYRO_SCALE_FS_SEL3' : 16.4,
            'ACCEL_SCALE_FS_SEL0' : 1671.8,
            'ACCEL_SCALE_FS_SEL1' : 835.9,
            'ACCEL_SCALE_FS_SEL2' : 417.9,
            'ACCEL_SCALE_FS_SEL3' : 209.0,
            }

    def sample_rate(self, sr):  # Set a sample rate = sr (and return the SMPRT_DIV register value)
        config = read_byte(self.data, self.i2c_adr, self.regs['CONFIG'])
        dlpf = config & 0b111
        if (dlpf == 0) or (dlpf == 7):
            self.dlpf_enabled = False   # Digital Low Pass Filter disabled
            gyr = 8000    # Gyroscope Output Rate = 8000Hz
            sr_div = (gyr/sr)-1 # From datasheet; Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
        else:
            self.dlpf_enabled = True
            gyr = 1000    # Gyroscope Output Rate = 1000Hz
            sr_div = (gyr/sr)-1
        write_byte(self.bus, self.i2c_adr, self.regs['SMPRT_DIV'], sr_div)
        return sr_div


    def dis_fifo(self): # Clear all bits of FIFO_EN; nothing will be loaded into the fifo buffer
        write_byte(self.bus, self.i2c_adr, self.regs['FIFO_EN'], 0x00)

    def just_gyro_accel_fifo(self): # Set gx,gy,gz,accel bits of FIFO_EN; gyro and accel data from the sensor registers will be loaded into the fifo buffer
        write_byte(self.bus, self.i2c_adr, self.regs['FIFO_EN'], 0xb01111000)


    def dis_interrupts(self):   # Disable all interrupts
        write_byte(self.bus, self.i2c_adr, self.regs['INT_ENABLE'], 0x00)

    def en_data_interrupts(self):
        interrupts = read_byte(self.data, self.i2c_adr, self.regs['INT_ENABLE'])
        interrupts = interrupts | self.bits['DATA_RDY_EN']
        write_byte(self.bus, self.i2c_adr, self.regs['INT_ENABLE'], interrupts)

    def data_available(self):   # Return true if data interrupt
        data = read_byte(self.bus, self.i2c_adr, self.regs['INT_ENABLE'])
        if (data & self.bits['DATA_RDY_EN']):
            return True
        else:
            return False


    def inbed(self):    # Check if mpu is sleeping (as sleep() function would do with an arg) [Ex: sleep(Is_Noise)]
        mode = read_byte(self.bus, self.i2c_adr, self.regs['PWR_MGMT_1'])    # Read MODE_1 reg from i2c_adr
        sleep = mode & self.bits['SLEEP']
        if sleep: # If mpu is sleeping (PWR_MGMT_1 reg, SLEEP bit is 1)
            return True # Exit, mpu sleeped
        else:
            return False    # Exit, mpu is awake

    def sleep(self, noise=None):    # Put mpu6050 to sleep (default mode at power up) except when Noise=Something (then this is just a check, True = Sleep)
        mode = read_byte(self.bus, self.i2c_adr, self.regs['PWR_MGMT_1'])
        sleep = mode & self.bits['SLEEP']   # And take the SLEEP bit
        if sleep: # If mpu is sleeping (PWR_MGMT_1 reg, SLEEP bit is 1)
            return True # Exit, alredy sleeping, nothing to do here
        else:   # If mpu is not sleeping...
            if noise is not None: # ...and there is noise, it wont sleep:
                return False    # Exit without sleeping
        # Mpu is not sleeping but there is not noise so it will sleep:
        mode = mode | self.bits['SLEEP']   # Copy MODE_1 byte but set SLEEP bit
        write_byte(self.bus, self.i2c_adr, self.regs['PWR_MGMT_1'], mode)   # power_mgmt_1 reg = X1XX XXXX
        return True # Mpu in bed

    def wakeup(self):
        mode = read_byte(self.bus, self.i2c_adr, self.regs['PWR_MGMT_1'])
        sleep = mode & self.bits['SLEEP']   # And take the SLEEP bit
        if not sleep:
            return True
        # if sleep:
        mode = mode & ~self.bits['SLEEP']   # Clear SLEEP bit
        write_byte(self.bus, self.i2c_adr, self.regs['PWR_MGMT_1'], mode)     # power_mgmt_1 reg = X0XX XXXX
        # Delay after this so the gyros could stabilize & registers have time to reset


    def range_sensor(self, sensor, fs_sel=0):   # Selects full scale range of gyroscopes ('GYRO') or accelerometer ('ACCEL') with fs_sel = 0,1,2,3
        fs_sel = 'FS_SEL' + str(fs_sel) # fs_sel choose the scale of the sensor
        scale = sensor + '_SCALE_' + fs_sel
        if sensor == 'GYRO':    # sensor is used to determine which range sensor change and its config register
            self.gyro_scale = self.scales[scale]
        elif sensor == 'ACCEL':
            self.accel_scale = self.scales[scale]
        sensor += '_CONFIG'
        write_byte(self.bus, self.i2c_adr, self.regs[sensor], self.bits[fs_sel])


    def raw_x_accel(self):
        return read_word_2c(self.bus, self.i2c_adr, self.regs['AX'], -1)

    def raw_y_accel(self):
        return read_word_2c(self.bus, self.i2c_adr, self.regs['AY'], -1)

    def raw_z_accel(self):
        return read_word_2c(self.bus, self.i2c_adr, self.regs['AZ'], -1)

    def raw_accel(self):    # Get raw measurements from accelerometers registers
        x = self.raw_x_accel()
        y = self.raw_y_accel()
        z = self.raw_z_accel()
        return [x,y,z]

    def accel(self):
        raw = self.raw_accel()
        scaled = [i / self.accel_scale for i in raw]
        return scaled


    def raw_x_gyro(self):
        return read_word_2c(self.bus, self.i2c_adr, self.regs['GX'], -1)

    def raw_y_gyro(self):
        return read_word_2c(self.bus, self.i2c_adr, self.regs['GY'], -1)

    def raw_z_gyro(self):
        return read_word_2c(self.bus, self.i2c_adr, self.regs['GZ'], -1)

    def raw_gyro(self):     # Get raw measurements from gyroscopes registers
        x = self.raw_x_gyro()
        y = self.raw_y_gyro()
        z = self.raw_z_gyro()
        return [x,y,z]

    def gyro(self):
        raw = self.raw_gyro()
        scaled = [i / self.gyro_scale for i in raw]
        return scaled

class ak8963:
    def __init__(self, bus, i2c_adr=0x68):   # Default i2c address of imu6050 is 64(dec) = 40(hex)
        self.bus = bus  # i2c bus to be used
        self.i2c_adr=i2c_adr # i2c address if ak8963
        self.range_sensor('GYRO',0)

        # Dictionary for ak's registers (low byte, add -1 calling read/write words)
        regs = {'WIA' : 0x00, # Device ID of AKM. It is described in one byte and fixed value
                'INFO' : 0x01, # Device information for AKM
                'ST1' : 0x02, # Bit DRDY (D0) is '1' when data is ready in single measurement mode or self-test mode. It returns '0' when any one of ST2 register or measurement data register (HXL to HZH) is read
                'HXL' : 0x03, # X-axis measurement data lower 8bit
                'HXH' : 0x04, # X-axis measurement data higher 8bit
                'HYL' : 0x05, # You can guess
                'HYH' : 0x06, #
                'HZL' : 0x07, #
                'HZH' : 0x08, #
                'ST2' : 0x09, # Bit (D3) 'Magnetic sensor overflow' [magnetic data is not correct if this is '1'] & Bit (D4) 'Output bit setting' [Mirror data of BIT bit of CNTL1 register]
                'CNTL1' : 0x0A, # Bits (D3-0) 'MODEx' [0001 for single measurement mode] & Bit (D4) 'BIT' [Output bit setting: '0' 14-bit output || '1' 16-bit output]
                'RSV' : 0x0B, # Reserved
                'ASTC' : 0x0C, # Self test
                'TS1' : 0x0D, # Test1: TS1 and TS2 registers are test registers for shipment test. Do not use these registers
                'TS2' : 0x0E, # Test2
                'I2CDIS' : 0x0F, # i2c disable: 00011011 to disable. i2c enabled by default
                'ASAX' : 0x10, # X axis sensitivity adjustment value
                'ASAY' : 0x11, #
                'ASAZ' : 0x12, #
                }
