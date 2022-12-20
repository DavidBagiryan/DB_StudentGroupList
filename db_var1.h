#pragma once

#include <cstdint>  // ��� ���� ������ int16_t

// ������������ ��� ������ "�������� ���� ������" ������� 1
namespace db_var1 {
    // ��������� ������������ ������ ������
    static const unsigned int str_size__ = 100;
    // ��������� ������������ ������ ������ ��������� ������� ������
    static const unsigned int s_g_l_size__ = 100;
    // ��������� �����
    static const char* line__ = "----------------------------";

    // ��������� ������ ������ �� ���������
    struct Grades {
        int16_t maths_ = 0;         // ����������           // ���������� ����������� ���������� *��� ������� ��������
        int16_t geometry_ = 0;      // ���������            // �� ���������� int8_t, ����� ����� �� ����������������� ��� ��� ASCII
        int16_t phys_�ult_ = 0;     // ���������� ��������  // *��� �� �����������, ������ ���������� ���� ����
        int16_t programming_ = 0;   // ����������������
        int16_t history_ = 0;       // �������
    };

    // ��������� ������ �������
    struct Student {
        char name_[str_size__];        // ���
        char surname_[str_size__];     // �������
        char patronymic_[str_size__];  // ��������
        char group_[str_size__];       // ������
        int16_t course_ = 0;           // ����
        Grades grades_;                // ������ �� ���������
    };

    // ����� ��������� "������ ������� ������"
    class StudyGroupList {
    public:
        // ������ ���������
        void Start();

    private:
        Student students_[s_g_l_size__];    // ������ ������ ���������
        int ind_next_ = 0;                  // ������ ������� ������� �������� ������

        // ���� ���������
        void Menu();

        // �������� �������� � ������
        void Add(int index);
        // �������� ������ � ������
        void ChangeEntry();
        // ������� ������ �� ������
        void DeleteEntry();
        // ������� ���� ������
        bool PrintAll();
        // ������� ������ �� ���������� ��������
        void PrintStudent();
        // ���������� ������ �� ����������� �����
        void SortList();
        // ��������� ���� ������ � ����
        void SaveToFile();
        // ��������� ���� ������ �� �����
        void LoadFromFile();
        // ������� �������� ���� ���� ������ �� ����������
        void CreateBinaryFile();
        // ��������� ���� ������ �� ��������� �����
        void LoadFromBinaryFile();
        // ������� ������ � ��������, ������� ������������ ������� ����
        void PrintMostSuccessfulStudent();

        // ������� ��������� ������ �� �������
        void PrintOne(int id, int ind_max_size, int name_max_size, int group_max_size);
        // ���������� ����� ����� � �����
        int CountLinesInFile();
    };

} // namespace bd_var1