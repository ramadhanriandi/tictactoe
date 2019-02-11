/*	NIM				: 13517080
	Nama			: Mgs. M. Riandi Ramadhan
	Deskripsi		: Permainan Tic Tac Toe */
	
#include <stdio.h>
#include "boolean.h"

#define NSym 2 								// Banyak simbol dalam file
#define NBrsAkhirC 77						// Banyak baris state akhir computer 1st dalam file
#define NKolAkhirC 2						// Banyak kolom state akhir computer 1st dalam file
#define NBrsAkhirP 65						// Banyak baris state akhir player 1st dalam file
#define NKolAkhirP 2						// Banyak kolom state akhir player 1st dalam file
#define NBrsTFC 77							// Banyak baris transition function computer 1st dalam file
#define NKolTFC 8							// Banyak kolom transition function computer 1st dalam file
#define NBrsTFP 65							// Banyak baris transition function player 1st dalam file
#define NKolTFP 8							// Banyak kolom transition function player 1st dalam file
#define NStateC 202							// Banyak daftar state computer 1st dalam file
#define NStateP 199							// Banyak daftar state player 1st dalam file

/* KAMUS UNIVERSAL */
char IsiPapan[10] = { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};
char Step[10] = {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};

/* PROGRAM UTAMA */
int main () {
	/* KAMUS */
	FILE *Simbol;							// Nama pengganti file eksternal transition function computer 1st
	FILE *AwalComputer;						// Nama pengganti file eksternal state awal computer 1st
	FILE *AkhirComputer;					// Nama pengganti file eksternal state akhir computer 1st
	FILE *TFComputer;						// Nama pengganti file eksternal transition function computer 1st
	FILE *AwalPlayer;						// Nama pengganti file eksternal state awal player 1st
	FILE *AkhirPlayer;						// Nama pengganti file eksternal state akhir player 1st
	FILE *TFPlayer;							// Nama pengganti file eksternal transition function player 1st
	FILE *StateComputer;					// Nama pengganti file eksternal state computer 1st
	FILE *StatePlayer;						// Nama pengganti file eksternal state player 1st
	char AwalC[10];							// Menyimpan state awal computer 1st
	char AkhirC[100][100][10];				// Menyimpan state akhir computer 1st
	char AwalP[10];							// Menyimpan state awal player 1st
	char AkhirP[100][100][10];				// Menyimpan state akhir player 1st
	char Sym[100];							// Menyimpan daftar simbol 
	char TFC[100][100][10];					// Menyimpan transition function computer 1st
	char TFP[100][100][10];					// Menyimpan transition function player 1st
	char StateC[250][1][10];				// Menyimpan daftar state computer 1st
	char StateP[250][1][10];				// Menyimpan daftar state player 1st
	char ExState[100][10];					// Menyimpan daftar state yang dilalui
	char Step[10];							// Menyimpan step yang dilalui permainan
	int Baris = 1;
	int Kolom = 1;
	int i, j;	
	boolean Found;							// Mengembalikan true jika mendapatkan state
	int Indeks, Count, Pilihan, Idx;		// Menyatakan indeks, count, pilihan angka
	char First;								// Input urutan pertama
	int Turn = 1;							// Menyatakan urutan ke-n
	boolean Same, Valid;    				// Mengembalikan true jika sama atau valid atau final state
	boolean Final = false;					// Mengembalikan true jika sudah final state
	
	/* FUNGSI DAN PROSEDUR */
	void Papan();							// Prosedur menggambar papan tic tac toe	
	
	/* ALGORITMA */
	/* Input simbol dari file ke dalam array */	
	Simbol = fopen("Simbol.txt", "r");
    for(Kolom = 1; Kolom <= NSym+1; Kolom++) {
       	fscanf(Simbol, "%c", &Sym[Kolom]);
   	}
    
    /* Input state awal computer 1st dari file ke dalam variabel */	
	AwalComputer = fopen("AwalComputer.txt", "r");
    fscanf(AwalComputer, "%9s", &AwalC);
    
    /* Input state akhir computer 1st dari file ke dalam matriks */	
	AkhirComputer = fopen("AkhirComputer.txt", "r");
	for(Baris = 1; Baris <= NBrsAkhirC; Baris++) {
        for(Kolom = 1; Kolom <= NKolAkhirC; Kolom++) {
        	fscanf(AkhirComputer, "%9s", &AkhirC[Baris][Kolom]);
   	 	}
    }
    
	/* Input transition function computer 1st dari file ke dalam matriks */	
	TFComputer = fopen("TFComputer.txt", "r");
	for(Baris = 1; Baris <= NBrsTFC; Baris++) {
        for(Kolom = 1; Kolom <= NKolTFC; Kolom++) {
        	fscanf(TFComputer, "%9s", &TFC[Baris][Kolom]);
   	 	}
    }
    
    /* Input state awal player 1st dari file ke dalam variabel */	
	AwalPlayer = fopen("AwalPlayer.txt", "r");
    fscanf(AwalPlayer, "%9s", &AwalP);
    
    /* Input state akhir player 1st dari file ke dalam matriks */	
	AkhirPlayer = fopen("AkhirPlayer.txt", "r");
	for(Baris = 1; Baris <= NBrsAkhirP; Baris++) {
        for(Kolom = 1; Kolom <= NKolAkhirP; Kolom++) {
        	fscanf(AkhirPlayer, "%9s", &AkhirP[Baris][Kolom]);
   	 	}
    }
    
	/* Input transition function player 1st dari file ke dalam matriks */	
	TFPlayer = fopen("TFPlayer.txt", "r");
	for(Baris = 1; Baris <= NBrsTFP; Baris++) {
        for(Kolom = 1; Kolom <= NKolTFP; Kolom++) {
        	fscanf(TFPlayer, "%9s", &TFP[Baris][Kolom]);
   	 	}
    }
	
	/* Input daftar state computer 1st dari file ke dalam matriks */	
	StateComputer = fopen("StateComputer.txt", "r");
	for(Baris = 1; Baris <= NStateC; Baris++) {
        fscanf(StateComputer, "%9s", &StateC[Baris][1]);
    }
    
    /* Input daftar state player 1st dari file ke dalam matriks */	
	StatePlayer = fopen("StatePlayer.txt", "r");
	for(Baris = 1; Baris <= NStateP; Baris++) {
        fscanf(StatePlayer, "%9s", &StateP[Baris][1]);
    }
	
	/* Tampilan Awal Program */;                                                                                 
 	printf("_|_|_|_|_|  _|               _|_|_|_|_|                       _|_|_|_|_|\n");     
	printf("    _|            _|_|_|         _|      _|_|_|    _|_|_|         _|      _|_|      _|_|\n");                    
    printf("    _|      _|  _|               _|    _|    _|  _|               _|    _|    _|  _|_|_|_|\n");  
	printf("    _|      _|  _|               _|    _|    _|  _|               _|    _|    _|  _| \n");  
	printf("    _|      _|    _|_|_|         _|      _|_|_|    _|_|_|         _|      _|_|      _|_|_|\n");  
	printf("\n");
	printf("\n");
	printf("Who Goes First : Computer or Player ? (C/P)\n");
	scanf("%c", &First);								// Input urutan pertama
	
	/* Jika Computer Pertama */
	if (First == 'C') {
		while (!Final) {								// Loop hingga final state
			if (Turn == 1) {							// Turn pertama
				Pilihan = AwalC[0] - '0';				// Mengambil input awal dari array state awal computer 1st
				IsiPapan[Pilihan] = Sym[3];				// Mengubah isi papan
				Step[Turn] = AwalC[0];					
				printf("Computer turn, pick a number : %d\n", Pilihan);
				Baris = 1;
				Kolom = 0;
				Indeks = 0;
			}
			else { 
				if (Turn % 2 == 0) {							// Turn genap
					Valid = false;
					do {										// Validasi input angka
						printf("Player turn, pick a number : ");
						scanf("%d", &Pilihan);					// Input angka player
						if (IsiPapan[Pilihan] == '#') {
							IsiPapan[Pilihan] = Sym[1];			// Mengubah isi papan
							Valid = true;
						}
						else {									// Input angka salah
							printf("Wrong input, try again\n");
						}
					} while (!Valid);
					Step[Turn] = Pilihan + '0';
					Same = false;
					Kolom++;
					Indeks++;    
					while (!Same) {								// Mencari next state
						if (Step[Indeks+1] != TFC[Baris][Kolom][Indeks]) {
							Baris++;	
						}
						else {
							Same = true;
						}
					}
				}
				else if (Turn % 2 == 1) {						// Turn ganjil bukan 1
					Kolom++; 
					Indeks++;
					Pilihan = TFC[Baris][Kolom][Indeks] - '0';	// Mengambil input dari transition table
					IsiPapan[Pilihan] = Sym[3];					// Mengubah isi papan
					Step[Turn] = Pilihan + '0';
					printf("Computer turn, pick a number : %d\n", Pilihan);
				}
				Count = 0;
				for (Idx = 0; Idx <= 8; Idx++) {				// Final state checking
					if (TFC[Baris][Kolom][Idx] == AkhirC[Baris][1][Idx]) {
						Count++;
					}
				}
				if (Count == 9) {								// Jika final state
					Final = true;
				} 				
			}
			Papan();
			for (i = 1; i <= 10; i++) {					// Menyimpan daftar state yang dilalui
				ExState[Turn][i] = Step[i];
			}
			Turn++;
		}
	}
	/* Jika Player Pertama */
	else if (First == 'P') {
		Papan();
		while (!Final) {								// Loop hingga final state
			if (Turn == 1) {							// Turn pertama
				Valid = false;
				do {									// Validasi input
					printf("Player turn, pick a number : ");
					scanf("%d", &Pilihan);				// Input angka
					if (Pilihan != AwalP[0]-'0') {
						printf("Wrong input, turn pertama dimulai dari 5\n");
					}
					else {
						Valid = true;
					}
				} while (!Valid);
				IsiPapan[Pilihan] = Sym[1];				// Mengubah isi papan
				Step[Turn] = AwalP[0];
				Baris = 1;
				Kolom = 0;
				Indeks = 0;
			}
			else { 
				if (Turn % 2 == 0) {					// Turn genap
					Kolom++; 
					Indeks++;
					Pilihan = TFP[Baris][Kolom][Indeks] - '0';		// Mengambil input dari transition table
					IsiPapan[Pilihan] = Sym[3];			// Mengubah isi papan
					Step[Turn] = Pilihan + '0';
					printf("Computer turn, pick a number : %d\n", Pilihan);
				}
				else if (Turn % 2 == 1) {				// Turn ganjil bukan 1
					Valid = false;
					do {								// Validasi input angka
						printf("Player turn, pick a number : ");
						scanf("%d", &Pilihan);			// Input angka
						if (IsiPapan[Pilihan] == '#') {
							IsiPapan[Pilihan] = Sym[1];	// Mengubah isi papan
							Valid = true;
						}
						else {
							printf("Wrong input, try again\n");
						}
					} while (!Valid);
					Step[Turn] = Pilihan + '0';
					Same = false;
					Kolom++;
					Indeks++;    
					while (!Same) {						// Mencari next state
						if (Step[Indeks+1] != TFP[Baris][Kolom][Indeks]) {
							Baris++;	
						}
						else {
							Same = true;
						}
					}
				}
				Count = 0;
				for (Idx = 0; Idx <= 8; Idx++) {		// Final state checking
					if (TFP[Baris][Kolom][Idx] == AkhirP[Baris][1][Idx]) {
						Count++;
					}
				}
				if (Count == 9) {						// Jika final state	
					Final = true;
				} 				
			}
			Papan();
			for (i = 1; i <= 10; i++) {					// Menyimpan daftar state yang dilalui
				ExState[Turn][i] = Step[i];
			}
			Turn++;
		}
	}
	
	/* Game Selesai */
	if (First == 'P'|| First == 'C') {
		printf("Passed State : \n");				// Menulis daftar state yang dilalui
		for (i = 1; i <= Turn-1; i++) {
			for (j = 1; j <= 10; j++) {
				printf("%c", ExState[i][j]);
			}
			printf("\n");	
		}
		if (AkhirC[Baris][2][0] == 'w') {			// Computer Win
			printf("Computer WIN\n");
		}
		else {										// Game Draw
			printf("Game DRAW\n");
		}		
	}
	else {											// Input awal salah
		printf("Wrong input\n");
	}
					
	/* Menutup file */
	fclose(Simbol);
	fclose(AwalComputer);
	fclose(AkhirComputer);
	fclose(TFComputer);
	fclose(AwalPlayer);
	fclose(AkhirPlayer);
	fclose(TFPlayer);
	fclose(StateComputer);
	fclose(StatePlayer);
	
	return 0;	
}

/* FUNGSI DAN PROSEDUR */
void Papan()								// Prosedur menggambar papan tic tac toe
{
    printf(" _____ _____ _____ \n");
    printf("|     |     |     |\n");
    printf("|  %c  |  %c  |  %c  |\n", IsiPapan[1], IsiPapan[2], IsiPapan[3]);
    printf("|_____|_____|_____|\n");
    printf("|     |     |     |\n");
    printf("|  %c  |  %c  |  %c  |\n", IsiPapan[4], IsiPapan[5], IsiPapan[6]);
    printf("|_____|_____|_____|\n");
    printf("|     |     |     |\n");
    printf("|  %c  |  %c  |  %c  |\n", IsiPapan[7], IsiPapan[8], IsiPapan[9]);
    printf("|_____|_____|_____|\n\n");
}
