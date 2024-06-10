/*

  ******************************************************************************
  * @file 			( фаил ):   FM24xx.c
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	author: Golinskiy Konstantin	e-mail: golinskiy.konstantin@gmail.com
  ******************************************************************************
  
*/

/* Includes ----------------------------------------------------------*/
#include "FM24xx.h"

/*
	******************************************************************************
	* @brief	 ( описание ):  Отчиска всего чипа ( 0xFF )
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void FM24xx_erase_chip( void ){
	
	uint8_t data = 0xFF;
	
	#if defined (WP_GPIO_Port)
		HAL_GPIO_WritePin ( WP_GPIO_Port, WP_Pin, GPIO_PIN_RESET );	// отключаем защиту от записи
	#endif
		
		for( uint32_t i = 0; i < FM24XX_MAX_MEM_ADDRESS; i++){
			#if defined(FM2401) || defined(FM2402)
				HAL_I2C_Mem_Write( &FM24XX_I2C,  FM24XX_I2C_ADDR, i, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY );
			#else
				HAL_I2C_Mem_Write( &FM24XX_I2C,  FM24XX_I2C_ADDR, i, I2C_MEMADD_SIZE_16BIT, &data, 1, HAL_MAX_DELAY );
			#endif
		}
		
	#if defined (WP_GPIO_Port)
		HAL_GPIO_WritePin ( WP_GPIO_Port, WP_Pin, GPIO_PIN_SET );	// включаем защиту от записи
	#endif
	
}
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  Функция для записи в память массив данных ( uint8_t )
	* @param	( параметры ):	1- адрес в памяти значение от 0 до FM24XX_MAX_MEM_ADDRESS
								2- сам массив с данными
								3- размер массива ( или части )в байтах, сколько хотим записать байт 
	* @return  ( возвращает ):	вернет 0 если запись не произошла ( передали адрес и размер массива больше чем память чипа )
								вернет ( если запись удалась ) адресс на котором зокончили запись, удобно для последуещей записи с конца.

	******************************************************************************
*/
uint16_t FM24xx_write( uint16_t addMem_write, uint8_t *data_write, uint16_t size_write){
	
	if( (addMem_write + size_write) < FM24XX_MAX_MEM_ADDRESS ){
		
		#if defined (WP_GPIO_Port)
			HAL_GPIO_WritePin ( WP_GPIO_Port, WP_Pin, GPIO_PIN_RESET );	// отключаем защиту от записи
		#endif
					
		#if defined(FM2401) || defined(FM2402)
			HAL_I2C_Mem_Write( &FM24XX_I2C,  FM24XX_I2C_ADDR, addMem_write, I2C_MEMADD_SIZE_8BIT, (uint8_t*)data_write, size_write, HAL_MAX_DELAY );
		#else
			HAL_I2C_Mem_Write( &FM24XX_I2C,  FM24XX_I2C_ADDR, addMem_write, I2C_MEMADD_SIZE_16BIT, (uint8_t*)data_write, size_write, HAL_MAX_DELAY );
		#endif
					
		#if defined (WP_GPIO_Port)
			HAL_GPIO_WritePin ( WP_GPIO_Port, WP_Pin, GPIO_PIN_SET );	// включаем защиту от записи
		#endif
		
		return addMem_write + size_write;
	}
	else{
		return 0;
	}
}
//----------------------------------------------------------------------------------


/*
	******************************************************************************
	* @brief	 ( описание ):  Функция для чтения из памяти в массив данных ( uint8_t )
	* @param	( параметры ):	1- адрес в памяти значение от 0 до FM24XX_MAX_MEM_ADDRESS
								2- сам массив для данных
								3- размер массива ( или части )в байтах, сколько хотим считать байт 
	* @return  ( возвращает ):	вернет 0 если чтение не произошло ( передали адрес и размер массива больше чем память чипа )
								вернет ( если чтение удалось ) адресс на котором зокончили чтение, удобно для последуещего чтения с конца.

	******************************************************************************
*/
uint16_t FM24xx_read( uint16_t addMem_read, uint8_t *data_read, uint16_t size_read){
	
	if( (addMem_read + size_read) < FM24XX_MAX_MEM_ADDRESS ){
				
		#if defined(FM2401) || defined(FM2402)
			HAL_I2C_Mem_Read( &FM24XX_I2C,  FM24XX_I2C_ADDR, addMem_read, I2C_MEMADD_SIZE_8BIT, (uint8_t*)data_read, size_read, HAL_MAX_DELAY );
		#else
			HAL_I2C_Mem_Read( &FM24XX_I2C,  FM24XX_I2C_ADDR, addMem_read, I2C_MEMADD_SIZE_16BIT, (uint8_t*)data_read, size_read, HAL_MAX_DELAY );
		#endif
		
		return addMem_read + size_read;
	}
	else{
		return 0;
	}
}
//----------------------------------------------------------------------------------------


/************************ (C) COPYRIGHT GKP *****END OF FILE****/
