# Tugas 2 — Implementasi dan Analisis Algoritma Sorting
**Mata Kuliah:** Praktikum Struktur Data dan Algoritma C

---

## Deskripsi

Program ini mengimplementasikan dan membandingkan performa enam algoritma sorting yang dibagi menjadi dua kategori:

- **Sorting Dasar** — bekerja pada array integer acak (1.000 data)
- **Advance Sorting** — bekerja pada array string kata bahasa Inggris (hingga 500.000 kata)

Setiap algoritma menampilkan preview data sebelum dan sesudah diurutkan, serta waktu eksekusi dalam milidetik.

---

## Algoritma yang Diimplementasikan

### Sorting Dasar (Integer)
| Algoritma | Kompleksitas Waktu | Keterangan |
|---|---|---|
| Bubble Sort | O(n²) | Membandingkan dan menukar elemen berdekatan secara berulang |
| Insertion Sort | O(n²) | Menyisipkan elemen satu per satu ke posisi yang tepat |
| Selection Sort | O(n²) | Memilih elemen terkecil lalu menempatkannya di awal |

### Advance Sorting (String)
| Algoritma | Kompleksitas Waktu | Keterangan |
|---|---|---|
| Merge Sort | O(n log n) | Divide and conquer; stabil dan konsisten untuk dataset besar |
| Quick Sort | O(n log n) avg | Pivot median-of-three untuk menghindari worst-case |
| Shell Sort | O(n log² n) | Insertion sort dengan gap bertahap |

---

## Struktur File

```
.
├── sorting.c       # Source code utama
├── words_en.txt    # Dataset kata bahasa Inggris (wajib ada)
└── README.md       # Dokumentasi ini
```

> **Penting:** File `words_en.txt` harus berada di direktori yang sama dengan program. Tanpa file ini, menu Advance Sorting tidak dapat dijalankan.

---

## Cara Kompilasi dan Menjalankan

### Kompilasi
```bash
gcc -o sorting sorting.c
```

### Menjalankan
```bash
./sorting
```

---

## Contoh Output

```
  Memuat dataset kata dari 'words_en.txt'...
  Berhasil memuat 370103 kata.

========================================
        === MENU UTAMA ===
========================================
  1. Sorting Dasar  (Integer, 1000 data)
  2. Advance Sorting (String, 370103 kata)
  3. Keluar
----------------------------------------
  Pilih menu :
```

Setelah memilih algoritma:
```
  [Bubble Sort]
  Sebelum Sort : 47821, 3192, 88045, 512, ...
  Sesudah Sort  : 1, 5, 11, 18, ...
  Waktu Eksekusi : 2.3410 ms
```

---

## Konfigurasi

Konstanta berikut dapat diubah di bagian atas `sorting.c`:

| Konstanta | Default | Keterangan |
|---|---|---|
| `INT_DATA_SIZE` | 1000 | Jumlah data integer yang diuji |
| `PREVIEW_COUNT` | 10 | Jumlah elemen yang ditampilkan pada preview |
| `MAX_WORDS` | 500000 | Kapasitas maksimum kata yang dimuat |
| `MAX_WORD_LEN` | 100 | Panjang maksimum satu kata |
| `WORDS_FILE` | `"words_en.txt"` | Nama file dataset kata |

---

## Catatan Teknis

- Perbandingan string menggunakan `strcasecmp` (case-insensitive).
- Merge Sort dan Quick Sort mengalokasikan memori secara dinamis (`malloc`) untuk menghindari stack overflow pada dataset besar.
- Data di-*shuffle* ulang sebelum setiap pengujian agar hasil waktu lebih representatif.
- Fitur **Benchmark** (pilihan 4) menjalankan semua algoritma secara berurutan sehingga perbandingan waktu dapat dilakukan langsung.

---

## Persyaratan Sistem

- Compiler: GCC (versi 5 ke atas direkomendasikan)
- Sistem Operasi: Linux / macOS / Windows (dengan MinGW)
- Fungsi `strcasecmp` tersedia di POSIX. Pengguna Windows perlu mengganti dengan `_stricmp` jika menggunakan MSVC.

## 👥 Anggota Kelompok
| No | Nama | NPM |
|---|---|---|
| 1 | AL AUL TSAQIF | 250810701100034 |
| 2 | MUHAMMAD RAYYAN | ... |
| 3 | IMAM AS-SHADIQ | ... |
