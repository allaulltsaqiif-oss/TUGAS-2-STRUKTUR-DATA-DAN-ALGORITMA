# Tugas 2 – Praktikum Struktur Data dan Algoritma C
## Implementasi dan Analisis Algoritma Sorting

---

## 📋 Deskripsi
Program CLI berbasis bahasa **C** yang mengimplementasikan dan membandingkan performa berbagai algoritma sorting:

| Kategori | Algoritma | Tipe Data |
|---|---|---|
| Sorting Dasar | Bubble Sort, Insertion Sort, Selection Sort | Integer (1000 data acak) |
| Advance Sorting | Merge Sort, Quick Sort, Shell Sort | String (file `words_en.txt`) |

---

## 📁 Struktur File
```
.
├── sorting.c       # Source code utama
├── words_en.txt    # Dataset kata (letakkan di folder yang sama)
└── README.md
```

---

## ⚙️ Cara Kompilasi & Menjalankan

### Prasyarat
- GCC (GNU Compiler Collection)
- File `words_en.txt` dari [Kaggle – words-en](https://www.kaggle.com/datasets/jiprud/words-en) diletakkan di folder yang sama dengan program

### Kompilasi
```bash
gcc -O2 -Wall -o sorting sorting.c
```

### Menjalankan
```bash
./sorting
```
*(Windows: `sorting.exe`)*

---

## 🖥️ Tampilan Menu
```
========================================
        === MENU UTAMA ===
========================================
  1. Sorting Dasar  (Integer, 1000 data)
  2. Advance Sorting (String, N kata)
  3. Keluar
----------------------------------------
  Pilih menu :
```

### Submenu Sorting Dasar
```
========================================
       === SORTING DASAR ===
========================================
  1. Bubble Sort
  2. Insertion Sort
  3. Selection Sort
  4. Jalankan Semua (Benchmark)
  5. Kembali
```

### Submenu Advance Sorting
```
========================================
       === ADVANCE SORTING ===
========================================
  1. Merge Sort
  2. Quick Sort
  3. Shell Sort
  4. Jalankan Semua (Benchmark)
  5. Kembali
```

---

## 📊 Fitur Program
- ✅ Generate data integer acak dengan `rand()`
- ✅ Baca dataset string dari file `words_en.txt`
- ✅ **Shuffle data** sebelum sorting (metode swap acak)
- ✅ Tampilkan **10 data pertama** sebelum dan sesudah sorting
- ✅ Ukur **waktu eksekusi** dengan `clock()`
- ✅ Mode **Benchmark** untuk menjalankan semua algoritma sekaligus
- ✅ Sorting secara **ascending**
- ✅ Tanpa fungsi sorting bawaan C

---

## 🔍 Penjelasan Algoritma

### Bubble Sort — O(n²)
Membandingkan elemen berdampingan dan menukarnya jika urutan salah. Diulang sampai tidak ada pertukaran.

### Insertion Sort — O(n²)
Membangun array terurut satu per satu dengan menyisipkan tiap elemen ke posisi yang tepat.

### Selection Sort — O(n²)
Menemukan elemen minimum dari sisa array dan menempatkannya di posisi berikutnya.

### Merge Sort — O(n log n)
Membagi array menjadi dua bagian, mengurutkan masing-masing secara rekursif, lalu menggabungkan.

### Quick Sort — O(n log n) rata-rata
Memilih pivot, mempartisi array, lalu mengurutkan dua bagian secara rekursif. Menggunakan **median-of-three** untuk menghindari worst-case.

### Shell Sort — O(n log² n)
Varian Insertion Sort yang membandingkan elemen dengan jarak (gap) tertentu, semakin kecil hingga gap = 1.

---

## 👥 Anggota Kelompok
| No | Nama | NIM |
|---|---|---|
| 1 | ... | ... |
| 2 | ... | ... |
| 3 | ... | ... |
