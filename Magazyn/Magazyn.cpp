#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Kontrahent
{
	string imie, nazwisko;
	Kontrahent *nast;
};

struct Towar
{
	int	liczba_sztuk, dzien, miesiac, rok;
	Towar *nast;
	Kontrahent *kupiec;
};

struct Rodzaj
{
	string nazwa;
	int cena;
	Rodzaj *nast;
	Towar *zamowienie;
};

char menu()
{
	char znak;
	cout << "MAGAZYN" << endl
		<< "---------------------" << endl
		<< "Wybierz cyfre:" << endl
		<< "1.Dodaj towar" << endl
		<< "2.Dodaj zamowienie" << endl
		<< "3.Dodaj kontrahentow" << endl
		<< "4.Wyswietl baze danych" << endl
		<< "5.Usun zamowienie" << endl
		<< "6.Usun towar (mozliwe tylko po usunieciu wszystkich zamowien)" << endl
		<< "7.Wyszukaj towar" << endl
		<< "8.Edytuj zamowienie" << endl
		<< "9.Zapisz" << endl
		<< "0.Zakoncz program" << endl
		<< "---------------------" << endl;
	cin >> znak;
	return znak;
}

char menu_wyswietlania()
{
	char znak_sort;
	cout << "Wybierz 1 aby posortowac towary wedlug nazwy" << endl
		<< "Wybierz 0 aby kontynuowac" << endl;
	cin >> znak_sort;
	return znak_sort;
}

char edycja_menu()
{
	char znak;
	cout << "Wybierz cyfre:" << endl
		<< "1.Zmien ilosc" << endl
		<< "2.Zmien date" << endl
		<< "0.Kontynuuj" << endl;
	cin >> znak;
	return znak;
}

void dodaj_rodzaj(Rodzaj*& produkty)
{
	string nazwa1;
	int cena1;
	cout << "Podaj nazwe towaru:" << endl;
	cin >> nazwa1;
	cout << "Podaj cene towaru:" << endl;
	cin >> cena1;
	if (produkty == NULL)
	{
		Rodzaj *nowy = new Rodzaj;
		nowy->nazwa = nazwa1;
		nowy->cena = cena1;
		nowy->nast = NULL;
		nowy->zamowienie = NULL;
		produkty = nowy;
		return;
	}
	Rodzaj *wskaznik = produkty;
		while (wskaznik->nast != NULL)
		{
			if (wskaznik->nazwa == nazwa1)
			{
				cout << "Taki towar juz istnieje" << endl;
				return;
			}
			wskaznik = wskaznik->nast;
		}
		if (wskaznik->nazwa == nazwa1)
		{
			cout << "Taki towar juz istnieje" << endl;
			produkty = wskaznik;
			return;
		}
		Rodzaj *nowy = new Rodzaj;
		nowy->nazwa = nazwa1;
		nowy->cena = cena1;
		nowy->nast = NULL;
		nowy->zamowienie = NULL;
		wskaznik->nast = nowy;
}

void dodaj_kontrahenta(Kontrahent *&lista)
{
	string imie1, nazwisko1;
	cout << "Podaj imie nowego kontrahenta:" << endl;
	cin >> imie1;
	cout << "Podaj nazwisko nowego kontrahenta:" << endl;
	cin >> nazwisko1;
	if (lista == NULL)
	{
		Kontrahent *nowy = new Kontrahent;
		nowy->imie = imie1;
		nowy->nazwisko = nazwisko1;
		nowy->nast = NULL;
		lista = nowy;
		return;
	}
	Kontrahent *wskaznik = lista;
		while (wskaznik->nast != NULL)
		{
			if (wskaznik->imie == imie1 && wskaznik->nazwisko == nazwisko1)
			{
				cout << "Taki kontrahent juz istnieje" << endl;
				return;
			}
			wskaznik = wskaznik->nast;
		}
		if (wskaznik->imie == imie1 && wskaznik->nazwisko == nazwisko1)
		{
			cout << "Taki kontrahent juz istnieje" << endl;
			return;
		}
	Kontrahent *nowy = new Kontrahent;
	nowy->imie = imie1;
	nowy->nazwisko = nazwisko1;
	nowy->nast = NULL;
	wskaznik->nast = nowy;
}

void wyswietl_kontrahentow(Kontrahent *lista)
{
	cout << "Wybierz kontrahenta ktoremu chcesz przydzielic towar:" << endl;
	while (lista != NULL)
	{
		cout << lista->imie << " " << lista->nazwisko << endl;
		lista = lista->nast;
	}
	cout << "---------------------" << endl;
}

void wybierz_kontrahenta(Towar *&lista_towarow,Kontrahent *lista)
{
	Kontrahent*wskaznik = lista;
	string imie1, nazwisko1;
	cout << "Podaj imie:" << endl;
	cin >> imie1;
	cout << "Podaj nazwisko:" << endl;
	cin >> nazwisko1;
	while ( wskaznik != NULL)
	{
		if (wskaznik->imie == imie1 && wskaznik->nazwisko == nazwisko1)
		{
			lista_towarow->kupiec = wskaznik;
			return;
		}
		wskaznik = wskaznik->nast;
	}
	cout << "Nie ma takiego kontrahenta" << endl;
	wybierz_kontrahenta(lista_towarow,lista);
}

void wyswietl_rodzaje(Rodzaj *produkty)
{
	cout << "Wybierz towar z listy:" << endl;
	while (produkty != NULL)
	{
		cout << produkty->nazwa << endl;
		produkty = produkty->nast;
	}
	cout << "---------------------" << endl;
}

void podaj_dane_zamowienia(Rodzaj *&produkty,Kontrahent *lista)
{
	
	int liczba_sztuk1,dzien1,miesiac1,rok1;
	cout << "Podaj liczbe sztuk towaru:" << endl;
	cin >> liczba_sztuk1;
	cout << "Podaj dzien zamowienia towaru:" << endl;
	cin >> dzien1;
	cout << "Podaj miesiac zamowienia towaru:" << endl;
	cin >> miesiac1;
	cout << "Podaj rok zamowienia towaru:" << endl;
	cin >> rok1;
	if (produkty->zamowienie == NULL)
	{
		Towar*nowy = new Towar;
		nowy->liczba_sztuk = liczba_sztuk1;
		nowy->dzien = dzien1;
		nowy->miesiac = miesiac1;
		nowy->rok = rok1;
		nowy->nast = NULL;
		nowy->kupiec = NULL;
		produkty->zamowienie = nowy;
		wyswietl_kontrahentow(lista);
		wybierz_kontrahenta(produkty->zamowienie, lista);
		cout << "Dodano zamowienie" << endl;
		return;
	}
	Towar*lista_towarow = produkty->zamowienie;
	if (lista_towarow->nast != NULL)
	{
		lista_towarow = lista_towarow->nast;
		while (lista_towarow->nast != NULL)
			lista_towarow = lista_towarow->nast;
	}
	Towar*nowy = new Towar;
	nowy->liczba_sztuk = liczba_sztuk1;
	nowy->dzien = dzien1;
	nowy->miesiac = miesiac1;
	nowy->rok = rok1;
	nowy->nast = NULL;
	nowy->kupiec = NULL;
	lista_towarow->nast = nowy;
	wyswietl_kontrahentow(lista);
	wybierz_kontrahenta(lista_towarow->nast,lista);
	
}

void wybierz_rodzaj(Rodzaj *&produkty, Kontrahent *lista)
{
	Rodzaj *wskaznik=produkty;
	string nazwa1;
	cin >> nazwa1;
	while (wskaznik != NULL)
	{
		if (wskaznik->nazwa == nazwa1)
		{
			podaj_dane_zamowienia(wskaznik,lista);
			return;
		}
		wskaznik = wskaznik->nast;
	}
	cout << "Nie ma takiego towaru, ponow probe" << endl;
	wyswietl_rodzaje(produkty);
	wybierz_rodzaj(produkty,lista);
}



void dodaj_zamowienie(Rodzaj*&produkty,Kontrahent*&lista)
{
	if (produkty == NULL || lista == NULL)
	{
		cout << "Musisz dodac przynajmniej jeden towar lub kontrahenta!" << endl;
		return;
	}
	wyswietl_rodzaje(produkty);
	wybierz_rodzaj(produkty,lista);
}

int suma(Towar*lista_towarow)
{
	int liczba=0;
		while (lista_towarow != NULL)
		{
			liczba = liczba + lista_towarow->liczba_sztuk;
			lista_towarow = lista_towarow->nast;
		}
	return liczba;
}

void wyswietl_dane(Rodzaj *produkty)
{
	while (produkty != NULL)
	{
		Towar*lista_towarow = produkty->zamowienie;
		int n=1;
		cout << "Nazwa: " << produkty->nazwa << " Cena: " << produkty->cena << " Laczna ilosc: " << suma(lista_towarow) << endl << endl;
		while (lista_towarow != NULL)
		{
			Kontrahent*kontrahent_kupujacy = lista_towarow->kupiec;
			cout << n << ". " << " Ilosc sztuk: " << lista_towarow->liczba_sztuk
				<< " Wlasciciel: " << kontrahent_kupujacy->imie << " " << kontrahent_kupujacy->nazwisko
				<< " Data zakupu:" << lista_towarow->dzien << "." << lista_towarow->miesiac << "." << lista_towarow->rok << endl;
				n++;
				lista_towarow = lista_towarow->nast;
		}
		cout << endl;
		produkty = produkty->nast;
	}
}

void sortowanie(Rodzaj *&produkty)
{
	Rodzaj*produkty1 = produkty;
	if (produkty != NULL && produkty->nast != NULL)
	{
		if (produkty->nast->nazwa < produkty->nazwa)
		{
			produkty1 = produkty1->nast;
			produkty->nast = produkty->nast->nast;
			produkty1->nast = produkty;
			produkty = produkty1;
		}
	}
	else
		return;
	Rodzaj *produkty2 = produkty;
	while (produkty2->nast->nast != NULL)
	{
		if (produkty2->nast->nast->nazwa < produkty2->nast->nazwa)
		{
			produkty1 = produkty2;
			produkty1 = produkty1->nast;
			produkty2->nast = produkty2->nast->nast;
			produkty1->nast = produkty1->nast->nast;
			produkty2->nast->nast = produkty1;
			sortowanie(produkty);
		}
		else
			produkty2 = produkty2->nast;
	}
}

void wybor(Rodzaj *&produkty)
{
	char znak_sort = menu_wyswietlania();
	while (znak_sort != 0)
	{
		switch (znak_sort)
		{
		case '1':
			sortowanie(produkty);
			wyswietl_dane(produkty);
			znak_sort = menu_wyswietlania();
			break;
		case '0':
			znak_sort = 0;
			break;
		default:
			cout << "Nie ma takiego znaku, podaj inny" << endl;
			znak_sort = menu_wyswietlania();
			break;
		}
	}
}

void wyswietl_zamowienia(Rodzaj *wskaznik,int &n)
{
	cout << "Podaj numer zamowienia:" << endl;
	Towar*lista_towarow = wskaznik->zamowienie;
	while (lista_towarow != NULL)
	{
		n++;
		Kontrahent*kontrahent_kupujacy = lista_towarow->kupiec;
		cout << n << ". " << " Ilosc sztuk: " << lista_towarow->liczba_sztuk
			<< " Wlasciciel: " << kontrahent_kupujacy->imie << " " << kontrahent_kupujacy->nazwisko
			<< " Data zakupu:" << lista_towarow->dzien << "." << lista_towarow->miesiac << "." << lista_towarow->rok << endl;
		lista_towarow = lista_towarow->nast;
	}
	cout << "---------------------" << endl;
}

void usuwanie_zamowienia_pierwszy(Rodzaj *&wskaznik)
{
	Towar*wskaznik1 = wskaznik->zamowienie;
	if (wskaznik->zamowienie->nast == NULL)
	{
		delete wskaznik1;
		wskaznik->zamowienie = NULL;
		cout << "USUNIETO" << endl;
		return;
	}
	wskaznik->zamowienie = wskaznik->zamowienie->nast;
	delete wskaznik1;
}

void usuwanie_zamowienia_srodkowy(Towar *&wskaznik,int nr,int i)
{
	if (i == nr-1)
	{
		Towar*wskaznik1 = wskaznik->nast;
		wskaznik->nast = wskaznik->nast->nast;
		delete wskaznik1;
		cout << "USUNIETO"<<endl;
		return;
	}
	wskaznik = wskaznik->nast;
	i++;
	usuwanie_zamowienia_srodkowy(wskaznik, nr, i);
}

void usuwanie_zamowienia_ostatni(Rodzaj *&wskaznik)
{
	Towar*wskaznik1 = wskaznik->zamowienie;
	while (wskaznik1->nast->nast!=NULL)
		wskaznik1 = wskaznik1->nast;
	delete wskaznik1->nast;
	wskaznik1->nast = NULL;
	cout << "USUNIETO" << endl;
}

void wybor_usuwanego_zamowienia(Rodzaj *&wskaznik,int n)
{
    int nr;
	cin >> nr;
	if (nr == 1)
	{
		usuwanie_zamowienia_pierwszy(wskaznik);
		return;
	}
	else
	{
		if (nr > 1 && nr < n)
		{
			int i = 1;
			Towar*wskaznik2 = wskaznik->zamowienie;
			usuwanie_zamowienia_srodkowy(wskaznik2,nr,i);
			return;
		}
		else
		{
			if (nr == n)
			{
				usuwanie_zamowienia_ostatni(wskaznik);
				return;
			}
			else
				cout << "Nie ma zamowienie o takim numerze" << endl
				<< "Ponow probe:" << endl;
		}
	}
	wybor_usuwanego_zamowienia(wskaznik, n);
}

void usun_zamowienie(Rodzaj *&produkty)
{
	Rodzaj*wskaznik = produkty;
	wyswietl_rodzaje(produkty);
	string nazwa1;
	cin >> nazwa1;
	while (wskaznik != NULL)
	{
		if (wskaznik->nazwa == nazwa1)
		{
			int n = 0;
			wyswietl_zamowienia(wskaznik,n);
			wybor_usuwanego_zamowienia(wskaznik, n);
			return;
		}
		wskaznik = wskaznik->nast;
	}
	cout << "Nie ma takiego towaru, ponow probe" << endl;
	wyswietl_rodzaje(produkty);
	usun_zamowienie(produkty);
}

void wyszukaj_towar(Rodzaj *produkty)
{
	string nazwa1;
	cout << "Wyszukaj towar jaki chcesz nazlezc:" << endl;
	cin >> nazwa1;
	while (produkty != NULL)
	{
		if (produkty->nazwa == nazwa1)
		{
			int n = 0;
			wyswietl_zamowienia(produkty, n);
			cout << "Wybierz 0 aby kontynuowac" << endl;
			char k=1;
			while (k == 0)
				cin >> k;
			return;
		}
		produkty = produkty->nast;
	}
	cout << "Nie ma takiego towaru, ponow probe" << endl;
	wyszukaj_towar(produkty);
}

void usuwanie_towaru_pierwszy(Rodzaj *&produkty)
{
	Rodzaj*wskaznik = produkty;
	if (wskaznik->nast == NULL)
	{
		delete wskaznik;
		produkty = NULL;
		cout << "USUNIETO" << endl;
		return;
	}
	produkty = wskaznik->nast;
	delete wskaznik;
}

void usuwanie_towaru_srodkowy(Rodzaj *&wskaznik,Rodzaj*&produkty)
{
	Rodzaj*wskaznik1 = produkty;
	while (wskaznik1->nast != wskaznik)
		wskaznik1 = wskaznik1->nast;
	Rodzaj*wskaznik2 = wskaznik;
	wskaznik1->nast = wskaznik1->nast->nast;
	delete wskaznik;
	cout << "USUNIETO" << endl;
	return;
}

void usuwanie_towaru_ostatni(Rodzaj *&produkty)
{
	Rodzaj*wskaznik = produkty;
	while (wskaznik->nast->nast != NULL)
		wskaznik = wskaznik->nast;
	Rodzaj*wskaznik1 = wskaznik->nast;
	delete wskaznik1;
	wskaznik->nast = NULL;
	cout << "USUNIETO" << endl;
}

void wybor_usuwanego_towaru(Rodzaj *&wskaznik, Rodzaj *&produkty)
{
	if (wskaznik == produkty)
	{
		usuwanie_towaru_pierwszy(produkty);
		return;
	}
	else
	{
		if (wskaznik->nast!=NULL)
		{
			usuwanie_towaru_srodkowy(wskaznik,produkty);
			return;
		}
		else
		{
			if (wskaznik->nast == NULL)
			{
				usuwanie_towaru_ostatni(produkty);
				return;
			}
			else
				cout << "Nie ma zamowienie o takim numerze" << endl
				<< "Ponow probe:" << endl;
		}
	}
	wybor_usuwanego_towaru(wskaznik, produkty);
}

void usun_towar(Rodzaj *&produkty)
{
	Rodzaj* wskaznik = produkty;
	wyswietl_rodzaje(produkty);
	string nazwa1;
	cin >> nazwa1;
	while (wskaznik != NULL)
	{
		if (wskaznik->nazwa == nazwa1)
		{
			if (wskaznik->zamowienie != NULL)
			{
				cout << "Nie mozesz usunac tego towaru, najpierw usun wszystkie zamowienia na ten towar" << endl;
				return;
			}
			wybor_usuwanego_towaru(wskaznik, produkty);
			return;
		}
		wskaznik = wskaznik->nast;
	}
	cout << "Nie ma takiego towaru, ponow probe" << endl;
	wyswietl_rodzaje(produkty);
	usun_towar(produkty);
}

void wybor_edytowanego_zamowienia(Rodzaj*&wskaznik,Kontrahent *lista)
{
	Towar*lista_towarow = wskaznik->zamowienie;
	int nr,n=0,dzien1,miesiac1,rok1,liczba_sztuk1;
	cin >> nr;
	while (n == nr)
	{
		if (lista_towarow->nast == NULL)
		{
			cout << "Nie ma zamowienie o takim numerze" << endl
				<< "Ponow probe:" << endl;
			wybor_edytowanego_zamowienia(wskaznik,lista);
			return;
		}
		lista_towarow = lista_towarow->nast;
		n++;
	}
	char znak = edycja_menu();
	while (znak != 0)
	{
		switch (znak)
		{
		case'1':
			cout << "Podaj nowa liczbe sztuk towaru:" << endl;
			cin >> liczba_sztuk1;
			lista_towarow->liczba_sztuk = liczba_sztuk1;
			znak = edycja_menu();
			break;
		case'2':
			cout << "Podaj nowy dzien zamowienia towaru:" << endl;
			cin >> dzien1;
			cout << "Podaj nowy miesiac zamowienia towaru:" << endl;
			cin >> miesiac1;
			cout << "Podaj nowy rok zamowienia towaru:" << endl;
			cin >> rok1;
			lista_towarow->dzien = dzien1;
			lista_towarow->miesiac = miesiac1;
			lista_towarow->rok = rok1;
			znak = edycja_menu();
			break;
		case'0':
			znak = 0;
			break;
		default:
			cout << "Nie ma takiego znaku, podaj inny" << endl;
			znak = edycja_menu();
			break;
		}
	}
}

void edytuj(Rodzaj*&produkty, Kontrahent *lista)
{
	Rodzaj*wskaznik = produkty;
	wyswietl_rodzaje(produkty);
	string nazwa1;
	cin >> nazwa1;
	while (wskaznik != NULL)
	{
		if (wskaznik->nazwa == nazwa1)
		{
			int n = 0;
			wyswietl_zamowienia(wskaznik,n);
			wybor_edytowanego_zamowienia(wskaznik,lista);
			return;
		}
		wskaznik = wskaznik->nast;
	}
	cout << "Nie ma takiego towaru, ponow probe" << endl;
	edytuj(produkty,lista);
}

void zapisz(Rodzaj *produkty, Kontrahent *lista)
{
	ofstream plik2("lista_kontrahentow.dat", ios::out | ios::binary);
	plik2.write((char*)produkty, sizeof(Kontrahent) * 3);
	plik2.close();
	ofstream plik("lista_produktow.dat", ios::out | ios::binary);
	plik.write((char*)produkty, sizeof(Rodzaj)*3);
	plik.close();
}

void wczytaj(Rodzaj *produkty, Kontrahent *lista)
{
	ifstream plik2("lista_kontrahentow.dat", ios::in | ios::binary);
	plik2.read((char*)produkty, sizeof(Kontrahent) * 3);
	plik2.close();
	ifstream plik("lista_produktow.dat", ios::in | ios::binary);
	plik.read((char*)produkty, sizeof(Rodzaj) * 3);
	plik.close();
}

void usuwanie_z_pamieci(Rodzaj *&produkty, Kontrahent *&lista)
{
	Rodzaj*wskaznik=produkty;
	Towar*zamowienia;
	Rodzaj*wskaznik_poprz=produkty;
	Kontrahent *kontrahenci = lista;
	Kontrahent *kontrahenci_poprz = lista;
	if (produkty != NULL)
	{
		Towar* zamowienia_poprz = produkty->zamowienie;
		while (wskaznik->nast != NULL)
		{
			while (wskaznik->nast != NULL)
			{
				if (wskaznik->nast->nast == NULL)
					wskaznik_poprz = wskaznik;
				wskaznik = wskaznik->nast;
			}
			if (wskaznik->zamowienie != NULL)
			{
				zamowienia = wskaznik->zamowienie;
				while (zamowienia->nast != NULL)
				{
					while (zamowienia->nast != NULL)
					{
						if (zamowienia->nast->nast == NULL)
							zamowienia_poprz = zamowienia;
						zamowienia = zamowienia->nast;
					}
					delete zamowienia->kupiec;
					delete zamowienia;
					zamowienia_poprz->nast = NULL;
					zamowienia = wskaznik->zamowienie;
				}
				delete zamowienia;
			}
			delete wskaznik;
			wskaznik_poprz->nast = NULL;
			wskaznik = produkty;
		}
		delete wskaznik;
	}
	if (lista != NULL)
	{
		while (kontrahenci->nast != NULL)
		{
			while (kontrahenci->nast != NULL)
			{
				if (kontrahenci->nast->nast == NULL)
					kontrahenci_poprz = kontrahenci;
				kontrahenci = kontrahenci->nast;
			}
			delete kontrahenci;
			kontrahenci_poprz->nast = NULL;
			kontrahenci = lista;
		}
		delete kontrahenci;
	}
}

int main()
{
	Rodzaj * produkty = NULL;
	Kontrahent * lista = NULL;
	//wczytaj(produkty, lista);
	char znak = menu();
	while (znak != '0')
	{
		switch (znak)
		{
		case '1':
			dodaj_rodzaj(produkty);
			znak = menu();
			break;
		case '2':
			dodaj_zamowienie(produkty, lista);
			znak = menu();
			break;
		case '3':
			dodaj_kontrahenta(lista);
			znak = menu();
			break;
		case '4':
			wyswietl_dane(produkty);
			wybor(produkty);
			znak = menu();
			break;
		case'5':
			usun_zamowienie(produkty);
			znak = menu();
			break;
		case '6':
			usun_towar(produkty);
			znak = menu();
			break;
		case '7':
			wyszukaj_towar(produkty);
			znak = menu();
			break;
		case '8':
			edytuj(produkty,lista);
			znak = menu();
			break;
		case'9':
			zapisz(produkty, lista);
			znak = menu();
			break;
		case '0':
			break;
		default:
			cout << "Nie ma takiego znaku, podaj inny" << endl;
			znak = menu();
			break;
		}
	}
	usuwanie_z_pamieci(produkty, lista);
	return 0;
}