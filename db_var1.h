#pragma once

#include <cstdint>  // для типа данных int16_t

// пространство имён Задачи "Создание базы данных" Вариант 1
namespace db_var1 {
    // константа Максимальный размер строки
    static const unsigned int str_size__ = 100;
    // константа Максимальный размер списка студентов учебной группы
    static const unsigned int s_g_l_size__ = 100;
    // константа Линия
    static const char* line__ = "----------------------------";

    // структура данных Оценки по предметам
    struct Grades {
        int16_t maths_ = 0;         // математика           // используем минимальные контейнеры *без плотной упаковки
        int16_t geometry_ = 0;      // геометрия            // не используем int8_t, чтобы число не итерпретировалось как код ASCII
        int16_t phys_сult_ = 0;     // физическая культура  // *это не обязательно, просто сэкономили пару байт
        int16_t programming_ = 0;   // программирование
        int16_t history_ = 0;       // история
    };

    // структура данных Студент
    struct Student {
        char name_[str_size__];        // имя
        char surname_[str_size__];     // фамилия
        char patronymic_[str_size__];  // отчество
        char group_[str_size__];       // группа
        int16_t course_ = 0;           // курс
        Grades grades_;                // оценки по предметам
    };

    // класс Программа "Список учебной группы"
    class StudyGroupList {
    public:
        // Запуск программы
        void Start();

    private:
        Student students_[s_g_l_size__];    // массив списка студентов
        int ind_next_ = 0;                  // индекс первого пустого элемента списка

        // Меню программы
        void Menu();

        // Добавить студента в список
        void Add(int index);
        // Изменить запись в списке
        void ChangeEntry();
        // Удалить запись из списка
        void DeleteEntry();
        // Вывести весь список
        bool PrintAll();
        // Вывести запись по отдельному студенту
        void PrintStudent();
        // Сортировка списка по возрастанию курса
        void SortList();
        // Сохранить базу данных в файл
        void SaveToFile();
        // Загрузить базу данных из файла
        void LoadFromFile();
        // Создать бинарный файл базы данных из текстового
        void CreateBinaryFile();
        // Загрузить базу данных из бинарного файла
        void LoadFromBinaryFile();
        // Вывести запись о студенте, имеющем максимальный средний балл
        void PrintMostSuccessfulStudent();

        // Вывести одиночную запись из таблицы
        void PrintOne(int id, int ind_max_size, int name_max_size, int group_max_size);
        // Подсчитать число строк в файле
        int CountLinesInFile();
    };

} // namespace bd_var1