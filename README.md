# TUBES-Analisis-Kompleksitas-Algoritma
Smart Parking Analyzer adalah aplikasi simulasi sistem parkir yang dikembangkan untuk membandingkan efisiensi waktu eksekusi (running time) antara dua pendekatan algoritma: Iteratif dan Rekursif. Aplikasi ini memvisualisasikan data dalam bentuk grafik real-time untuk membantu analisis kompleksitas waktu Big-O. Disusun untuk memenuhi Tugas Besar Analisis Kompleksitas Algoritma (AKA).


 DISUSUN OLEH
- BAGAS BINTANG SAPUTRO (103072400078) Kelas:IF-04-02
- MUHAMMAD ZAKI OKTARUNA (103072400001) Kelas: IF-04-02
- WAHYU PUJI RISKI PURWANTO (103072400050) Kelas: IF-04-02

UNIVERSITAS TELKOM SURABAYA


Dalam pengembangan sistem parkir berskala besar (ribuan hingga jutaan slot), kecepatan pengecekan ketersediaan slot sangat krusial. Proyek ini bertujuan untuk membuktikan secara empiris perbedaan performa antara:
1.Pendekatan Iteratif: Menggunakan perulangan (for/while).
2.Pendekatan Rekursif: Menggunakan pemanggilan fungsi diri sendiri (disimulasikan untuk stabilitas memori).
Aplikasi ini mengukur waktu eksekusi dalam milidetik (ms) dan menampilkannya dalam grafik perbandingan.

Fitur Utama Input Slot Tanpa Batas: Mendukung input jumlah slot ($N$) dalam skala besar (misal: 10.000, 100.000, hingga 1.000.000) tanpa crash (Force Close).Visualisasi Grafik (Qt Charts):Grafik garis (Line Chart) untuk membandingkan Iteratif (Biru) vs Rekursif (Merah).Grid kotak-kotak dan data points untuk kemudahan pembacaan.Pengukuran Waktu Presisi: Menggunakan std::chrono::high_resolution_clock untuk akurasi tinggi.Anti-Stack Overflow: Menggunakan metode "Simulasi Rekursif" untuk mencegah memori penuh saat input angka besar, namun tetap mempertahankan karakteristik overhead waktu rekursif.Dark Mode UI: Antarmuka pengguna yang modern dan nyaman di mata.

Analisis Algoritma
1. Algoritma IteratifMenggunakan pendekatan looping sederhana.Kompleksitas Waktu: O(N)- Linear.
   Karakteristik: Sangat cepat dan efisien memori. Dalam grafik, garis ini cenderung datar atau naik sangat perlahan.

2.Algoritma Rekursif (Simulasi)
Menggunakan pendekatan beban kerja bertingkat untuk meniru perilaku rekursif yang memakan resource.
Kompleksitas Waktu: O(N x c)- Linear dengan konstanta besar.
Karakteristik: Lebih lambat karena adanya overhead proses. Dalam grafik, garis ini akan menanjak lebih tajam dibanding iteratif.

Teknologi yang Digunakan
1.Bahasa Pemrograman: C++ (Standard C++17)
2.Framework GUI: Qt 6.10.1 (Qt Widgets)
3.Library Visualisasi: Qt Charts
4.Compiler: MinGW 64-bit
5.IDE: Qt Creator (opsional sesuai kenyamanan pribadi)

Instalasi dan Penggunaan
Cara Menjalankan 
1.Unduh folder Release/Deploy yang sudah disediakan (file .zip).
2.Ekstrak folder tersebut.
3.Buka folder hasil ekstrak, lalu jalankan file Tubes_aka_fix.exe.
4.Aplikasi siap digunakan tanpa perlu instalasi Qt.

Cara Kompilasi (Developer)
1.Pastikan Qt Creator dan Qt 6.x sudah terinstall.
2.Buka file Tubes_aka_fix.pro menggunakan Qt Creator.
3.Konfigurasi Project ke mode Release.
4.Tekan tombol Build (Palu) atau Run (Play Hijau).

susunan folder
Tubes_aka_fix/
├── main.cpp           # Logika utama (Algoritma & Chart)
├── mainwindow.cpp     # Implementasi Window (jika dipakai)
├── mainwindow.h       # Header Window
├── mainwindow.ui      # Desain UI (XML)
├── Tubes_aka_fix.pro  # Konfigurasi Project Qt
└── README.md          # Dokumentasi ini
