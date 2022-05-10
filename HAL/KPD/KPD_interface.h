/*
 * KPD_interface.h
 *
 *  Created on: Nov 2, 2021
 *      Author: taqwa
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

DIO_ErrorStatus KeyPadInt(void);
DIO_ErrorStatus KeyPadGetPressed(u8 *copy_pu8KeyValue );


#endif /* HAL_KPD_KPD_INTERFACE_H_ */
