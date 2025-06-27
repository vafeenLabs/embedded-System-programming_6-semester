#

## task1 

Установка platformio для компиляции
```
pip install platformio
```

Загрузка прошивки на ESP
```
esptool.exe --chip esp32 --port COM5 write-flash 0x1000 firmware.bin
```

Компиляция проекта:
```
pio run
```

Монитор блютуза:
```
platformio device monitor —port COM7 —baud 115200
```

## task2

Загрузка прошивки на ESP
```
esptool.exe --chip esp32 --port COM5 write-flash 0x1000 firmware.bin
```

Компиляция и загрузка прошивки на Arduino
```
pio run -t upload
```