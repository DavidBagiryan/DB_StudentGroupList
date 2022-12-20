#include "db_var1.h"
#include <clocale>				// нужен для setlocale

int main() {
	setlocale(0, "Russian");	// разрешаем вывод латинский символов в консоль

	db_var1::StudyGroupList study_list;
	study_list.Start();
}