# 🛠️ Syscalls C Projects

**EN:**  
This repository contains various C projects demonstrating system calls, memory management, multithreading, and steganography.

**TR:**  
Bu depo, sistem çağrıları, bellek yönetimi, çoklu iş parçacığı (thread) kullanımı ve steganografi konularını içeren çeşitli C projelerini barındırır.

---

## 🧟 1. Zombie Simulation / Zombi Simülasyonu

**EN:**  
Simulates a game scenario where zombies enter a room through doors, and slayers try to kill them using multiple threads.

**TR:**  
Kapılardan giren zombilerin bir odayı istila ettiği ve avcıların onları öldürmeye çalıştığı bir oyun senaryosunu çoklu iş parçacıklarıyla simüle eder.

- **Concepts / Konseptler**: Multithreading, shared state, synchronization  
- **Functions / Fonksiyonlar**:
  - `zombieEntered()` – Increase zombie count / Zombi sayısını artırır  
  - `zombieKilled()` – Kill a zombie / Zombiyi öldürür  
  - `doorMan()` – Thread that lets zombies in / Zombi girişini sağlar  
  - `slayer()` – Thread that kills zombies / Zombileri öldürür  

---

## 💻 2. Command Executor / Komut Yürütücü

**EN:**  
A mini shell program that reads user commands, logs them, and executes them. If execution fails, it tries to locate the binary with `which`.

**TR:**  
Kullanıcı komutlarını okuyan, bunları log dosyasına kaydeden ve çalıştırmaya çalışan mini bir shell programıdır. Başarısız olursa `which` komutunu kullanarak yolu bulmaya çalışır.

- **Concepts / Konseptler**: Fork, exec, process control, command parsing  
- **Features / Özellikler**:
  - Command logging to `log.txt` / Komutlar `log.txt`'ye yazılır  
  - `fork()` and `execvp()` used for execution / `fork()` ve `execvp()` ile çalıştırma  
  - Custom fallback using `which` / Komut bulunamazsa `which` ile arama  

---

## 🧠 3. Custom Memory Allocator / Özel Bellek Yöneticisi

**EN:**  
Reimplements `malloc` and `free` with different allocation strategies like First Fit, Best Fit, etc. Uses `sbrk()` to request memory from the OS.

**TR:**  
`malloc` ve `free` fonksiyonlarının farklı tahsis stratejileri (First Fit, Best Fit, vb.) ile yeniden yazımıdır. Bellek tahsisi için `sbrk()` kullanır.

- **Concepts / Konseptler**: Dynamic memory allocation, block splitting/coalescing  
- **Functions / Fonksiyonlar**:
  - `mymalloc()` – Allocates memory / Bellek ayırır  
  - `myfree()` – Frees memory / Belleği serbest bırakır  
  - `split_block()`, `left_coalesce()`, `right_coalesce()` – Memory block operations  

---

## 🖼️ 4. BMP Steganography Tool / BMP Steganografi Aracı

**EN:**  
A tool to hide messages inside 32-bit BMP images using the Least Significant Bit (LSB) method. Encodes 1 character per pixel by using 2 bits from each RGBA channel.

**TR:**  
32-bit BMP görüntülerde En Az Önemli Bit (LSB) yöntemiyle mesaj saklayan bir araç. Her pikselde 1 karakter saklanabilir; her RGBA kanalından 2 bit kullanılır.

- **Concepts / Konseptler**: Steganography, image processing, bitwise operations  
- **Features / Özellikler**:
  - 1 character per pixel / Piksel başına 1 karakter  
  - Minimal impact on image quality / Görüntü kalitesini bozmadan  
  - Simple API: `hidemsg()` and `readmsg()`  

### 🛠️ Example Usage / Örnek Kullanım

```c
Image *img = imread("image.bmp");        // Load BMP image / BMP resmi yükle
hidemsg(img, "Secret");                  // Hide a message / Mesaj gizle
readmsg(img, buffer, 100);               // Read a message / Mesajı oku
```
Works only with 32-bit BMP files
Sadece 32-bit BMP dosyalarında çalışır

## 🧪 Çalışma Ortamı / Runtime Environment

**TR:**  
Projelerde POSIX standartlarına uygun sistem çağrıları kullanılmıştır. Bu nedenle, kodları sorunsuz çalıştırmak için **POSIX uyumlu bir Linux dağıtımı** kullanmanız önerilir. Ayrıca WSL 2 ve macOS gibi POSIX desteği bulunan sistemlerde de test edebilirsiniz.

**EN:**  
The projects use system calls that conform to POSIX standards. Therefore, to run and test the code without issues, it is recommended to use a **POSIX-compliant Linux distribution**. You can also test them on systems like WSL 2 and macOS, which provide POSIX support.

---

### 🧯 Sistem Uyumluluk Tablosu / System Compatibility Table

| Platform         | POSIX Uyumluluğu / POSIX Compatibility | Açıklama / Notes                                   |
|------------------|-----------------------------------------|----------------------------------------------------|
| 🐧 Linux (Ubuntu, Debian, Arch...) | ✅ Yüksek / High             | `glibc` ve çekirdek desteğiyle geniş uyumluluk     |
| 💻 macOS          | ✅ Resmi / Officially certified        | POSIX.1-2001 ve 2008 uyumlu                         |
| 🪟 WSL 2          | ✅ Neredeyse tam / Near-complete       | Gerçek Linux çekirdeği çalıştırır                  |
| 🪟 WSL 1          | ⚠️ Sınırlı / Limited                  | NT çekirdeği ile uyumluluk katmanlı                |
| 🪟 Windows (native) | ❌ Yok / None                         | POSIX desteklemez; sadece derleyici ile çalışabilir|

