#!/usr/bin/env python
import smbus

def ini2c(ind = 1):    #Open the i2c bus
    return smbus.SMBus(ind)    # bus = smbus.SMBus(!1) for !(Revision 2 boards)

# Functions to read bytes, words, and 2complement words
def read_byte(bus, i2c_adr, reg_adr): #Read 8 bit register (reg_adr) from i2c device  (i2c_adr)
    return bus.read_byte_data(i2c_adr, reg_adr)

def read_word (bus, i2c_adr, low_reg_adr, offset=1): # Read a 16 bit word adding two 8 bit registers (low_reg_adr+offset & low_reg_adr)
    low = bus.read_byte_data(i2c_adr, low_reg_adr)  # Read 8 LSB from low_reg_adr
    high = bus.read_byte_data(i2c_adr, low_reg_adr+offset) # Read 8 MSB from low_reg_adr + offset (usually +1, but could be -1)
    val = (high << 8) + low # Add the bytes together
    return val

def read_word_2c(bus, i2c_adr, low_reg_adr, offset=1): # Read a word using the previous function and gives 2c complement
    val = read_word(bus, i2c_adr, low_reg_adr, offset)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val

# Functions to write bytes, words, and 12 bit values with zeros as MSBs to fit two 8 bit registers (16bits)
def write_byte(bus, i2c_adr, reg_adr, data): # Write 8 bit register (to reg_adr) of i2c device  (i2c_adr)
    if (data > 0xff):    # Raise exception if data is greater than 8 (0xff) (1111 1111)
        print('write_byte: data to write does not fit in 8 bit')
        raise ValueError
    bus.write_byte_data(i2c_adr, reg_adr, data)

def write_12word (bus, i2c_adr, low_reg_adr, data, offset=1): # Write a 12 bit word in two different 8 bit registers (the high one is 0x0000XXXX)
    if (data > 0xfff):    # Raise exception if data is greater than 4095 (0xfff) (1111 1111 1111)
        print('write_12word: data to write does not fit in 12 bit')
        raise ValueError
    low = data & 0xff # low = 8 LSB from data
    high = (data >> 8) & 0xff # high = 8 MSB from data
    bus.write_byte_data(i2c_adr, low_reg_adr, low)    # Write 8 LSB in low_reg_adr register of i2c_adr
    bus.write_byte_data(i2c_adr, low_reg_adr+offset, high) # Write 8 MSB in (low_reg_adr + offset) register of i2c_adr

def write_16word (bus, i2c_adr, low_reg_adr, data, offset=1): # Write a 16 bit word in two different 8 bit registers
    if (data > 0xffff):    # Raise exception if data is greater than (0xffff) (1111 1111 1111 1111)
        print('write_16word: data to write does not fit in 16 bit')
        raise ValueError
    low = data & 0xff    # low = 8 LSB from data
    high = (data >> 8) & 0xff    # high = 8 MSB from data
    bus.write_byte_data(i2c_adr, low_reg_adr, low)    # Write 8 LSB in low_reg_adr register of i2c_adr
    bus.write_byte_data(i2c_adr, low_reg_adr+offset, high) # Write 8 MSB in (low_reg_adr + offset) register of i2c_adr
