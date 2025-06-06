# STM8_SPL_Tim_UART

## Giới thiệu

**STM8_SPL_Tim_UART** là dự án điều khiển quạt sử dụng vi điều khiển STM8, lập trình với thư viện SPL (Standard Peripheral Library). Dự án hỗ trợ các chức năng:
- Điều khiển tốc độ quạt (3 mức)
- Hẹn giờ tắt quạt (1h, 2h, 4h, 8h)
- Điều khiển chế độ quay (swing)
- Nhận tín hiệu từ remote hồng ngoại (IR) chuẩn NEC
- Điều khiển bằng nút nhấn vật lý
- Báo hiệu bằng buzzer và LED

## Phần cứng

- Vi điều khiển: STM8 (ví dụ STM8S003F3P6)
- Quạt điện (điều khiển qua relay hoặc transistor)
- Remote IR chuẩn NEC
- Các nút nhấn: OFF, SPEED, TIMER, SWING
- LED báo trạng thái hẹn giờ, swing
- Buzzer cảnh báo

## Sơ đồ chân (tham khảo)

| Chức năng      | STM8 Pin      | Ghi chú           |
|----------------|---------------|-------------------|
| IR Receiver    | PD4           | Ngắt ngoài        |
| Fan Low        | PD3           | Điều khiển quạt   |
| Fan Mid        | PD2           |                   |
| Fan High       | PD5           |                   |
| Buzzer         | PD1           |                   |
| Motor Swing    | PC3           |                   |
| LED 1H         | PC4           |                   |
| LED 2H         | PC5           |                   |
| LED 4H         | PC6           |                   |
| LED 8H         | PC7           |                   |
| LED Swing      | PB5           |                   |
| BTN OFF        | PA3           | Nút nhấn vật lý   |
| BTN SPEED      | PD6           |                   |
| BTN TIMER      | PA2           |                   |
| BTN SWING      | PA1           |                   |

## Chức năng phần mềm

- **Điều khiển tốc độ quạt:**  
  Nhấn nút SPEED hoặc remote để chuyển đổi giữa các mức 1-2-3.

- **Hẹn giờ:**  
  Nhấn TIMER để chọn thời gian tắt (1h, 2h, 4h, 8h). LED tương ứng sẽ sáng.

- **Tắt quạt:**  
  Nhấn OFF hoặc remote để tắt quạt và hẹn giờ.

- **Chế độ quay (Swing):**  
  Nhấn SWING để bật/tắt chế độ quay.

- **Nhận tín hiệu IR:**  
  Giải mã tín hiệu remote chuẩn NEC, thực hiện lệnh tương ứng.

- **Buzzer:**  
  Phát âm báo khi có thao tác điều khiển.

## Cấu trúc mã nguồn

- `main.c`: Toàn bộ logic điều khiển, xử lý ngắt, giải mã IR, điều khiển quạt, LED, buzzer, nút nhấn.
- Sử dụng các hàm tách biệt:  
  - `HandleIR()`: Xử lý tín hiệu IR  
  - `HandleButtonAndIRCode()`: Xử lý nút nhấn và mã IR  
  - `HandleTimerAndLED()`: Xử lý hẹn giờ và trạng thái LED  
  - `Fan_SetSpeed()`, `BUZZER_Config()`, `Delay()`, v.v.

## Biên dịch & nạp chương trình

- Sử dụng PlatformIO hoặc SDCC với Makefile.
- Kết nối mạch với ST-Link hoặc USB-UART để nạp chương trình.

## Ghi chú

- Có thể mở rộng thêm chức năng UART để debug.
- Code đã tối ưu, dễ bảo trì, dễ mở rộng.
- Đảm bảo kết nối phần cứng đúng như sơ đồ.

---

**Tác giả:**  
- [linh-danh-thue-KN](https://github.com/linh-danh-thue-KN)

**Mọi góp ý, báo lỗi xin gửi issue trên GitHub.**
