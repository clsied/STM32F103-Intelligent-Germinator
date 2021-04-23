# STM32F103-Intelligent-Germinator

## Description

Using [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) and [Android Studio](https://developer.android.com/studio) to **drive STM32F103 board**

## Android Application

### MainActivity.java
+ **Provided as a prototype**
+ Have added some **Bluetooth functions**, and hope they are helpful  
+ Have added some comments as reminders to put your tailor-made functions


## STM32 Source Codes

### main.c
+ As you may know, STM32CubeMx provide easier way for STM32 board user to settle their configuration
+ Consequently, we merely **include the user implementation codes as reference**
+ Some details i.e. pin setting and communication protocol used are not included, you can have your own setting later

### stm32f1xx_it.c
+ Similar as main.c, we **merely include the user implementation codes** 
+ i.e. **extern variable and global interrupt setting for HC05**

### prototypes
+ In [prototypes folder](https://github.com/clsied/STM32F103-Intelligent-Germinator/tree/main/Src/prototypes), **provided several driven prototype of sensors**
+ Have added all the require variable and function in single **[sensor name].c** file
+ Have added **Threshold.c** for simple threshold setting

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure your updates or additions do not have major mistakes.

## License
[MIT](https://choosealicense.com/licenses/mit/)
