# BATTLE BOT

Repo này sẽ bao gồm firmware điều khiển robot ( dựa trên chip NRF51822 trên Board VBLUno) với [mbed-cli](https://github.com/ARMmbed/mbed-cli).

THIẾT LẬP MÔI TRƯỜNG
----------------------

Để build được ứng dụng, trước hết ta phải cài đặt các phần mềm như:
* [CMake](http://www.cmake.org/download/).
* [mbed-cli](https://github.com/ARMmbed/mbed-cli). Please note that **mbed-cli has its own set of dependencies**, listed in the installation instructions.
* [Python](https://www.python.org/downloads/).
* [ARM GCC toolchain](https://gnu-mcu-eclipse.github.io/toolchain/arm/install/).
* Giả lập serial monitor (ví dụ screen, pySerial)

HARDWARE
--------

Về hardware chúng ta sẽ sử dụng board [VBLUno](https://vngiotlab.github.io/vbluno/vi/mydoc_introduction_vi.html). do VNG sản xuất dựa trên chip NRF51822 của NORDIC.

BUILD VÀ TEST CHƯƠNG TRÌNH
---------------------------

__Để build một chương trình dựa trên Mbed OS ta thực hiện các bước như sau:__
1. CLone về dự án ( ví dụ như bot battle)


```
git clone https://github.com/iotmakervn/bot-battle-fw.git
```

Hoặc là bạn có thể tạo một dự án mẫu bằng lênh


```
mbed new NameProjec	
```

2. Di chuyển đến thư mục chứa dự án.

```
cd bot-battle-fw
```

3. Update source tree

```
mbed update
```

4. Thiết lập toolchain mặc định

```
mbed toolchain GCC_ARM
```

5. Thiết lập target mặc định ( lựa chọn chip)

Chương trình sẽ chạy trên BOARD VBLUno nên target sẽ chọn là **VBLUNO51_LEGACY**

```
mbed target VBLUNO51_LEGACY
```

6. Apply patch for 4 PWM

```
git apply pwm.patch
```

7. Compile chương trình

```
mbed compile
```
hoặc `make flash`

8. Sau khi Compile thành công, file HEX được tạo sẽ nằm trong thư mục có cấu trúc như sau: ```BUILD/<target-name>/<toolchain>```

	Trong project này thư mục sẽ là ```BUILD/VBLUNO51_LEGACY/GCC_ARM```

	**Lưu ý** Tùy vào target mà file được tạo có thể là file `.HEX` hoặc `.BIN`

8. Kết nối Board VBLUno với máy tính bằng cổng COM. Thư mục DAPLINK sẽ xuất hiện và bạn chỉ cần copy file HEX vừa được tạo vào trong thư mục đó để nạp chương trình

9. Reset lại chip.

### GIAO THỨC BLE ĐƯỢC DÙNG TRONG ỨNG DỤNG BOTBATTLE


#### Service

UUID `A000` có 1 Characteristic

#### Characteristic

Characteristic UUID: `0xA001`, size 1 byte, Read, Write - dùng để gởi command


*Command sẽ được so sánh để thực hiện các chức năng như sau:*

| Giá trị    | chức năng                                      |
| ---------- | :-------------:                                |
| 0x0n       | chạy tới với tốc độ n (0..F), ví dụ 0x01, 0x05 |
| 0x1n       | xoay trái tốc độ n (0..F), ví dụ 0x11, 0x1F    |
| 0x2n       | xoay phải tốc độ n (0..F)                      |
| 0x3n       | chạy lùi tốc độ n (0..F)                       |
| 0x50       | Dừng                                           |
| 0x61       | turn on reverse robot                          |
| 0x60       | turn off reverse robot                         |
| 0x70       | turn on skill Q                                |
| 0x71       | turn on skill W                                |
| 0x72       | turn on skill E                                |
| 0x73       | turn on skill R                                |
| 0b10abyyyyy| lái từng bánh xe, b=0-left/1-right, a=forwad/backward, yyyy = speed                           |
| 0x41       | Vào chế độ tự động xoay khi mất kết nối        |
| 0x40       | Thoát chế độ tự động xoay khi mất kết nối      |
