#include "db_var1.h"

#pragma warning(disable : 4996) // отключение предупреждения в Visual Studio

#include <iostream> // для функий ввода/вывода
#include <iomanip>  // для функций корретировки вывода таблицы
#include <fstream>  // для работы с файлами

using namespace db_var1;

// функция Добавления текстовых данных в массив
template<typename size_t N>             // для автоматического вычисления размера
void AddStr(char(&str)[N]) {
    std::cin.getline(str, str_size__);  // getline для чтения всей строки с пробелами
    if (std::cin.fail()) {              // при переполнении буфера пропускаем не вместившиеся символы
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Запуск программы
void StudyGroupList::Start() {
	std::cout << "[Программа \"Список учебной группы\" запущена.]" << std::endl;
	Menu();
}

// Меню программы
void StudyGroupList::Menu() {
	while (true) {
        std::cout << 
            line__ << '\n' <<
            "1\t- Добавить ученика\n" <<
            "2\t- Изменить запись\n" <<
            "3\t- Удалить запись\n" <<
            "4\t- Вывести список учеников\n" <<
            "5\t- Вывести определенного ученика\n" <<
            "6\t- Сортировать учеников по курсу\n" <<
            "7\t- Сохранить БД в файл\n" <<
            "8\t- Загрузить БД из файла\n" <<
            "9\t- Перевод файла в бинарный\n" <<
            "10\t- Загрузить БД из бинарного файла\n" <<
            "11\t- Распечатать анкетные данные студента, имеющего максимальный средний балл\n" << 
            "0\t- Выход\n" <<
            line__ << std::endl;

        char command[2] = { -1, -1};
        // проверка на ввод цифр
        while (true) {
            std::cin.get(command[0]); if (command[0] == '\n') continue;

            if (!(command[0] >= 48 && command[0] <= 57)) { // код ASCII 48 = '0', код ASCII 57 = '9'
                std::cout << line__ << std::endl;
                continue;
            }
            if (std::cin.peek() && std::cin.peek() != '\n') {
                std::cin.get(command[1]);
                if (!(command[1] >= 48 && command[1] <= 57)) {
                    std::cout << line__ << std::endl;
                    continue;
                }
            }
            std::cout << line__ << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // считали max 2 символа, остальное пропустили
            break;
        }

        int ch = atoi(command); // получаем число
        switch (ch) {
        case 1:
        {
            Add(ind_next_);
            ++ind_next_;        // обновляем индекс

            std::cout << line__ <<
                "\n[Студент " <<
                students_[ind_next_ - 1].surname_ << " " <<
                students_[ind_next_ - 1].name_ << " " <<
                students_[ind_next_ - 1].patronymic_ << " " <<
                "добавлен в список.]" << std::endl;
            break;
        }
        case 2:
            ChangeEntry();
            break;
        case 3:
            DeleteEntry();
            break;
        case 4:
            PrintAll();
            break;
        case 5:
            PrintStudent();
            break;
        case 6:
            SortList();
            break;
        case 7:
            SaveToFile();
            break;
        case 8:
            LoadFromFile();
            break;
        case 9:
            CreateBinaryFile();
            break;
        case 10:
            LoadFromBinaryFile();
            break;
        case 11:
            PrintMostSuccessfulStudent();
            break;
        case 0:
            std::cout << "[Программа \"Список учебной группы\" закрыта.]" << std::endl;
            return;
        default:
            break;
        }
	}
}

// Добавить студента в список
void StudyGroupList::Add(int index) {
    std::cout << "Введите имя: ";
    AddStr(students_[index].name_);
    std::cout << "\nВведите фамилию: ";
    AddStr(students_[index].surname_);
    std::cout << "\nВведите отчество: ";
    AddStr(students_[index].patronymic_);
    std::cout << "\nВведите группу: ";
    AddStr(students_[index].group_);
    std::cout << "\nВведите курс: ";
    std::cin >> students_[index].course_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // записываем первый символ, остальное пропускаем
    std::cout << "\nВведите оценку по программированию: ";
    std::cin >> students_[index].grades_.programming_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nВведите оценку по истории: ";
    std::cin >> students_[index].grades_.history_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nВведите оценку по физической культуре: ";
    std::cin >> students_[index].grades_.phys_сult_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nВведите оценку по геометрии: ";
    std::cin >> students_[index].grades_.geometry_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nВведите оценку по математике: ";
    std::cin >> students_[index].grades_.maths_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Изменить запись в списке
void StudyGroupList::ChangeEntry() {
    if (!PrintAll()) return;

    std::cout << "[Введите id соответствующей записи для редактирования.]" << std::endl;

    int tmp = 0;
    std::cin >> tmp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tmp < 0 || tmp >= ind_next_) {
        std::cout << "[Такой записи нет!]\n" << line__ << std::endl;;
        return;
    }

    Add(tmp); // перезаписываем
}

// Удалить запись из списка
void StudyGroupList::DeleteEntry() {
    if (!PrintAll()) return;
    
    std::cout << "[Введите id соответствующей записи для удаления.]" << std::endl;

    int tmp = 0;
    std::cin >> tmp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tmp < 0 || tmp >= ind_next_) {
        std::cout << "Такой записи нет\n";
        return;
    }

    for (int i = tmp; i < ind_next_; ++i)   // "удаляем" запись смещением данных в массиве
    {
        students_[i] = students_[i + 1];
    }
    --ind_next_;                            // обновляем индекс

    std::cout << "[Запись успешно удалена.]" << std::endl;
}

// Вывести весь список
bool StudyGroupList::PrintAll() {
    if (ind_next_ == 0) {
        std::cout << "[Список пуст!]" << std::endl;
        return false;   // возвращаем флаг, что вывода не было
    }

    // определим ширину столбцов для таблицы
    int ind_s = 1;      
    ind_next_ > 9 ? ind_s = 2 : ind_s = 1;
    int name_max_s = 5;
    int group_max_s = 5;
    for (int i = 0; i < ind_next_; ++i) // находим максимальную длину ФИО и Группы в таблице,
    {                                   // т.к. это единственные поля, где разрешён ввод > 1 символа
        int width_name = strlen(students_[i].name_) + strlen(students_[i].surname_) + strlen(students_[i].patronymic_) + 2;
        if (name_max_s < width_name) name_max_s = width_name;
        int width_group = strlen(students_[i].group_) - 1;
        if (group_max_s < width_group) group_max_s = width_group;
    }

    int alignment_student = name_max_s + group_max_s + 7;   // ширина отступа в шапке Студент
    if (alignment_student % 2 != 0) {
        ++alignment_student;
        ++name_max_s;
    }

    // шапка таблицы
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(alignment_student) << std::left << "Студент" << '|' << std::right << std::setw(18) << "Оценки" << std::setw(18) << '|' << '\n';
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(name_max_s) << std::left << "ФИО" << '|' << std::setw(group_max_s + 1) << "Группа" << '|' << "Курс" << '|' << "Мат." << '|' << "Геом." << '|' << "Физ.культ." << '|' << "Програм." << '|'  << "Ист." << '|' << '\n';
    // записи в таблице
    for (int i = 0; i < ind_next_; ++i) {
        PrintOne(i, ind_s, name_max_s, group_max_s);
    }
    std::cout << line__ << std::endl;
}

// Вывести одиночную запись из таблицы
void StudyGroupList::PrintOne(int id, int ind_max_size, int name_max_size, int group_max_size) {
    char fio_buff[3 * str_size__ + 2] = {};         // буфер для хранения Фамилии Имени Отчества в одной строке; 2 - пробелы
    strcat_s(fio_buff, 3 * str_size__ + 2, students_[id].surname_);
    strcat_s(fio_buff, 3 * str_size__ + 2, " ");    // добавляем пробелы
    strcat_s(fio_buff, 3 * str_size__ + 2, students_[id].name_);
    strcat_s(fio_buff, 3 * str_size__ + 2, " ");
    strcat_s(fio_buff, 3 * str_size__ + 2, students_[id].patronymic_);
    std::cout << std::setw(ind_max_size) << id << '|' << std::setw(name_max_size) << std::left << fio_buff << '|' << std::setw(group_max_size + 1) << students_[id].group_ << '|' << std::setw(4) << students_[id].course_ << '|' << std::setw(4) << students_[id].grades_.maths_ << '|' << std::setw(5) << students_[id].grades_.geometry_ << '|' << std::setw(10) << students_[id].grades_.phys_сult_ << '|' << std::setw(8) << students_[id].grades_.programming_ << '|' << std::setw(4) << students_[id].grades_.history_ << '|' << std::right << '\n';
}

// Вывести запись по id
void StudyGroupList::PrintStudent() {
    if (!PrintAll()) return;

    std::cout << "[Введите id соответствующей записи для вывода информации.]" << std::endl;

    int tmp = 0;
    std::cin >> tmp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tmp < 0 || tmp >= ind_next_) {
        std::cout << "[Такой записи нет!]\n";
        return;
    }

    int ind_s = 1;
    tmp > 9 ? ind_s = 3 : ind_s = 2;

    int name_s = 5;
    int group_s = 5;
    int width_name = strlen(students_[tmp].name_) + strlen(students_[tmp].surname_) + strlen(students_[tmp].patronymic_) + 2;
    if (name_s < width_name) name_s = width_name;
    int width_group = strlen(students_[tmp].group_) - 1;
    if (group_s < width_group) group_s = width_group;

    int alignment_student = name_s + group_s + 7;
    if (alignment_student % 2 != 0) {
        ++alignment_student;
        ++name_s;
    }
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(alignment_student) << std::left << "Студент" << '|' << std::right << std::setw(18) << "Оценки" << std::setw(18) << '|' << '\n';
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(name_s) << std::left << "ФИО" << '|' << std::setw(group_s + 1) << "Группа" << '|' << "Курс" << '|' << "Мат." << '|' << "Геом." << '|' << "Физ.культ." << '|' << "Програм." << '|' << "Ист." << '|' << '\n';
    PrintOne(tmp, ind_s, name_s, group_s);
}

// Сортировка списка по возрастанию Курса
void StudyGroupList::SortList() {
    // пузырьковая сортировка
    Student temp;   // буфер
    for (int i = 0; i < ind_next_ - 1; i++) {   // сужение массива путём смещения точки старта анализа
        for (int j = i + 1; j < ind_next_; j++) // сдвиг некоторого элемента в край
        {
            if (students_[i].course_ > students_[j].course_) {
                temp = students_[i];
                students_[i] = students_[j];
                students_[j] = temp;
            };
        }
    }
    std::cout << "[Сортировка списка по возрастанию успешно завершена.]" << std::endl;
}

// Сохранить базу данных в файл
void StudyGroupList::SaveToFile() {
    std::ofstream out("DB.txt", std::ios::app); // флаг app - писать только в конец файла, дополняя его
    if (!out.is_open()) {
        std::cout << "[Файл не удалось открыть.]" << std::endl;
        return;
    }
    if (ind_next_ == 0) {
        std::cout << "[Список пуст!]" << std::endl;
        return;
    }

    for (int i = 0; i < ind_next_; i++) {
        out <<
            students_[i].name_ << '\n' <<
            students_[i].surname_ << '\n' <<
            students_[i].patronymic_ << '\n' <<
            students_[i].group_ << '\n' <<
            students_[i].course_ << '\n' <<
            students_[i].grades_.maths_ << '\n' <<
            students_[i].grades_.geometry_ << '\n' <<
            students_[i].grades_.phys_сult_ << '\n' <<
            students_[i].grades_.programming_ << '\n' <<
            students_[i].grades_.history_ << '\n';
    }
    out.close();
    std::cout << "[База данных в файле DB.txt успешно обновлена]" << std::endl;
}

// Загрузить базу данных из файла
void StudyGroupList::LoadFromFile() {
    int count_line = CountLinesInFile();
    if (count_line == 0) return;

    if (ind_next_ != 0) {   // проверяем, пуст ли список
        std::cout << "[Вы хотите очистить список перед загрузкой данных из файла?]\n[1 - Да]" << std::endl;
        char tmp = 0;
        std::cin >> tmp;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (tmp == '1') {
            for (int i = ind_next_ - 1; i >= 0; --i) {
                students_[i] = students_[i + 1];
                --ind_next_;
            }
        }
    }

    int count_student = count_line / 10;                                // находим кол-во структур Student
    if (count_student > s_g_l_size__) count_student = s_g_l_size__;     // если студентов в базе больше max размера списка,
                                                                        // сразу пропускаем
    std::ifstream fin("DB.txt");
    if (!fin)
    {
        std::cout << "[Текстовый файл не удалось открыть.]" << std::endl;
        return;
    }

    int ind_next = ind_next_;   // записываем, размер списка до добавления записей
    for (int i = ind_next; i < count_student + ind_next; i++) {
        fin.getline(students_[i].name_, str_size__);
        fin.getline(students_[i].surname_, str_size__);
        fin.getline(students_[i].patronymic_, str_size__);
        fin.getline(students_[i].group_, str_size__);
        fin >> students_[i].course_;
        fin >> students_[i].grades_.maths_;
        fin >> students_[i].grades_.geometry_;
        fin >> students_[i].grades_.phys_сult_; 
        fin >> students_[i].grades_.programming_;
        fin >> students_[i].grades_.history_;
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // пропускаем символ перевода строки
        ++ind_next_;                                                    // обновляем список
    }
    fin.close();

    std::cout << "[База данных из текстового файла успешно загружена.]" << std::endl;
}

// Подсчитать число строк в файле
int StudyGroupList::CountLinesInFile() {
    auto* in = fopen("DB.txt", "a+t");  // открываем файл для чтения-записи, получаем указатель на него
    int counter = 0;                    // предполагаем, что строк ноль в файле - т.е. пустой
    if (in == NULL) {
        std::cout << "[Текстовый файл не удалось открыть.]" << std::endl;
        return 0;
    }
    else {
        int ch, pre = EOF;              // текущий символ, последний считаный символ

        /* в цикле считаем сколько переводов строки в файле и запоминаем это в переменную counter
         а также выводим на экран каждый считаный символ.
         если файл пустой, то тело цикла не выполнится ни разу, так как первый считанный символ будет как раз EOF
         и в pre останется EOF */
        while ((ch = fgetc(in)) != EOF) {   // в цикле проходим весь файл посимвольно
            pre = ch;                       // запоминаем последний считаный символ
            if (ch == '\n') ++counter;      // если нашли перевод строки, то увеличиваем счетчик строк
        }
        fclose(in);

        /* весь смысл переменной pre в том, чтобы запомнить какой символ мы считали перед тем как наткнулись на EOF в файле
         или в pre будет EOF - если тело цикла ни разу не выполнилось, это будет при пустом файле
         последняя строка файла может заканчиваться не \n, а строку посчитать надо - вот для этого и нужна переменная pre */

        if (pre == EOF) {   // если файл пустой
            std::cout << "[Файл пустой!]" << std::endl;
            return 0;
        }
        else if (pre != '\n') ++counter;   // если pre содержит в себе не перевод строки, и файл не пустой, то увеличиваем счетчик строк
    }

    if (counter % 10 != 0) {    // на 1 студента 10 строк информации
        std::cout << "[Данные в файле не полные!]";
        return 0;               // выходим, для корректной работы программы
    }
    return counter;
}

// Создать бинарный файл базы данных из текстового
void StudyGroupList::CreateBinaryFile() {
    std::ofstream out("DB.bin", std::ios::binary | std::ios::out);
    if (!out.is_open()) {
        std::cout << "[Бинарный файл не удалось открыть.]" << std::endl;
        return;
    }
    std::ifstream in("DB.txt");
    if (!in.is_open()) {
        std::cout << "[Текстовый файл не удалось открыть.]" << std::endl;
        return;
    }

    int count_line = CountLinesInFile();    // находим число строк в текстовом файле
    if (count_line == 0) return;            // сразу выходим после ошибки, для корректной работы программы

    Student students_from_file;             // создаём временное хранилище, для чтения из файла
    
    int count_student = count_line / 10;    // находим кол-во структур Student
    for (int i = 0; i < count_student; i++) {
        in.getline(students_from_file.name_, str_size__);
        in.getline(students_from_file.surname_, str_size__);
        in.getline(students_from_file.patronymic_, str_size__);
        in.getline(students_from_file.group_, str_size__);
        in >> students_from_file.course_;
        in >> students_from_file.grades_.maths_;
        in >> students_from_file.grades_.geometry_;
        in >> students_from_file.grades_.phys_сult_;
        in >> students_from_file.grades_.programming_;
        in >> students_from_file.grades_.history_;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');           // пропускаем символ перевода строки

        out.write((char*)&students_from_file, sizeof(students_from_file));      // записываем структуру Student в бинарный файл
    }

    in.close();
    out.close();

    std::cout << "[База данных из текстового файла успешно сохранена в бинарном файле.]" << std::endl;
}

// Загрузить базу данных из бинарного файла
void StudyGroupList::LoadFromBinaryFile() {
    std::ifstream in("DB.bin", std::ios::binary | std::ios::in);
    if (!in.is_open()) {
        std::cout << "[Бинарный файл не удалось открыть.]" << std::endl;
        return;
    }

    if (ind_next_ != 0) {   // проверяем, пуст ли список
        std::cout << "[Вы хотите очистить список перед загрузкой данных из файла?]\n[1 - Да]" << std::endl;
        char tmp = 0;
        std::cin >> tmp;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (tmp == '1') {
            for (int i = ind_next_ - 1; i >= 0; --i) {
                students_[i] = students_[i + 1];
                --ind_next_;
            }
        }
    }

    // определяем количество структур в файле
    in.seekg(0, in.end);                    // перемещаем указатель чтения в конец файла
    unsigned int tripsCount = in.tellg();   // записываем позицию указателя в переменную, она равна количеству байт в файле
    tripsCount /= sizeof(Student);          // делим общее количество байт в файле на количество байт занимаемых одной структурой
    in.seekg(0, in.beg);                    // возвращаем указатель чтения в начало файла

    int ind_next = ind_next_;
    for (int i = ind_next; i < tripsCount + ind_next; i++) {
        in.read((char*)&students_[i], sizeof(students_[i]));
        ++ind_next_;
    }

    std::cout << "[База данных из бинарного файла успешно загружена.]" << std::endl;
}

// Вывести запись о студенте, имеющем максимальный средний балл
void StudyGroupList::PrintMostSuccessfulStudent() {
    int successful_student_id = 0;
    float gpa = 0, gpa_max = -1.0;
    for (int i = 0; i < ind_next_; i++) {
        gpa = (students_[i].grades_.maths_ + students_[i].grades_.geometry_
            + students_[i].grades_.phys_сult_ + students_[i].grades_.programming_
            + students_[i].grades_.history_) / 5;
        if (gpa_max < gpa) {
            gpa_max = gpa;
            successful_student_id = i;
        }
    }

    // определим ширину столбцов для таблицы
    int ind_s = 1;     
    successful_student_id > 9 ? ind_s = 2 : ind_s = 1;
    int name_max_s = 5;
    int group_max_s = 5;

    int width_name = strlen(students_[successful_student_id].name_) + strlen(students_[successful_student_id].surname_) + strlen(students_[successful_student_id].patronymic_) + 2;
    if (name_max_s < width_name) name_max_s = width_name;
    int width_group = strlen(students_[successful_student_id].group_) - 1;
    if (group_max_s < width_group) group_max_s = width_group;

    int alignment_student = name_max_s + group_max_s + 7;
    if (alignment_student % 2 != 0) {
        ++alignment_student;
        ++name_max_s;
    }

    std::cout << std::setw(ind_s + 1) << '|' << std::setw(alignment_student) << std::left << "Студент" << '|' << std::right << std::setw(18) << "Оценки" << std::setw(18) << '|' << '\n';
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(name_max_s) << std::left << "ФИО" << '|' << std::setw(group_max_s + 1) << "Группа" << '|' << "Курс" << '|' << "Мат." << '|' << "Геом." << '|' << "Физ.культ." << '|' << "Програм." << '|' << "Ист." << '|' << '\n';
    PrintOne(successful_student_id, ind_s, name_max_s, group_max_s);
    std::cout << line__ << std::endl;

    std::cout << "[Средний балл: " << gpa_max << "]\n" << line__ << std::endl;
}