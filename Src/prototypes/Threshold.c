//Threshold
uint32_t thr_soil = 0;
uint16_t thr_lux = 0;
float thr_RH_up = 100;
float thr_RH_low = 0;
float thr_TEMP = 50;

void Threshold(){
	//light
	if(lux < thr_lux)
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
	else if(lux > thr_lux + 200)
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);	
	//pump
	if(result_soil < thr_soil || (thr_RH_low > Humidity))
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
	//vent
	if(thr_RH_up < Humidity || Temperature > thr_TEMP)
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	else		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
}
