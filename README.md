# N9H26K5 1024x600_TFT_LCD Driver

### Description
Just simple VPOST test code 4 HightekVision

### Image Setting
|N|Name|Description|
|---|---|---|
|1|Input Image data format|RGB565|
|2|Output Image data format|RGB888|

### MPU Enviorment
|N|Name|Description|Note|
|---|---|---|---|
|1|ARM MDK|Keil uVision Ver. 5.34.0.0|IDE|
|2|N9H26_NonOS_BSP|2023_02_15 Released|[Link](https://github.com/OpenNuvoton/N9H26_NonOS_BSP)|
|3|LCD Driver|hx8282 +hx8696|Sync LCD Driver|
|4|Original Image|kakao|.png|
|5|Conver Image|KAKAO_RGB565|.dat|

### Output Image
![KakaoTalk_20230515_174227398](https://github.com/keikkang/1024x600_TFT_LCD_N9H26K5/assets/108905975/d4652fc6-54aa-489e-b6e6-91a38c63ab02)

### Debug Image
![image](https://github.com/keikkang/1024x600_TFT_LCD_N9H26K5/assets/108905975/b75aa7ce-f86f-4a75-8cc9-1ee1210ff9b7)

### How to convert Image to C array 
[Open source image converter](https://notisrac.github.io/FileToCArray/)
![image](https://github.com/keikkang/1024x600_TFT_LCD_N9H26K5/assets/108905975/2ef665aa-dfcb-45ea-9b75-64bf9a68e153)

### Turbo Writer Setting
![image](https://github.com/keikkang/1024x600_TFT_LCD_N9H26K5/assets/108905975/3d6ba7d8-4047-4e20-8908-95d2b884c25d)
|N|Name|Description|Note|
|---|---|---|---|
|1|N9H26_NANDLoader_240MHz_Fast.bin|for NAND flash booting|
|2|VPOST.bin|excute code|
