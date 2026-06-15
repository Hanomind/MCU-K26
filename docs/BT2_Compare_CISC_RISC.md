# BÁO CÁO: SO SÁNH KIẾN TRÚC CISC VÀ RISC

## 1. Giới thiệu

Kiến trúc tập lệnh (ISA) là nền tảng quyết định cách thức hoạt động của bộ xử lý. Hai kiến trúc phổ biến hiện nay là CISC (Complex Instruction Set Computer) và RISC (Reduced Instruction Set Computer).

## 2. Khái niệm cơ bản

### CISC

CISC sử dụng tập lệnh phức tạp với số lượng lệnh lớn. Một lệnh có thể thực hiện nhiều thao tác khác nhau.

Ví dụ: Intel Core, AMD Ryzen.

### RISC

RISC sử dụng tập lệnh đơn giản, mỗi lệnh thường chỉ thực hiện một chức năng duy nhất.

Ví dụ: ARM Cortex-M, ARM Cortex-A, RISC-V.

## 3. Ưu điểm và nhược điểm

### CISC

**Ưu điểm**
- Giảm số lượng lệnh trong chương trình.
- Tương thích phần mềm cao.

**Nhược điểm**
- Phần cứng phức tạp.
- Tiêu thụ điện năng cao.

### RISC

**Ưu điểm**
- Tốc độ xử lý cao.
- Tiêu thụ điện năng thấp.
- Dễ tối ưu Pipeline.

**Nhược điểm**
- Cần nhiều lệnh hơn để thực hiện cùng một tác vụ.

## 4. So sánh CISC và RISC

| Tiêu chí | CISC | RISC |
|-----------|--------|--------|
| Cấu trúc tập lệnh | Phức tạp | Đơn giản |
| Tốc độ xử lý | Thấp hơn | Cao hơn |
| Kích thước chương trình | Nhỏ hơn | Lớn hơn |
| Độ phức tạp phần cứng | Cao | Thấp |
| Ứng dụng | Intel, AMD | ARM, RISC-V |

## 5. Quan điểm cá nhân

Trong lĩnh vực hệ thống nhúng hiện nay, RISC phù hợp hơn do tiêu thụ năng lượng thấp, hiệu suất cao và được sử dụng rộng rãi trên các vi điều khiển ARM như STM32.

## 6. Kết luận

CISC và RISC đều có ưu điểm riêng. Tuy nhiên, với xu hướng phát triển IoT, robot và hệ thống nhúng, RISC đang trở thành lựa chọn phổ biến hơn.