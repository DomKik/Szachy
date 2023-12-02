#include <stdio.h>
#include <stdlib.h>
#define  W_SZACHOWNICY 8
#define KROL 1073741824
#define HETMAN  900
#define SKOCZEK  300
#define GONIEC  400
#define PION  100
#define WIEZA  500
#define PUSTE  0

//const int HETMAN = 900, SKOCZEK = 300, GONIEC = 400, PION = 100, WIEZA = 500, PUSTE = 0;
const int CZLOWIEK = -1, KOMPUTER = 1, MAX_GLEBIA = 4;

int szachownica[W_SZACHOWNICY][W_SZACHOWNICY];

int ruch_kompa_wrsz, ruch_kompa_kol, ruszana_bierka_kompa_wrsz, ruszana_bierka_kompa_kol;

int heurystyki[7][8][8] = {
    // Krol
    {
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
        {KROL, KROL, KROL, KROL, KROL, KROL, KROL, KROL},
    },
    // Hetman
    {
        {HETMAN, HETMAN, HETMAN, HETMAN, HETMAN, HETMAN, HETMAN ,HETMAN},
        {HETMAN, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5 ,HETMAN},
        {HETMAN, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5 ,HETMAN},
        {HETMAN, HETMAN + 5, HETMAN + 10, HETMAN + 10, HETMAN + 10, HETMAN + 10, HETMAN + 5 ,HETMAN},
        {HETMAN, HETMAN + 5, HETMAN + 10, HETMAN, HETMAN + 10, HETMAN + 10, HETMAN + 5 ,HETMAN},
        {HETMAN, HETMAN + 5, HETMAN + 10, HETMAN, HETMAN + 10, HETMAN + 10, HETMAN + 5 ,HETMAN},
        {HETMAN, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5, HETMAN + 5 ,HETMAN},
        {HETMAN, HETMAN, HETMAN, HETMAN, HETMAN, HETMAN, HETMAN ,HETMAN}

    },
    // Wie¿a
    {
        {WIEZA, WIEZA, WIEZA + 5, WIEZA + 10, WIEZA + 10, WIEZA + 5, WIEZA ,WIEZA},
        {WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA},
        {WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA},
        {WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA},
        {WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA},
        {WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA},
        {WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA, WIEZA},
        {WIEZA, WIEZA, WIEZA + 5, WIEZA + 10, WIEZA + 10, WIEZA + 5, WIEZA ,WIEZA}

    },
    // Goniec
    {
        {GONIEC, GONIEC, GONIEC, GONIEC, GONIEC, GONIEC, GONIEC, GONIEC},
        {GONIEC, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC},
        {GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5},
        {GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5},
        {GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5},
        {GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5},
        {GONIEC, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC + 5, GONIEC},
        {GONIEC, GONIEC, GONIEC, GONIEC, GONIEC, GONIEC, GONIEC, GONIEC},
    },
    // Skoczek
    {
        {SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK},
        {SKOCZEK, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK},
        {SKOCZEK, SKOCZEK + 5, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 5, SKOCZEK},
        {SKOCZEK, SKOCZEK + 5, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 5, SKOCZEK},
        {SKOCZEK, SKOCZEK + 5, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 5, SKOCZEK},
        {SKOCZEK, SKOCZEK + 5, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 8, SKOCZEK + 5, SKOCZEK},
        {SKOCZEK, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK + 5, SKOCZEK},
        {SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK, SKOCZEK},
    },
    // Pionek
    {
        {PION, PION, PION, PION, PION, PION, PION, PION},
        {PION, PION, PION, PION, PION, PION, PION, PION},
        {PION + 1, PION + 1, PION + 1, PION + 1, PION + 1, PION + 1, PION + 1, PION + 1},
        {PION + 2, PION + 2, PION + 2, PION + 2, PION + 2, PION + 2, PION + 2, PION + 2},
        {PION + 3, PION + 3, PION + 3, PION + 3, PION + 3, PION + 3, PION + 3, PION + 3},
        {PION + 4, PION + 4, PION + 4, PION + 4, PION + 4, PION + 4, PION + 4, PION + 4},
        {PION + 5, PION + 5, PION + 5, PION + 5, PION + 5, PION + 5, PION + 5, PION + 5},
        {PION, PION, PION, PION, PION, PION, PION, PION},
    },
    //puste
    {
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
        {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
    }
};

int sprawdz_mozliwosci(int, int);

int id_figury(int pole)
{
         pole = abs(pole);
         switch(pole)
         {
         case KROL:
                  return 0;
                  break;
         case HETMAN:
                  return 1;
                  break;
         case WIEZA:
                  return 2;
                  break;
         case GONIEC:
                  return 3;
                  break;
         case SKOCZEK:
                  return 4;
                  break;
         case PION:
                  return 5;
                  break;
         case PUSTE:
                  return 6;
                  break;
         }
}

int abs(int a)
{
         if(a < 0) return -a;
         return a;
}

char ktora_bierka(int war_pola)
{
         int przeciwnik = 0;
         if(war_pola < 0) { przeciwnik = 32; }
         war_pola = abs(war_pola);

         if(war_pola == KROL) { return 'K' + przeciwnik; }
         else if(war_pola == HETMAN) { return 'H' + przeciwnik; }
         else if(war_pola == WIEZA) { return 'W' + przeciwnik; }
         else if(war_pola == GONIEC) { return 'G' + przeciwnik; }
         else if(war_pola == SKOCZEK) { return 'S' + przeciwnik; }
         else if(war_pola == PION) { return 'P' + przeciwnik; }
         else { return ' '; }
}

void wypisz()
{
         int nr_wiersza = 1;
         printf("    a   b   c   d   e   f   g   h  \n");
         printf("  ---------------------------------\n");
         for(int i=0; i<W_SZACHOWNICY; i++)
         {
                  printf("%d ", nr_wiersza);
                  for(int j=0; j<W_SZACHOWNICY; j++)
                  {
                           printf("| %c ", ktora_bierka(szachownica[i][j]));
                  }
                  printf("|\n  ---------------------------------\n");
                  ++nr_wiersza;
         }
         printf("\n");
}

void reset()
{
         szachownica[0][0] = WIEZA; szachownica[0][7] = WIEZA;
         szachownica[7][0] = -WIEZA; szachownica[7][7] = -WIEZA;
         szachownica[0][1] = SKOCZEK; szachownica[0][6] = SKOCZEK;
         szachownica[7][1] = -SKOCZEK; szachownica[7][6] = -SKOCZEK;
         szachownica[0][2] = GONIEC; szachownica[0][5] = GONIEC;
         szachownica[7][2] = -GONIEC; szachownica[7][5] = -GONIEC;
         szachownica[0][3] = HETMAN; szachownica[0][4] = KROL;
         szachownica[7][3] = -HETMAN; szachownica[7][4] = -KROL;
         for(int i=0; i<W_SZACHOWNICY; i++)
         {
                  szachownica[1][i] = PION;
                  szachownica[2][i] = PUSTE;
                  szachownica[3][i] = PUSTE;
                  szachownica[4][i] = PUSTE;
                  szachownica[5][i] = PUSTE;
                  szachownica[6][i] = -PION;
         }
}

int ocen_sytuacje_na_szachownicy()
{
         int ocena = 0;
         for(int i=0; i<W_SZACHOWNICY; i++)
         {
                  for(int j=0; j<W_SZACHOWNICY; j++)
                  {
                           if(szachownica[i][j] < 0)
                           {
                                    ocena -= heurystyki[id_figury(szachownica[i][j])][i][j];
                           }
                           else
                           {
                                    ocena += heurystyki[id_figury(szachownica[i][j])][i][j];
                           }
                  }
         }
         return ocena;
}

void wykonaj_ruch(int pole_s_wrsz, int pole_s_kol, int pole_n_wrsz, int pole_n_kol)
{
         szachownica[pole_n_wrsz][pole_n_kol] = szachownica[pole_s_wrsz][pole_s_kol];
         szachownica[pole_s_wrsz][pole_s_kol] = PUSTE;
}

int sprawdz_mozliwosci_dla_ruchu(int gracz, int pole_s_wrsz, int pole_s_kol, int pole_n_wrsz, int pole_n_kol, int glebia, int aktualna_ocena)
{
         int poprzednia_war_starego_pola = szachownica[pole_s_wrsz][pole_s_kol];
         int poprzednia_war_nowego_pola = szachownica[pole_n_wrsz][pole_n_kol];

         szachownica[pole_n_wrsz][pole_n_kol] = szachownica[pole_s_wrsz][pole_s_kol];
         szachownica[pole_s_wrsz][pole_s_kol] = PUSTE;

         int ocena;
         if(gracz == CZLOWIEK)
         {
                  ocena = sprawdz_mozliwosci(KOMPUTER, glebia + 1);
         }
         else if(gracz == KOMPUTER)
         {
                  ocena = sprawdz_mozliwosci(CZLOWIEK, glebia + 1);
         }

         szachownica[pole_s_wrsz][pole_s_kol] = poprzednia_war_starego_pola;
         szachownica[pole_n_wrsz][pole_n_kol] = poprzednia_war_nowego_pola;
         if(gracz == KOMPUTER && ocena >= aktualna_ocena)
         {
                  aktualna_ocena = ocena;
                  if(glebia == 0)
                  {
                           ruch_kompa_wrsz = pole_n_wrsz;
                           ruch_kompa_kol = pole_n_kol;

                           ruszana_bierka_kompa_kol = pole_s_kol;
                           ruszana_bierka_kompa_wrsz = pole_s_wrsz;
                  }
         }
         else if(gracz == CZLOWIEK && ocena < aktualna_ocena)
         {
                  aktualna_ocena = ocena;
         }

         return aktualna_ocena;
}

int czy_ruch_mozliwy(int gracz, int wrsz, int kol)
{
         if(wrsz < 0 || wrsz > W_SZACHOWNICY - 1 || kol < 0 || kol > W_SZACHOWNICY - 1) { return 0; }
         if(gracz * szachownica[wrsz][kol] > 0) { return 0; } // gdy gracz i figura na docelowym polu sa tych samych znakow
         return 1;
}

int analizuj_ruch_wieza(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         int nowy_wrsz = wrsz + 1, nowa_kol = kol, czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  ++nowy_wrsz;
         }

         nowy_wrsz = wrsz - 1;
         czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  --nowy_wrsz;
         }

         nowy_wrsz = wrsz;
         nowa_kol = kol + 1;
         czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  ++nowa_kol;
         }

         nowa_kol = kol - 1;
         czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  --nowa_kol;
         }
         return aktualna_ocena;
}

int analizuj_ruch_goniec(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         int nowy_wrsz = wrsz + 1, nowa_kol = kol + 1, czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  ++nowy_wrsz;
                  ++nowa_kol;
         }

         nowy_wrsz = wrsz - 1;
         nowa_kol = kol - 1;
         czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  --nowy_wrsz;
                  --nowa_kol;
         }

         nowy_wrsz = wrsz - 1;
         nowa_kol = kol + 1;
         czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  ++nowa_kol;
                  --nowy_wrsz;
         }

         nowa_kol = kol - 1;
         nowy_wrsz = wrsz + 1;
         czy_napotkana_figura = 0;

         while(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol) == 1 && czy_napotkana_figura == 0)
         {
                  if(szachownica[nowy_wrsz][nowa_kol] != 0) { czy_napotkana_figura = 1; }
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  --nowa_kol;
                  ++nowy_wrsz;
         }
         return aktualna_ocena;
}

int analizuj_ruch_hetman(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         aktualna_ocena = analizuj_ruch_goniec(gracz, wrsz, kol, glebia, aktualna_ocena);
         aktualna_ocena = analizuj_ruch_wieza(gracz, wrsz, kol, glebia, aktualna_ocena);
         return aktualna_ocena;
}

int analizuj_ruch_pion(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         //gracz = -gracz;
         int nowy_wrsz, nowa_kol;
         nowy_wrsz = wrsz + gracz; nowa_kol = kol;
         short int czy_nie_wyszlo_poza;
         czy_nie_wyszlo_poza = (nowy_wrsz < W_SZACHOWNICY ) && (nowy_wrsz > -1);
         if(czy_nie_wyszlo_poza && szachownica[nowy_wrsz][nowa_kol] == PUSTE)
         {
                  //szachownica[nowy_wrsz][nowa_kol] = WIEZA;
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
         }
         nowa_kol = kol - 1;
         if(czy_nie_wyszlo_poza && nowa_kol > -1 && szachownica[nowy_wrsz][nowa_kol] * gracz < PUSTE)
         {
                  //szachownica[nowy_wrsz][nowa_kol] = KROL;
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
         }
         nowa_kol = kol + 1;
         if(czy_nie_wyszlo_poza && nowa_kol < W_SZACHOWNICY && szachownica[nowy_wrsz][nowa_kol] * gracz < PUSTE)
         {
                  //szachownica[nowy_wrsz][nowa_kol] = SKOCZEK;
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
         }
         nowy_wrsz = wrsz + 2 * gracz; nowa_kol = kol;
         if(szachownica[nowy_wrsz][nowa_kol] == PUSTE && (wrsz == 1 || wrsz == 6))
         {
                  //szachownica[nowy_wrsz][nowa_kol] = -SKOCZEK;
                  aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
         }
         return aktualna_ocena;
}

int analizuj_ruch_krol(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         for(int nowy_wrsz=wrsz-1; nowy_wrsz<wrsz+2; nowy_wrsz++)
         {
                  for(int nowa_kol=kol-1; nowa_kol<kol+2; nowa_kol++)
                  {
                           if(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol))
                           {
                                    //szachownica[nowy_wrsz][nowa_kol] = KROL;
                                    aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                           }
                  }
         }
         return aktualna_ocena;
}

int analizuj_ruch_skoczek(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         int nowy_wrsz = wrsz, nowa_kol = kol;
         for(int i=-2; i<3; i+=4)
         {
                  nowy_wrsz = wrsz + i;
                  nowa_kol = kol - 1;
                  if(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol))
                  {
                           //szachownica[nowy_wrsz][nowa_kol] = SKOCZEK;
                           aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  }
                  nowa_kol = kol + 1;
                  if(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol))
                  {
                           //szachownica[nowy_wrsz][nowa_kol] = SKOCZEK;
                           aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  }
         }
         nowy_wrsz = wrsz; nowa_kol = kol;
         for(int i=-2; i<3; i+=4)
         {
                  nowy_wrsz = wrsz - 1;
                  nowa_kol = kol + i;
                  if(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol))
                  {
                           //szachownica[nowy_wrsz][nowa_kol] = SKOCZEK;
                           aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  }
                  nowy_wrsz = wrsz + 1;
                  if(czy_ruch_mozliwy(gracz, nowy_wrsz, nowa_kol))
                  {
                           //szachownica[nowy_wrsz][nowa_kol] = SKOCZEK;
                           aktualna_ocena = sprawdz_mozliwosci_dla_ruchu(gracz, wrsz, kol, nowy_wrsz, nowa_kol, glebia, aktualna_ocena);
                  }
         }
         return aktualna_ocena;
}

int analizuj_ruch(int gracz, int wrsz, int kol, int glebia, int aktualna_ocena)
{
         int aktualne_pole = abs(szachownica[wrsz][kol]);
         if(aktualne_pole == PION)
         {
                  aktualna_ocena = analizuj_ruch_pion(gracz, wrsz, kol, glebia, aktualna_ocena);
         }
         else if(aktualne_pole == SKOCZEK)
         {
                  aktualna_ocena = analizuj_ruch_skoczek(gracz, wrsz, kol, glebia, aktualna_ocena);
         }
         else if(aktualne_pole == GONIEC)
         {
                  aktualna_ocena = analizuj_ruch_goniec(gracz, wrsz, kol, glebia, aktualna_ocena);
         }
         else if(aktualne_pole == WIEZA)
         {
                  aktualna_ocena = analizuj_ruch_wieza(gracz, wrsz, kol, glebia, aktualna_ocena);
         }
         else if(aktualne_pole == HETMAN)
         {
                  aktualna_ocena = analizuj_ruch_hetman(gracz, wrsz, kol, glebia, aktualna_ocena);
         }
         else if(aktualne_pole == KROL)
         {
                  aktualna_ocena = analizuj_ruch_krol(gracz, wrsz, kol, glebia, aktualna_ocena);
         }
         return aktualna_ocena;
}

int sprawdz_mozliwosci(int gracz, int glebia)
{
         int aktualna_ocena_na_szachownicy = ocen_sytuacje_na_szachownicy();
         if(aktualna_ocena_na_szachownicy > (KROL >> 1))
         {
                  return aktualna_ocena_na_szachownicy - glebia * 1000;
         }
         else if(aktualna_ocena_na_szachownicy < -(KROL >> 1))
         {
                  return aktualna_ocena_na_szachownicy + glebia * 1000;
         }
         else if(glebia == MAX_GLEBIA) { return aktualna_ocena_na_szachownicy; }

         int najlepsza_ocena;

         if(gracz ==  KOMPUTER) { najlepsza_ocena = -KROL - MAX_GLEBIA * 1000 - 1; }
         else if(gracz == CZLOWIEK) { najlepsza_ocena = KROL + MAX_GLEBIA * 1000 + 1; }

         for(int wrsz=0; wrsz<W_SZACHOWNICY; wrsz++)
         {
                  for(int kol=0; kol<W_SZACHOWNICY; kol++)
                  {
                           if(szachownica[wrsz][kol] * gracz > 0)
                           {
                                    najlepsza_ocena = analizuj_ruch(gracz, wrsz, kol, glebia, najlepsza_ocena);
                                    /*if(gracz == KOMPUTER && najlepsza_ocena < aktualna_ocena_na_szachownicy ||
                                       gracz == CZLOWIEK && najlepsza_ocena > aktualna_ocena_na_szachownicy)
                                    {
                                             break;
                                    }*/
                           }
                  }
         }
         return najlepsza_ocena;
}

int czy_pole_istnieje(int wrsz, int kol)
{
         if(wrsz < 0 || wrsz > W_SZACHOWNICY - 1 || kol < 0 || kol > W_SZACHOWNICY - 1)
         {
                  return 0;
         }
         return 1;
}

int main()
{
         reset();
         wypisz();
         printf("ocena: %d\n", ocen_sytuacje_na_szachownicy());
         int nr_starego_wiersza, nr_nowego_wiersza;
         short int wygrany = CZLOWIEK;
         char  nr_starej_kolumny, nr_nowej_kolumny;
         while(abs(ocen_sytuacje_na_szachownicy()) < (KROL >> 2))
         {
                  nr_starego_wiersza = -1; nr_nowego_wiersza = -1; nr_starej_kolumny = -1; nr_nowej_kolumny = -1;
                  while(czy_ruch_mozliwy(CZLOWIEK, nr_nowego_wiersza, nr_nowej_kolumny) == 0 ||
                        czy_pole_istnieje(nr_starego_wiersza, nr_starej_kolumny) == 0)
                  {
                           printf("Wpisz nr wiersza i nr kolumny ruszanej figury a nastepnie nr wiersz i nr kolumny docelowego pola\n");
                           scanf("%d %c %d %c", &nr_starego_wiersza, &nr_starej_kolumny, &nr_nowego_wiersza, &nr_nowej_kolumny);
                           --nr_starego_wiersza; nr_starej_kolumny -= 'a';
                           --nr_nowego_wiersza; nr_nowej_kolumny -= 'a';
                  }
                  wykonaj_ruch(nr_starego_wiersza, (int)nr_starej_kolumny, nr_nowego_wiersza, (int)nr_nowej_kolumny);

                  sprawdz_mozliwosci(KOMPUTER, 0);
                  if(szachownica[ruch_kompa_wrsz][ruch_kompa_kol] == -KROL)
                  {
                           wygrany = KOMPUTER;
                           break;
                  }
                  wykonaj_ruch(ruszana_bierka_kompa_wrsz, ruszana_bierka_kompa_kol, ruch_kompa_wrsz, ruch_kompa_kol);
                  wypisz();
                  printf("ocena: %d\n", ocen_sytuacje_na_szachownicy());
         }
         if(wygrany == KOMPUTER)
         {
                  printf("PRZEGRALES!\n");
         }
         else if(wygrany == CZLOWIEK)
         {
                  printf("WYGRALES!\n");
         }
         return 0;
}
