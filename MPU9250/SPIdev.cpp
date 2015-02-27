#include <SPI.h>
#include "SPIdev.h"

#define BUFFSIZE 20

/** Default timeout value for read operations.
 * Set this to 0 to disable timeout detection.
 */
uint16_t SPIdev::readTimeout = SPIDEV_DEFAULT_READ_TIMEOUT;

/** Default constructor.
 */
SPIdev::SPIdev() {
}

/** Read a single bit from an 8-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-7)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t SPIdev::readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout) {
    uint8_t b;
    uint8_t count = readByte(devAddr, regAddr, &b, timeout);
    *data = b & (1 << bitNum);
    return count;
}

/** Read a single bit from a 16-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-15)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t SPIdev::readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout) {
    uint16_t b;
    uint8_t count = readWord(devAddr, regAddr, &b, timeout);
    *data = b & (1 << bitNum);
    return count;
}

/** Read multiple bits from an 8-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t SPIdev::readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout) {
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count, b, r = 0;
    if ((count = readByte(devAddr, regAddr, &b, timeout)) != 0) {
        for (uint8_t i = bitStart; i > bitStart - length; i--) {
            r |= (b & (1 << i));
        }
        r >>= (bitStart - length + 1);
        *data = r;
    }
    return count;
}

/** Read multiple bits from a 16-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-15)
 * @param length Number of bits to read (not more than 16)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Status of read operation (1 = success, 0 = failure, -1 = timeout)
 */
int8_t SPIdev::readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout) {
    // 1101011001101001 read byte
    // fedcba9876543210 bit numbers
    //    xxx           args: bitStart=12, length=3
    //    010           masked
    //           -> 010 shifted
    uint8_t count;
    uint16_t w, r = 0;
    if ((count = readWord(devAddr, regAddr, &w, timeout)) != 0) {
        for (uint8_t i = bitStart; i > bitStart - length; i--) {
            r |= (w & (1 << i));
        }
        r >>= (bitStart - length + 1);
        *data = r;
    }
    return count;
}

/** Read single byte from an 8-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t SPIdev::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout) {
    return readBytes(devAddr, regAddr, 1, data, timeout);
}

/** Read single word from a 16-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr Register regAddr to read from
 * @param data Container for word value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t SPIdev::readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout) {
    return readWords(devAddr, regAddr, 1, data, timeout);
}

/** Read multiple bytes from an 8-bit device register.
 * @param devAddr SPI pin address
 * @param regAddr First register regAddr to read from
 * @param length Number of bytes to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Number of bytes read (0 indicates failure)
 */
int8_t SPIdev::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout) {
    uint8_t buffer[BUFFSIZE];
    buffer[0] = regAddr | 0x80;
    SPI.transfer(devAddr, buffer, length+1);
    memcpy(data, &buffer[1], length);
    return length;
}

/** Read multiple words from a 16-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr First register regAddr to read from
 * @param length Number of words to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in SPIdev::readTimeout)
 * @return Number of words read (0 indicates failure)
 */
int8_t SPIdev::readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout) {
    readBytes(devAddr, regAddr, length*2, (uint8_t*)data, timeout);
    return length;
}

/** write a single bit in an 8-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool SPIdev::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    readByte(devAddr, regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return writeByte(devAddr, regAddr, b);
}

/** write a single bit in a 16-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-15)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool SPIdev::writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data) {
    uint16_t w;
    readWord(devAddr, regAddr, &w);
    w = (data != 0) ? (w | (1 << bitNum)) : (w & ~(1 << bitNum));
    return writeWord(devAddr, regAddr, w);
}

/** Write multiple bits in an 8-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool SPIdev::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 01000000 shift left (8 - length)    ]
    // 00001000 shift right (7 - bitStart) ] --- two shifts ensure all non-important bits are 0
    // 11100011 mask byte
    // 10101111 original value (sample)
    // 10100011 original & mask
    // 10101011 masked | value
    uint8_t b;
    if (readByte(devAddr, regAddr, &b) != 0) {
        //uint8_t mask = (0xFF << (8 - length)) | (0xFF >> (bitStart + length - 1));
        uint8_t mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return writeByte(devAddr, regAddr, b);
    } else {
        return false;
    }
}

/** Write multiple bits in a 16-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-15)
 * @param length Number of bits to write (not more than 16)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool SPIdev::writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data) {
    //              010 value to write
    // fedcba9876543210 bit numbers
    //    xxx           args: bitStart=12, length=3
    // 01000000         shift left (16 - length)    ]
    // 00001000         shift right (15 - bitStart) ] --- two shifts ensure all non-important bits are 0
    // 11100011         mask byte
    // 10101111         original value (sample)
    // 10100011         original & mask
    // 10101011         masked | value
    uint16_t w;
    if (readWord(devAddr, regAddr, &w) != 0) {
        //uint16_t mask = (0xFFFF << (16 - length)) | (0xFFFF >> (bitStart + length - 1));
        uint16_t mask = (0xFFFF << (bitStart + 1)) | 0xFFFF >> ((16 - bitStart) + length - 1);
        data <<= (16 - length);
        data >>= (15 - bitStart);
        w &= mask;
        w |= data;
        return writeWord(devAddr, regAddr, w);
    } else {
        return false;
    }
}

/** Write single byte to an 8-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
bool SPIdev::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    return writeBytes(devAddr, regAddr, 1, &data);
}

/** Write single word to a 16-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr Register address to write to
 * @param data New word value to write
 * @return Status of operation (true = success)
 */
bool SPIdev::writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data) {
    return writeWords(devAddr, regAddr, 1, &data);
}

/** Write multiple bytes to an 8-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr First register address to write to
 * @param length Number of bytes to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool SPIdev::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data) {
    uint8_t buffer[BUFFSIZE];
    digitalWrite(devAddr, LOW);
    buffer[0] = regAddr;
    memcpy(&buffer[1], data, length);
    SPI.transfer(devAddr, buffer, length+1);
    digitalWrite(devAddr, HIGH);
    return true;
}

/** Write multiple words to a 16-bit device register.
 * @param devAddr SPI pin address or Slave Select pin if SPI
 * @param regAddr First register address to write to
 * @param length Number of words to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool SPIdev::writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t* data) {
    return writeBytes(devAddr, regAddr, length, (uint8_t*)data);
}
