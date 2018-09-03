
#ifndef _UTIL_CRC16_H_
#define _UTIL_CRC16_H_

#include "stdint.h"

#define lo8(x) ((x)&0xff) 
#define hi8(x) ((x)>>8)


uint16_t crc16_update(uint16_t crc, uint8_t a){

	int i;

	crc ^= a;

	for (i = 0; i < 8; ++i){

	    if (crc & 1){
			crc = (crc >> 1) ^ 0xA001;
		}
	    	
	    else{
			crc = (crc >> 1);
	    }

	}

	return crc;
}

uint16_t crc_xmodem_update (uint16_t crc, uint8_t data){

        int i;

        crc = crc ^ ((uint16_t)data << 8);

        for (i=0; i<8; i++){

            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;

            else
                crc <<= 1;
        }

        return crc;
}


uint16_t _crc_ccitt_update (uint16_t crc, uint8_t data){

        data ^= lo8 (crc);
        data ^= data << 4;

        return ((((uint16_t) data << 8) | hi8 (crc)) ^ (uint8_t) (data >> 4) 
                ^ ((uint16_t) data << 3));

}


uint8_t _crc_ibutton_update(uint8_t crc, uint8_t data){

	uint8_t i;

	crc = crc ^ data;

	for (i = 0; i < 8; i++){

	    if (crc & 0x01)
	        crc = (crc >> 1) ^ 0x8C;

	    else
	        crc >>= 1;
	}

	return crc;
}


#endif /* _UTIL_CRC16_H_ */
