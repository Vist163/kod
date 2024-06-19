#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

struct prace {
	int prace_postavka;
	int prace_prodaza;
};
typedef struct
{
	int id;
	char name[N];
	struct prace pr;
	int kilkict;
	int masa;
	char vud[N];
	char kraina[N];
	char ckladova[N];
}Kava;

FILE* kav;
// глобальні змінні
char filles[100];
int dim;
// прототипи фунцій
int openFile(const char[], const char[]);
Kava* dinamicmasiv(int);
void infomemory(Kava* massiv);
void Manager();
void Customer();
void cklad();
void powykkava(int coun, Kava* massiv);
void sortyvanya(int coun, Kava* massiv);
int ckankav(Kava* massiv);
int ckan_id(Kava* massiv, int coun);
int adkava(Kava* massiv, int coun, int id_kav);
int deletekavu(Kava* massiv, int coun);
void redagkavu(int coun, Kava* massiv);
void infakavu(int coun, Kava* massiv);

int openFile(const char mode[], const char files[])
{
	if(fopen_s(&kav, files, mode) != NULL)
	{
		puts(" Не вдалося відкрити файл, або його не існує \n");
		return 0;
	}
	else {
		return 1;
	}
}

Kava* dinamicmasiv(int dim) {
	Kava* massive = (Kava*)malloc(dim * sizeof(Kava));
	if (massive == NULL) {
		return NULL;
	}
	else {
		return massive;
	}
}

void infomemory(Kava* massiv)
{
	if (massiv == NULL) {
		puts("\nОшибка динамічний масив не був створений!");
	}
	else {
		puts("\nПам'ять для динамічного масива була розподілена!");
	}
}

int ckankav(Kava* massiv) {
	openFile("r", filles);
	int x, v = 0;
	for (int i = 0; i < dim; i++) {
		fscanf_s(kav, "%d  ", &massiv[i].id);
		fscanf_s(kav, "%s ", massiv[i].name, N);
		fscanf_s(kav, "%d ", &massiv[i].pr.prace_postavka);
		fscanf_s(kav, "%d ", &massiv[i].pr.prace_prodaza);
		fscanf_s(kav, "%d ", &massiv[i].kilkict);
		fscanf_s(kav, "%d ", &massiv[i].masa);
		fscanf_s(kav, "%s ", massiv[i].vud, N);
		fscanf_s(kav, "%s ", massiv[i].kraina, N);
		fscanf_s(kav, "%s ", massiv[i].ckladova, N);
		x = massiv[i].id;
		if (x > -1) {
			v++;
		}
	}
	fclose(kav);
	return v;
}

int ckan_id(Kava* massiv, int coun) {
	int max = 0;
	for (int i = 0; i < coun; i++) {
		if (massiv[i].id > max) {
			max = massiv[i].id;
		}
	}
	return max;
}

void cklad() {
	int cka, coun, id_kav;
	int podtver;
	Kava* massiv;
	massiv = dinamicmasiv(dim);
	infomemory(massiv);
	do {
		coun = ckankav(massiv);
		id_kav = ckan_id(massiv, coun);
		puts("\n Меню склада");
		printf(" В складе %d вид кав\n", coun);
		puts(" 1. Додати каву на продаж");
		puts(" 2. Показати інформацію про кав");
		puts(" 3. Редагувати каву");
		puts(" 4. Видалити каву");
		puts(" 0. для повернення в меню");
		printf(" Оберіть опцію меню: ");
		scanf_s("%d", &cka);
		switch (cka)
		{
		case 0: return 0; break;
		case 1:
			puts("Ви точно хочете добавити каву? (1-да, 0-ні)");
			scanf_s("%d", &podtver);
			if (podtver == 1) {
				adkava(massiv, coun, id_kav);
			}
			break;
		case 2:
			infakavu(coun, massiv);
			break;
		case 3:
			puts("Ви точно хочете редагувати каву? (1-да, 0-ні)");
			scanf_s("%d", &podtver);
			if (podtver == 1) {
				redagkavu(coun, massiv);
			}
			break;
		case 4:
			puts("Ви точно хочете видалити каву? (1-да, 0-ні)");
			scanf_s("%d", &podtver);
			if (podtver == 1) {
				deletekavu(massiv, coun);
			}
			break;
		default:
			puts("\n Невірно було обрано опцию.");
			break;
		}
	} while (cka != 0);
	free(massiv);
}

void redagkavu(int coun, Kava* massiv)
{
	if (coun == 0) {
		puts(" Вибачте, немає кав для редагування");
	}
	else{
	printf("Введіть номер кави, яку хотіли редагувати: ");
	int m, b, f = -1;
	scanf_s("%d", &m);
	for (int с = 0; с < coun; с++) {
		if (massiv[с].id == m) {
			f = с;
		}
	}
	if (f != -1) {
		do {
			puts("\n Меню редагування");
			puts(" 1) Назву кави");
			puts(" 2) Ціну за одиницю товару (поставки)");
			puts(" 3) Ціну за одиницю товару (продажі)");
			puts(" 4) Кількість одиниць товару (одн. пакетів)");
			puts(" 5) Массу нетто");
			puts(" 6) Вид кави");
			puts(" 7) Країну виробника");
			puts(" 8) Склад кави");
			puts("Виберіть опцію, яку хочете редагувати або введіть 0 для виходу із меню");
			scanf_s("%d", &b);
			switch (b)
			{
			case 0:return 0; break;
			case 1:
				printf(" Введіть назву кави: ");
				scanf_s("%s", massiv[f].name, N); break;
			case 2:
				printf(" Введіть ціну кави за одиницю товару (поставка): ");
				scanf_s("%d", &massiv[f].pr.prace_postavka); break;
			case 3:
				printf(" Введіть ціну кави за одиницю товару (продаж): ");
				scanf_s("%d", &massiv[f].pr.prace_prodaza); break;
			case 4:
				printf(" Введіть кількість одиниць (пакетів): ");
				scanf_s("%d", &massiv[f].kilkict); break;
			case 5:
				printf(" Введіть массу нетто в грамах: ");
				scanf_s("%d", &massiv[f].masa); break;
			case 6:
				printf(" Введіть вид кави (зерно або молота): ");
				scanf_s("%s", massiv[f].vud, N); break;
			case 7:
				printf(" Введіть країну виробника: ");
				scanf_s("%s", massiv[f].kraina, N); break;
			case 8:
				printf(" Введіть склад кави (арабіка, робуста): ");
				scanf_s("%s", massiv[f].ckladova, N); break;
			default:
				puts("\n Невірно було обрано опцию.");
				break;
			}
			openFile("w+", filles);
			for (int i = 0; i < coun; i++) {
				fprintf(kav, "\n%d ", massiv[i].id);
				fprintf(kav, "%s ", massiv[i].name);
				fprintf(kav, "%d ", massiv[i].pr.prace_postavka);
				fprintf(kav, "%d ", massiv[i].pr.prace_prodaza);
				fprintf(kav, "%d ", massiv[i].kilkict);
				fprintf(kav, "%d ", massiv[i].masa);
				fprintf(kav, "%s ", massiv[i].vud);
				fprintf(kav, "%s ", massiv[i].kraina);
				fprintf(kav, "%s ", massiv[i].ckladova);
			}
			fclose(kav);
		} while (b != 0);
	}
	else {
		puts(" Неправильно було введено номер кави");
	}
	}
}

int deletekavu(Kava* massiv, int coun) {
	if (coun == 0) {
		puts(" Вибачте, немає кав для видалення");
	}
	else {
		printf("Введіть номер кави, якого бажаєте видалити: ");
		int v;
		int k = -1;
		scanf_s("%d", &v);
		for (int m = 0; m < coun; m++) {
			if (massiv[m].id == v) {
				k = m;
			}
		}
		if (k != -1) {
			for (k; k < coun; k++) {
				massiv[k] = massiv[k + 1];
			}
			coun--;
			openFile("w+", filles);
			for (int i = 0; i < coun; i++) {
				fprintf(kav, "\n%d ", massiv[i].id);
				fprintf(kav, "%s ", massiv[i].name);
				fprintf(kav, "%d ", massiv[i].pr.prace_postavka);
				fprintf(kav, "%d ", massiv[i].pr.prace_prodaza);
				fprintf(kav, "%d ", massiv[i].kilkict);
				fprintf(kav, "%d ", massiv[i].masa);
				fprintf(kav, "%s ", massiv[i].vud);
				fprintf(kav, "%s ", massiv[i].kraina);
				fprintf(kav, "%s ", massiv[i].ckladova);
			}
			fclose(kav);
		}
		else {
			puts(" Неправильно було введено номер кави");
		}
	}
}

void infakavu(int coun, Kava* massiv)
{
	if (coun == 0) {
		puts(" Вибачте, немає кав для перегляду");
	}
	else {
		printf("\nІнформація про каву:\n");
		printf("|№ кави|  Назва кави  |  Ціна (поставка)  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
		for (int i = 0; i < coun; i++) {
			printf("| №%d   |%14s| %18d| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_postavka, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
		}
	}
}

int adkava(Kava* massiv, int coun, int id_kav)
{
	massiv[coun].id = id_kav + 1;
	printf(" Введіть назву кави: ");
	scanf_s("%s", massiv[coun].name, N);
	printf(" Введіть ціну кави за одиницю товару (поставка): ");
	scanf_s("%d", &massiv[coun].pr.prace_postavka);
	printf(" Введіть ціну кави за одиницю товару (продаж): ");
	scanf_s("%d", &massiv[coun].pr.prace_prodaza);
	printf(" Введіть кількість одиниць: ");
	scanf_s("%d", &massiv[coun].kilkict);
	printf(" Введіть массу нетто в грамах: ");
	scanf_s("%d", &massiv[coun].masa);
	printf(" Введіть вид кави (зерно або молота): ");
	scanf_s("%s", massiv[coun].vud, N);
	printf(" Введіть країну виробника: ");
	scanf_s("%s", massiv[coun].kraina, N);
	printf(" Введіть склад кави (арабіка, робуста): ");
	scanf_s("%s", massiv[coun].ckladova, N);
	openFile("at", filles);
	fprintf(kav, "\n%d ", massiv[coun].id);
	fprintf(kav, "%s ", massiv[coun].name);
	fprintf(kav, "%d ", massiv[coun].pr.prace_postavka);
	fprintf(kav, "%d ", massiv[coun].pr.prace_prodaza);
	fprintf(kav, "%d ", massiv[coun].kilkict);
	fprintf(kav, "%d ", massiv[coun].masa);
	fprintf(kav, "%s ", massiv[coun].vud);
	fprintf(kav, "%s ", massiv[coun].kraina);
	fprintf(kav, "%s ", massiv[coun].ckladova);
	fclose(kav);
}

void Manager() {
	int vedpass;
	int pass = 1111;
	do {
		puts(" Введіть пароль для входу! Або введіть 0 для повернення в меню");
		scanf_s("%d", &vedpass);
		if (vedpass == pass) {
			cklad();
			break;
		}
		else {
			puts(" Не правильний пароль для входу!");
		}
	} while (vedpass != 0);
}


int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int vubor,bonih=-1,x;
	if (argc == 2) {
		strcpy_s(filles, sizeof(filles), argv[1]);
		bonih=openFile("r", filles);
		if (bonih == 0) {
			char tertu[100];
			do {
				puts(" Введіть путь до текстового файла кав");
				scanf_s("%s", tertu, 99);
				strcpy_s(filles, sizeof(filles), tertu);
				bonih = openFile("r", filles);
			} while (bonih == 0);
		}
		fclose(kav);
	}
	else if (argc == 1) {
		char tertu[100];
		do {
			puts(" Введіть путь до текстового файла кав");
			scanf_s("%s", tertu, 99);
			strcpy_s(filles, sizeof(filles), tertu);
			bonih = openFile("r", filles);
		} while (bonih == 0);
		fclose(kav);
	}
	do {
		puts(" Введіть кількість кав для яких буде розподілена пам'ять (більше 10 но рекомендується 50)");
		scanf_s("%d", &dim);
	} while (dim < 10);
	do {
		puts("\n Меню");
		puts(" 1. Менеджер");
		puts(" 2. Покупець");
		puts(" 0. виход із програми");
		printf(" Оберіть опцію меню: ");
		scanf_s("%d", &vubor);
		switch (vubor)
		{
		case 0: return 0;break;
		case 1:Manager();break;
		case 2:Customer();break;
		default:
			puts("\n Невірно було обрано опцию.");
			break;
		}
	} while (vubor != 0);
	return 0;
}

void Customer()
{
	int coun;
	Kava* massiv;
	massiv = dinamicmasiv(dim);
	coun = ckankav(massiv, dim);
	int cus;
	do {
		puts("\n Меню");
		puts(" 1. Зробити замовляння");
		puts(" 2. Показати інформацію про кав які на продажі");
		puts(" 3. Пошук");
		puts(" 4. Сортування");
		puts(" 0. для повернення в меню");
		printf(" Оберіть опцію меню: ");
		scanf_s("\n %d", &cus);
		switch (cus)
		{
		case 0:return 0; break;
		case 1:
			zamovlennya(coun, massiv);
			break;
		case 2:
			if (coun==0) {
				puts("Вибачте, на продажі немає кав");
			}
			else {
				printf("\nІнформація про каву:\n");
				printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
				for (int i = 0; i < coun; i++) {
					if (massiv[i].kilkict > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
			}
			break;
		case 3:
			powykkava(coun, massiv);
			break;
		case 4:
			sortyvanya(coun, massiv);
			break;
		default:
			puts("\n Невірно було обрано опцию.");
			break;
		}
	} while (cus != 0);
	free(massiv);
}

int zamovlennya(int coun, Kava* massiv) {
	if (coun == 0) {
		puts("Вибачте, на продажі немає кав щоб замовити");
	}
	else {
		int caseew = 0, casew, zamovkilkct, bud = -2;
		char zamovname[N];
		int prosda;
		do {
			bud = -2;
			printf(" Введіть назву кави (повну назву): ");
			scanf_s("%s", zamovname, N);
			for (int i = 0; i < coun; i++) {
				if (strstr(zamovname, massiv[i].name) && massiv[i].kilkict > 0) {
					bud = i;
				}
			}
			if (bud == -2) {
				puts(" Неправильно або некоретно було введено назва або такої кави нема");
			}
			else {
				printf(" Введіть кількість пакетів: ");
				scanf_s("%d", &zamovkilkct);
				if (zamovkilkct <= massiv[bud].kilkict && massiv[bud].kilkict > 0) {
					casew = massiv[bud].pr.prace_prodaza * zamovkilkct;
					printf("\n Ви замовили %s; кількість пакетів %d; Сума замовлення: %d \n", zamovname, zamovkilkct, casew);
					puts(" Ви підтверджуєте замовлення? (1-да 0-ні)");
					int mok;
					scanf_s("%d", &mok);
					if (mok == 1) {
						caseew += casew;
						printf("\n Сума всіх замовлення: %d \n", caseew);
						massiv[bud].kilkict -= zamovkilkct;
						openFile("w+", filles);
						for (int i = 0; i < coun; i++) {
							fprintf(kav, "\n%d ", massiv[i].id);
							fprintf(kav, "%s ", massiv[i].name);
							fprintf(kav, "%d ", massiv[i].pr.prace_postavka);
							fprintf(kav, "%d ", massiv[i].pr.prace_prodaza);
							fprintf(kav, "%d ", massiv[i].kilkict);
							fprintf(kav, "%d ", massiv[i].masa);
							fprintf(kav, "%s ", massiv[i].vud);
							fprintf(kav, "%s ", massiv[i].kraina);
							fprintf(kav, "%s ", massiv[i].ckladova);
						}
						fclose(kav);
					}
					else {
						printf("\n Сума всіх замовлення: %d \n", caseew);
					}
				}
				else
				{
					puts(" Вибачте кількість кави якої ви хочете замовити немає на складі");
				}
			}
			puts(" Хочете замовити еще кави? (1-да,0-ні)");
			scanf_s("%d", &prosda);
		} while (prosda != 0);
	}
}

void powykkava(int coun, Kava* massiv)
{
	if (coun == 0) {
		puts("Вибачте, на продажі немає кав щоб здійснити пошук");
	}
	else {
		int powyk, cas, cas2, cas3,p = 0;;
		char mul[N];
		do {
			puts("\n Меню пошуку");
			puts(" 1. За назвою");
			puts(" 2. За ціною (продажу)");
			puts(" 3. За масаю нетто");
			puts(" 4. За видами кави");
			puts(" 5. За складом кави");
			puts(" 6. За країною виробника");
			puts(" 0. для виходу із меню пошука");
			printf(" Оберіть опцію меню: ");
			scanf_s("%d", &powyk);
			switch (powyk)
			{
			case 1:
				printf(" Введіть назву кави: ");
				scanf_s("%s", mul, N);
				p = 0;
				for (int i = 0; i < coun; i++) {
					if (strstr(massiv[i].name, mul) != NULL && massiv[i].kilkict > 0&&p==0) {
						printf("\nІнформація про каву за пошуком назою:\n");
						printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
						p++;
					}
					else if (strstr(massiv[i].name, mul) != NULL && massiv[i].kilkict > 0 && p > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
				if (p == 0) {
					puts("Вибачте, нічого не знайдено");
				}
				break;
			case 2:
				printf(" Введіть ціну (продажу) з: ");
				scanf_s("%d", &cas2);
				printf(" Введіть ціну (продажу) до: ");
				scanf_s("%d", &cas3);
				p = 0;
				for (int i = 0; i < coun; i++) {
					if (cas2 <= massiv[i].pr.prace_prodaza && massiv[i].pr.prace_prodaza <= cas3 && massiv[i].kilkict > 0 && p == 0) {
						printf("\nІнформація про каву за пошуком ціною (продажу):\n");
						printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
						p++;
					}
					else if (cas2 <= massiv[i].pr.prace_prodaza && massiv[i].pr.prace_prodaza <= cas3 && massiv[i].kilkict > 0 && p > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
				if (p == 0) {
					puts("Вибачте, нічого не знайдено");
				}
				break;
			case 3:
				printf(" Введіть масe нетто (в грамах 500, 1000, 1500): ");
				scanf_s("%d", &cas);
				p = 0;
				for (int i = 0; i < coun; i++) {
					if (cas == massiv[i].masa && massiv[i].kilkict > 0 && p == 0) {
						printf("\nІнформація про каву за пошуком масаю нетто:\n");
						printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
						p++;
					}
					else if (cas == massiv[i].masa && massiv[i].kilkict > 0 && p > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
				if (p == 0) {
					puts("Вибачте, нічого не знайдено");
				}
				break;
			case 4:
				printf(" Введіть вид кави (зерно або молота): ");
				scanf_s("%s", mul, N);
				p = 0;
				for (int i = 0; i < coun; i++) {
					if (strstr(massiv[i].vud, mul) != NULL && massiv[i].kilkict > 0 && p == 0) {
						printf("\nІнформація про каву за пошуком видом кави:\n");
						printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
						p++;
					}
					else if (strstr(massiv[i].vud, mul) != NULL && massiv[i].kilkict > 0 && p > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
				if (p == 0) {
					puts("Вибачте, нічого не знайдено");
				}
				break;
			case 5:
				printf(" Введіть склад кави (арабіка або робуста): ");
				scanf_s("%s", mul, N);
				p = 0;
				for (int i = 0; i < coun; i++) {
					if (strstr(massiv[i].ckladova, mul) != NULL && massiv[i].kilkict > 0 && p == 0) {
						printf("\nІнформація про каву за пошуком складом кави:\n");
						printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
						p++;
					}
					else if (strstr(massiv[i].ckladova, mul) != NULL && massiv[i].kilkict > 0 && p > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
				if (p == 0) {
					puts("Вибачте, нічого не знайдено");
				}
				break;
			case 6:
				printf(" Введіть країну виробника: ");
				scanf_s("%s", mul, N);
				p = 0;
				for (int i = 0; i < coun; i++) {
					if (strstr(massiv[i].kraina, mul) != NULL && massiv[i].kilkict > 0 && p == 0) {
						printf("\nІнформація про каву за пошуком країною виробника:\n");
						printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
						p++;
					}
					else if (strstr(massiv[i].kraina, mul) != NULL && massiv[i].kilkict > 0 && p > 0) {
						printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[i].id, massiv[i].name, massiv[i].pr.prace_prodaza, massiv[i].kilkict, massiv[i].masa, massiv[i].vud, massiv[i].kraina, massiv[i].ckladova);
					}
				}
				if (p == 0) {
					puts("Вибачте, нічого не знайдено");
				}
				break;
			case 0:break;
			default:
				puts(" Неправильно було обрано опцию меню");
				break;
			}
		} while (powyk != 0);
	}
}

void sortyvanya(int coun, Kava* massiv)
{
	if (coun == 0) {
		puts("Вибачте, на продажі немає кав щоб здійснити сортування");
	}
	else {
		int h;
		char* prom;
		do {
			puts("\n Меню сортування");
			puts(" 1. За назвою");
			puts(" 2. За ціною (продажу) з меншого до більшого");
			puts(" 3. За ціною (продажу) з більшого до меншого");
			puts(" 0. для виходу із меню сортування");
			printf(" Оберіть опцію меню: ");
			scanf_s("\n %d", &h);
			switch (h)
			{
			case 1:
				printf("\nІнформація про каву:\n");
				printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
				for (int q = 65; q <= 255; q++) {
					for (int s = 0; s < coun; s++) {
						prom = massiv[s].name;
						if ((char)q == prom[0] && massiv[s].kilkict > 0) {
							printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[s].id, massiv[s].name, massiv[s].pr.prace_prodaza, massiv[s].kilkict, massiv[s].masa, massiv[s].vud, massiv[s].kraina, massiv[s].ckladova);
						}
					}
				}
				break;
			case 2:
				printf("\nІнформація про каву:\n");
				printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
				for (int q = 0; q < 90000; q++) {
					for (int s = 0; s < coun; s++) {
						if (q == massiv[s].pr.prace_prodaza && massiv[s].kilkict > 0) {
							printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[s].id, massiv[s].name, massiv[s].pr.prace_prodaza, massiv[s].kilkict, massiv[s].masa, massiv[s].vud, massiv[s].kraina, massiv[s].ckladova);
						}
					}
				}
				break;
			case 3:
				printf("\nІнформація про каву:\n");
				printf("|№ кави|  Назва кави  |  Ціна (продажу)  | Кількість пакетів  |  Маса нетто (в гр.) |  Вид кави |      Країна     |Склад кави| \n");
				for (int q = 10000000; q > 0; q--) {
					for (int s = 0; s < coun; s++) {
						if (q == massiv[s].pr.prace_prodaza && massiv[s].kilkict > 0) {
							printf("| №%d   |%14s| %16d | %18d | %19d | %9s |  %14s |  %s |\n", massiv[s].id, massiv[s].name, massiv[s].pr.prace_prodaza, massiv[s].kilkict, massiv[s].masa, massiv[s].vud, massiv[s].kraina, massiv[s].ckladova);
						}
					}
				}
				break;
			case 0:break;
			default:
				puts(" Неправильно було обрано опцию меню");
				break;
			}
		} while (h != 0);
	}
}