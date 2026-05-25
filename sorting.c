/*
 * ============================================================
 *  Tugas 2 Praktikum Struktur Data dan Algoritma C
 *  Implementasi dan Analisis Algoritma Sorting
 * ============================================================
 *  Kompilasi : gcc -o sorting sorting.c
 *  Jalankan  : ./sorting
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
 *  KONFIGURASI
 * ============================================================ */
#define INT_DATA_SIZE   1000          /* jumlah data integer acak */
#define PREVIEW_COUNT   10            /* jumlah data yang ditampilkan */
#define MAX_WORDS       500000        /* kapasitas maksimum kata dari file */
#define MAX_WORD_LEN    100           /* panjang maksimum satu kata */
#define WORDS_FILE      "words_en.txt"

/* ============================================================
 *  WARNA TERMINAL (ANSI)
 * ============================================================ */
#define RESET   "\033[0m"       // Reset warna
#define BOLD    "\033[1m"       // Teks tebal
#define CYAN    "\033[1;36m"    // Warna cyan untuk judul
#define GREEN   "\033[1;32m"    // Warna hijau untuk hasil sukses
#define YELLOW  "\033[1;33m"    // Warna kuning untuk label
#define RED     "\033[1;31m"    // Warna merah untuk error
#define MAGENTA "\033[1;35m"    // Warna magenta untuk benchmark
#define WHITE   "\033[1;37m"    // Warna putih untuk menu utama

/* ============================================================
 *  UTILITAS UMUM
 * ============================================================ */

/* Cetak garis pemisah */
void print_line(char c, int len) {
    for (int i = 0; i < len; i++) putchar(c);
    putchar('\n');
}

/* Swap dua integer */
void swap_int(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

/* Swap dua string */
void swap_str(char *a, char *b) {
    char tmp[MAX_WORD_LEN];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

/* Salin array integer */
void copy_int_arr(int *dst, const int *src, int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* Salin array string */
void copy_str_arr(char dst[][MAX_WORD_LEN], char src[][MAX_WORD_LEN], int n) {
    for (int i = 0; i < n; i++) strcpy(dst[i], src[i]);
}

/* Tampilkan preview array integer */
void preview_int(const char *label, int *arr, int n, int preview) {
    int show = (preview < n) ? preview : n;
    printf("%s%s%s : ", YELLOW, label, RESET);
    for (int i = 0; i < show; i++) {
        printf("%d", arr[i]);
        if (i < show - 1) printf(", ");
    }
    if (n > preview) printf(", ... (%d data total)", n);
    printf("\n");
}

/* Tampilkan preview array string */
void preview_str(const char *label, char arr[][MAX_WORD_LEN], int n, int preview) {
    int show = (preview < n) ? preview : n;
    printf("%s%s%s : ", YELLOW, label, RESET);
    for (int i = 0; i < show; i++) {
        printf("%s", arr[i]);
        if (i < show - 1) printf(", ");
    }
    if (n > preview) printf(", ... (%d kata total)", n);
    printf("\n");
}

/* Hitung durasi dalam milidetik */
double elapsed_ms(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
}

/* ============================================================
 *  GENERATE & SHUFFLE DATA INTEGER
 * ============================================================ */

void generate_random_int(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000 + 1;
}

void shuffle_int(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap_int(&arr[i], &arr[j]);
    }
}

/* ============================================================
 *  LOAD & SHUFFLE DATA STRING
 * ============================================================ */

int load_words(char words[][MAX_WORD_LEN], int max) {
    FILE *fp = fopen(WORDS_FILE, "r");
    if (!fp) {
        printf(RED "  [ERROR] File '%s' tidak ditemukan!\n" RESET, WORDS_FILE);
        printf("  Pastikan file words_en.txt berada di direktori yang sama dengan program.\n");
        return -1;
    }
    int count = 0;
    while (count < max && fscanf(fp, "%99s", words[count]) == 1)
        count++;
    fclose(fp);
    return count;
}

void shuffle_str(char arr[][MAX_WORD_LEN], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap_str(arr[i], arr[j]);
    }
}

/* ============================================================
 *  SORTING DASAR — INTEGER
 * ============================================================ */

/* --- Bubble Sort --- */
void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                swap_int(&arr[j], &arr[j + 1]);
}

/* --- Insertion Sort --- */
void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* --- Selection Sort --- */
void selection_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap_int(&arr[i], &arr[min_idx]);
    }
}

/* ============================================================
 *  ADVANCE SORTING — STRING
 * ============================================================ */

/* --- Merge Sort (string) --- */
void merge_str(char arr[][MAX_WORD_LEN], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    /* Buffer dinamis untuk menghindari stack overflow pada dataset besar */
    char (*L)[MAX_WORD_LEN] = malloc(n1 * MAX_WORD_LEN);
    char (*R)[MAX_WORD_LEN] = malloc(n2 * MAX_WORD_LEN);
    if (!L || !R) { free(L); free(R); return; }

    for (int i = 0; i < n1; i++) strcpy(L[i], arr[l + i]);
    for (int j = 0; j < n2; j++) strcpy(R[j], arr[m + 1 + j]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcasecmp(L[i], R[j]) <= 0)
            strcpy(arr[k++], L[i++]);
        else
            strcpy(arr[k++], R[j++]);
    }
    while (i < n1) strcpy(arr[k++], L[i++]);
    while (j < n2) strcpy(arr[k++], R[j++]);

    free(L); free(R);
}

void merge_sort_str(char arr[][MAX_WORD_LEN], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_str(arr, l, m);
        merge_sort_str(arr, m + 1, r);
        merge_str(arr, l, m, r);
    }
}

/* --- Quick Sort (string) --- */
int partition_str(char arr[][MAX_WORD_LEN], int low, int high) {
    char pivot[MAX_WORD_LEN];
    strcpy(pivot, arr[high]);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcasecmp(arr[j], pivot) <= 0) {
            i++;
            swap_str(arr[i], arr[j]);
        }
    }
    swap_str(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_str(char arr[][MAX_WORD_LEN], int low, int high) {
    if (low < high) {
        /* Median-of-three pivot untuk menghindari worst-case pada data terurut */
        int mid = low + (high - low) / 2;
        if (strcasecmp(arr[low], arr[mid]) > 0) swap_str(arr[low], arr[mid]);
        if (strcasecmp(arr[low], arr[high]) > 0) swap_str(arr[low], arr[high]);
        if (strcasecmp(arr[mid], arr[high]) > 0) swap_str(arr[mid], arr[high]);
        swap_str(arr[mid], arr[high]);   /* pindahkan pivot ke high */

        int pi = partition_str(arr, low, high);
        quick_sort_str(arr, low, pi - 1);
        quick_sort_str(arr, pi + 1, high);
    }
}

/* --- Shell Sort (string) --- */
void shell_sort_str(char arr[][MAX_WORD_LEN], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char temp[MAX_WORD_LEN];
            strcpy(temp, arr[i]);
            int j = i;
            while (j >= gap && strcasecmp(arr[j - gap], temp) > 0) {
                strcpy(arr[j], arr[j - gap]);
                j -= gap;
            }
            strcpy(arr[j], temp);
        }
    }
}

/* ============================================================
 *  RUNNER — jalankan satu algoritma dan tampilkan hasilnya
 * ============================================================ */

void run_basic_sort(const char *name, void (*sort_fn)(int *, int),
                    const int *original, int n) {
    printf("\n" CYAN "  [%s]" RESET "\n", name);

    int *arr = malloc(n * sizeof(int));
    if (!arr) { printf(RED "  Alokasi memori gagal!\n" RESET); return; }
    copy_int_arr(arr, original, n);

    /* Shuffle sebelum sorting */
    shuffle_int(arr, n);
    preview_int("  Sebelum Sort", arr, n, PREVIEW_COUNT);

    clock_t start = clock();
    sort_fn(arr, n);
    clock_t end = clock();

    preview_int("  Sesudah Sort ", arr, n, PREVIEW_COUNT);
    printf(GREEN "  Waktu Eksekusi : %.4f ms\n" RESET, elapsed_ms(start, end));

    free(arr);
}

void run_advance_sort_mg(const char *name,
                         char words[][MAX_WORD_LEN], int n) {
    printf("\n" CYAN "  [%s]" RESET "\n", name);

    /* Alokasi buffer sementara */
    char (*arr)[MAX_WORD_LEN] = malloc(n * MAX_WORD_LEN);
    if (!arr) { printf(RED "  Alokasi memori gagal!\n" RESET); return; }
    copy_str_arr(arr, words, n);
    shuffle_str(arr, n);
    preview_str("  Sebelum Sort", arr, n, PREVIEW_COUNT);

    clock_t start = clock();
    merge_sort_str(arr, 0, n - 1);
    clock_t end = clock();

    preview_str("  Sesudah Sort ", arr, n, PREVIEW_COUNT);
    printf(GREEN "  Waktu Eksekusi : %.4f ms\n" RESET, elapsed_ms(start, end));
    free(arr);
}

void run_advance_sort_qs(const char *name,
                         char words[][MAX_WORD_LEN], int n) {
    printf("\n" CYAN "  [%s]" RESET "\n", name);
    char (*arr)[MAX_WORD_LEN] = malloc(n * MAX_WORD_LEN);
    if (!arr) { printf(RED "  Alokasi memori gagal!\n" RESET); return; }
    copy_str_arr(arr, words, n);
    shuffle_str(arr, n);
    preview_str("  Sebelum Sort", arr, n, PREVIEW_COUNT);

    clock_t start = clock();
    quick_sort_str(arr, 0, n - 1);
    clock_t end = clock();

    preview_str("  Sesudah Sort ", arr, n, PREVIEW_COUNT);
    printf(GREEN "  Waktu Eksekusi : %.4f ms\n" RESET, elapsed_ms(start, end));
    free(arr);
}

void run_advance_sort_sh(const char *name,
                         char words[][MAX_WORD_LEN], int n) {
    printf("\n" CYAN "  [%s]" RESET "\n", name);
    char (*arr)[MAX_WORD_LEN] = malloc(n * MAX_WORD_LEN);
    if (!arr) { printf(RED "  Alokasi memori gagal!\n" RESET); return; }
    copy_str_arr(arr, words, n);
    shuffle_str(arr, n);
    preview_str("  Sebelum Sort", arr, n, PREVIEW_COUNT);

    clock_t start = clock();
    shell_sort_str(arr, n);
    clock_t end = clock();

    preview_str("  Sesudah Sort ", arr, n, PREVIEW_COUNT);
    printf(GREEN "  Waktu Eksekusi : %.4f ms\n" RESET, elapsed_ms(start, end));
    free(arr);
}

/* ============================================================
 *  SUBMENU SORTING DASAR
 * ============================================================ */
void menu_sorting_dasar(int *int_data, int n) {
    int choice;
    do {
        printf("\n");
        print_line('=', 40);
        printf(BOLD "       === SORTING DASAR ===\n" RESET);
        print_line('=', 40);
        printf("  1. Bubble Sort\n");
        printf("  2. Insertion Sort\n");
        printf("  3. Selection Sort\n");
        printf("  4. Jalankan Semua (Benchmark)\n");
        printf("  5. Kembali\n");
        print_line('-', 40);
        printf("  Pilih metode : ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }

        switch (choice) {
            case 1:
                run_basic_sort("Bubble Sort", bubble_sort, int_data, n);
                break;
            case 2:
                run_basic_sort("Insertion Sort", insertion_sort, int_data, n);
                break;
            case 3:
                run_basic_sort("Selection Sort", selection_sort, int_data, n);
                break;
            case 4:
                printf("\n" MAGENTA "  === Benchmark Sorting Dasar (%d data) ===" RESET "\n", n);
                run_basic_sort("Bubble Sort",    bubble_sort,    int_data, n);
                run_basic_sort("Insertion Sort", insertion_sort, int_data, n);
                run_basic_sort("Selection Sort", selection_sort, int_data, n);
                break;
            case 5:
                printf("  Kembali ke menu utama...\n");
                break;
            default:
                printf(RED "  Pilihan tidak valid!\n" RESET);
        }
    } while (choice != 5);
}

/* ============================================================
 *  SUBMENU ADVANCE SORTING
 * ============================================================ */
void menu_advance_sorting(char words[][MAX_WORD_LEN], int word_count) {
    if (word_count <= 0) {
        printf(RED "\n  Data kata tidak tersedia. Pastikan file words_en.txt ada.\n" RESET);
        return;
    }

    int choice;
    do {
        printf("\n");
        print_line('=', 40);
        printf(BOLD "       === ADVANCE SORTING ===\n" RESET);
        printf("       Dataset : %d kata\n", word_count);
        print_line('=', 40);
        printf("  1. Merge Sort\n");
        printf("  2. Quick Sort\n");
        printf("  3. Shell Sort\n");
        printf("  4. Jalankan Semua (Benchmark)\n");
        printf("  5. Kembali\n");
        print_line('-', 40);
        printf("  Pilih metode : ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }

        switch (choice) {
            case 1:
                run_advance_sort_mg("Merge Sort", words, word_count);
                break;
            case 2:
                run_advance_sort_qs("Quick Sort", words, word_count);
                break;
            case 3:
                run_advance_sort_sh("Shell Sort", words, word_count);
                break;
            case 4:
                printf("\n" MAGENTA "  === Benchmark Advance Sorting (%d kata) ===" RESET "\n", word_count);
                run_advance_sort_mg("Merge Sort", words, word_count);
                run_advance_sort_qs("Quick Sort", words, word_count);
                run_advance_sort_sh("Shell Sort", words, word_count);
                break;
            case 5:
                printf("  Kembali ke menu utama...\n");
                break;
            default:
                printf(RED "  Pilihan tidak valid!\n" RESET);
        }
    } while (choice != 5);
}

/* ============================================================
 *  MAIN
 * ============================================================ */
int main(void) {
    srand((unsigned)time(NULL));

    /* --- Persiapan data integer --- */
    int int_data[INT_DATA_SIZE];
    generate_random_int(int_data, INT_DATA_SIZE);

    /* --- Persiapan data string --- */
    printf("\n" CYAN "  Memuat dataset kata dari '%s'..." RESET "\n", WORDS_FILE);
    char (*words)[MAX_WORD_LEN] = malloc((long)MAX_WORDS * MAX_WORD_LEN);
    int word_count = 0;
    if (words) {
        word_count = load_words(words, MAX_WORDS);
        if (word_count > 0)
            printf(GREEN "  Berhasil memuat %d kata.\n" RESET, word_count);
    } else {
        printf(RED "  Gagal mengalokasikan memori untuk dataset kata.\n" RESET);
    }

    /* --- Menu utama --- */
    int choice;
    do {
        printf("\n");
        print_line('=', 40);
        printf(BOLD WHITE "        === MENU UTAMA ===\n" RESET);
        print_line('=', 40);
        printf("  1. Sorting Dasar  (Integer, %d data)\n", INT_DATA_SIZE);
        printf("  2. Advance Sorting (String, %d kata)\n", word_count);
        printf("  3. Keluar\n");
        print_line('-', 40);
        printf("  Pilih menu : ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }

        switch (choice) {
            case 1:
                menu_sorting_dasar(int_data, INT_DATA_SIZE);
                break;
            case 2:
                menu_advance_sorting(words, word_count);
                break;
            case 3:
                printf("\n" GREEN "  Terima kasih! Program selesai.\n\n" RESET);
                break;
            default:
                printf(RED "  Pilihan tidak valid! Masukkan 1-3.\n" RESET);
        }
    } while (choice != 3);

    free(words);
    return 0;
}
