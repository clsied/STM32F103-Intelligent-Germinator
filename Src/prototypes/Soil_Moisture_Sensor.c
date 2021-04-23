uint32_t result_soil;
uint32_t soil_moisture;
char soil[4] = {0};

void Soil_GetValue()
{
	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, 1000);
	result_soil = HAL_ADC_GetValue(&hadc2); 
	
	if(result_soil < 1150)
		result_soil = 100;
	else if(result_soil > 3250)
		result_soil = 0;
	else
		result_soil =  ((float)2 / (float)23)*((float)3250 - (float)result_soil);
	
	sprintf(soil,"%d", result_soil);
}
