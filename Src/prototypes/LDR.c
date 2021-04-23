uint32_t result;
uint32_t lux;
char ldr[4] = {0};

void LDR_GetValue()
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	result = HAL_ADC_GetValue(&hadc1); 	
	if(((float)result - (float)400 )* 0.695 < 0)
		lux = 0;
	else
		lux = ((float)result - (float)400 )* 0.695;
	sprintf(ldr,"%d", lux);
}
