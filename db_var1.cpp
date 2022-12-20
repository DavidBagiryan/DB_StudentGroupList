#include "db_var1.h"

#pragma warning(disable : 4996) // ���������� �������������� � Visual Studio

#include <iostream> // ��� ������ �����/������
#include <iomanip>  // ��� ������� ������������ ������ �������
#include <fstream>  // ��� ������ � �������

using namespace db_var1;

// ������� ���������� ��������� ������ � ������
template<typename size_t N>             // ��� ��������������� ���������� �������
void AddStr(char(&str)[N]) {
    std::cin.getline(str, str_size__);  // getline ��� ������ ���� ������ � ���������
    if (std::cin.fail()) {              // ��� ������������ ������ ���������� �� ������������ �������
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// ������ ���������
void StudyGroupList::Start() {
	std::cout << "[��������� \"������ ������� ������\" ��������.]" << std::endl;
	Menu();
}

// ���� ���������
void StudyGroupList::Menu() {
	while (true) {
        std::cout << 
            line__ << '\n' <<
            "1\t- �������� �������\n" <<
            "2\t- �������� ������\n" <<
            "3\t- ������� ������\n" <<
            "4\t- ������� ������ ��������\n" <<
            "5\t- ������� ������������� �������\n" <<
            "6\t- ����������� �������� �� �����\n" <<
            "7\t- ��������� �� � ����\n" <<
            "8\t- ��������� �� �� �����\n" <<
            "9\t- ������� ����� � ��������\n" <<
            "10\t- ��������� �� �� ��������� �����\n" <<
            "11\t- ����������� �������� ������ ��������, �������� ������������ ������� ����\n" << 
            "0\t- �����\n" <<
            line__ << std::endl;

        char command[2] = { -1, -1};
        // �������� �� ���� ����
        while (true) {
            std::cin.get(command[0]); if (command[0] == '\n') continue;

            if (!(command[0] >= 48 && command[0] <= 57)) { // ��� ASCII 48 = '0', ��� ASCII 57 = '9'
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� max 2 �������, ��������� ����������
            break;
        }

        int ch = atoi(command); // �������� �����
        switch (ch) {
        case 1:
        {
            Add(ind_next_);
            ++ind_next_;        // ��������� ������

            std::cout << line__ <<
                "\n[������� " <<
                students_[ind_next_ - 1].surname_ << " " <<
                students_[ind_next_ - 1].name_ << " " <<
                students_[ind_next_ - 1].patronymic_ << " " <<
                "�������� � ������.]" << std::endl;
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
            std::cout << "[��������� \"������ ������� ������\" �������.]" << std::endl;
            return;
        default:
            break;
        }
	}
}

// �������� �������� � ������
void StudyGroupList::Add(int index) {
    std::cout << "������� ���: ";
    AddStr(students_[index].name_);
    std::cout << "\n������� �������: ";
    AddStr(students_[index].surname_);
    std::cout << "\n������� ��������: ";
    AddStr(students_[index].patronymic_);
    std::cout << "\n������� ������: ";
    AddStr(students_[index].group_);
    std::cout << "\n������� ����: ";
    std::cin >> students_[index].course_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������� ������ ������, ��������� ����������
    std::cout << "\n������� ������ �� ����������������: ";
    std::cin >> students_[index].grades_.programming_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n������� ������ �� �������: ";
    std::cin >> students_[index].grades_.history_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n������� ������ �� ���������� ��������: ";
    std::cin >> students_[index].grades_.phys_�ult_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n������� ������ �� ���������: ";
    std::cin >> students_[index].grades_.geometry_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n������� ������ �� ����������: ";
    std::cin >> students_[index].grades_.maths_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// �������� ������ � ������
void StudyGroupList::ChangeEntry() {
    if (!PrintAll()) return;

    std::cout << "[������� id ��������������� ������ ��� ��������������.]" << std::endl;

    int tmp = 0;
    std::cin >> tmp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tmp < 0 || tmp >= ind_next_) {
        std::cout << "[����� ������ ���!]\n" << line__ << std::endl;;
        return;
    }

    Add(tmp); // ��������������
}

// ������� ������ �� ������
void StudyGroupList::DeleteEntry() {
    if (!PrintAll()) return;
    
    std::cout << "[������� id ��������������� ������ ��� ��������.]" << std::endl;

    int tmp = 0;
    std::cin >> tmp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tmp < 0 || tmp >= ind_next_) {
        std::cout << "����� ������ ���\n";
        return;
    }

    for (int i = tmp; i < ind_next_; ++i)   // "�������" ������ ��������� ������ � �������
    {
        students_[i] = students_[i + 1];
    }
    --ind_next_;                            // ��������� ������

    std::cout << "[������ ������� �������.]" << std::endl;
}

// ������� ���� ������
bool StudyGroupList::PrintAll() {
    if (ind_next_ == 0) {
        std::cout << "[������ ����!]" << std::endl;
        return false;   // ���������� ����, ��� ������ �� ����
    }

    // ��������� ������ �������� ��� �������
    int ind_s = 1;      
    ind_next_ > 9 ? ind_s = 2 : ind_s = 1;
    int name_max_s = 5;
    int group_max_s = 5;
    for (int i = 0; i < ind_next_; ++i) // ������� ������������ ����� ��� � ������ � �������,
    {                                   // �.�. ��� ������������ ����, ��� �������� ���� > 1 �������
        int width_name = strlen(students_[i].name_) + strlen(students_[i].surname_) + strlen(students_[i].patronymic_) + 2;
        if (name_max_s < width_name) name_max_s = width_name;
        int width_group = strlen(students_[i].group_) - 1;
        if (group_max_s < width_group) group_max_s = width_group;
    }

    int alignment_student = name_max_s + group_max_s + 7;   // ������ ������� � ����� �������
    if (alignment_student % 2 != 0) {
        ++alignment_student;
        ++name_max_s;
    }

    // ����� �������
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(alignment_student) << std::left << "�������" << '|' << std::right << std::setw(18) << "������" << std::setw(18) << '|' << '\n';
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(name_max_s) << std::left << "���" << '|' << std::setw(group_max_s + 1) << "������" << '|' << "����" << '|' << "���." << '|' << "����." << '|' << "���.�����." << '|' << "�������." << '|'  << "���." << '|' << '\n';
    // ������ � �������
    for (int i = 0; i < ind_next_; ++i) {
        PrintOne(i, ind_s, name_max_s, group_max_s);
    }
    std::cout << line__ << std::endl;
}

// ������� ��������� ������ �� �������
void StudyGroupList::PrintOne(int id, int ind_max_size, int name_max_size, int group_max_size) {
    char fio_buff[3 * str_size__ + 2] = {};         // ����� ��� �������� ������� ����� �������� � ����� ������; 2 - �������
    strcat_s(fio_buff, 3 * str_size__ + 2, students_[id].surname_);
    strcat_s(fio_buff, 3 * str_size__ + 2, " ");    // ��������� �������
    strcat_s(fio_buff, 3 * str_size__ + 2, students_[id].name_);
    strcat_s(fio_buff, 3 * str_size__ + 2, " ");
    strcat_s(fio_buff, 3 * str_size__ + 2, students_[id].patronymic_);
    std::cout << std::setw(ind_max_size) << id << '|' << std::setw(name_max_size) << std::left << fio_buff << '|' << std::setw(group_max_size + 1) << students_[id].group_ << '|' << std::setw(4) << students_[id].course_ << '|' << std::setw(4) << students_[id].grades_.maths_ << '|' << std::setw(5) << students_[id].grades_.geometry_ << '|' << std::setw(10) << students_[id].grades_.phys_�ult_ << '|' << std::setw(8) << students_[id].grades_.programming_ << '|' << std::setw(4) << students_[id].grades_.history_ << '|' << std::right << '\n';
}

// ������� ������ �� id
void StudyGroupList::PrintStudent() {
    if (!PrintAll()) return;

    std::cout << "[������� id ��������������� ������ ��� ������ ����������.]" << std::endl;

    int tmp = 0;
    std::cin >> tmp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tmp < 0 || tmp >= ind_next_) {
        std::cout << "[����� ������ ���!]\n";
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
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(alignment_student) << std::left << "�������" << '|' << std::right << std::setw(18) << "������" << std::setw(18) << '|' << '\n';
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(name_s) << std::left << "���" << '|' << std::setw(group_s + 1) << "������" << '|' << "����" << '|' << "���." << '|' << "����." << '|' << "���.�����." << '|' << "�������." << '|' << "���." << '|' << '\n';
    PrintOne(tmp, ind_s, name_s, group_s);
}

// ���������� ������ �� ����������� �����
void StudyGroupList::SortList() {
    // ����������� ����������
    Student temp;   // �����
    for (int i = 0; i < ind_next_ - 1; i++) {   // ������� ������� ���� �������� ����� ������ �������
        for (int j = i + 1; j < ind_next_; j++) // ����� ���������� �������� � ����
        {
            if (students_[i].course_ > students_[j].course_) {
                temp = students_[i];
                students_[i] = students_[j];
                students_[j] = temp;
            };
        }
    }
    std::cout << "[���������� ������ �� ����������� ������� ���������.]" << std::endl;
}

// ��������� ���� ������ � ����
void StudyGroupList::SaveToFile() {
    std::ofstream out("DB.txt", std::ios::app); // ���� app - ������ ������ � ����� �����, �������� ���
    if (!out.is_open()) {
        std::cout << "[���� �� ������� �������.]" << std::endl;
        return;
    }
    if (ind_next_ == 0) {
        std::cout << "[������ ����!]" << std::endl;
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
            students_[i].grades_.phys_�ult_ << '\n' <<
            students_[i].grades_.programming_ << '\n' <<
            students_[i].grades_.history_ << '\n';
    }
    out.close();
    std::cout << "[���� ������ � ����� DB.txt ������� ���������]" << std::endl;
}

// ��������� ���� ������ �� �����
void StudyGroupList::LoadFromFile() {
    int count_line = CountLinesInFile();
    if (count_line == 0) return;

    if (ind_next_ != 0) {   // ���������, ���� �� ������
        std::cout << "[�� ������ �������� ������ ����� ��������� ������ �� �����?]\n[1 - ��]" << std::endl;
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

    int count_student = count_line / 10;                                // ������� ���-�� �������� Student
    if (count_student > s_g_l_size__) count_student = s_g_l_size__;     // ���� ��������� � ���� ������ max ������� ������,
                                                                        // ����� ����������
    std::ifstream fin("DB.txt");
    if (!fin)
    {
        std::cout << "[��������� ���� �� ������� �������.]" << std::endl;
        return;
    }

    int ind_next = ind_next_;   // ����������, ������ ������ �� ���������� �������
    for (int i = ind_next; i < count_student + ind_next; i++) {
        fin.getline(students_[i].name_, str_size__);
        fin.getline(students_[i].surname_, str_size__);
        fin.getline(students_[i].patronymic_, str_size__);
        fin.getline(students_[i].group_, str_size__);
        fin >> students_[i].course_;
        fin >> students_[i].grades_.maths_;
        fin >> students_[i].grades_.geometry_;
        fin >> students_[i].grades_.phys_�ult_; 
        fin >> students_[i].grades_.programming_;
        fin >> students_[i].grades_.history_;
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ���������� ������ �������� ������
        ++ind_next_;                                                    // ��������� ������
    }
    fin.close();

    std::cout << "[���� ������ �� ���������� ����� ������� ���������.]" << std::endl;
}

// ���������� ����� ����� � �����
int StudyGroupList::CountLinesInFile() {
    auto* in = fopen("DB.txt", "a+t");  // ��������� ���� ��� ������-������, �������� ��������� �� ����
    int counter = 0;                    // ������������, ��� ����� ���� � ����� - �.�. ������
    if (in == NULL) {
        std::cout << "[��������� ���� �� ������� �������.]" << std::endl;
        return 0;
    }
    else {
        int ch, pre = EOF;              // ������� ������, ��������� �������� ������

        /* � ����� ������� ������� ��������� ������ � ����� � ���������� ��� � ���������� counter
         � ����� ������� �� ����� ������ �������� ������.
         ���� ���� ������, �� ���� ����� �� ���������� �� ����, ��� ��� ������ ��������� ������ ����� ��� ��� EOF
         � � pre ��������� EOF */
        while ((ch = fgetc(in)) != EOF) {   // � ����� �������� ���� ���� �����������
            pre = ch;                       // ���������� ��������� �������� ������
            if (ch == '\n') ++counter;      // ���� ����� ������� ������, �� ����������� ������� �����
        }
        fclose(in);

        /* ���� ����� ���������� pre � ���, ����� ��������� ����� ������ �� ������� ����� ��� ��� ���������� �� EOF � �����
         ��� � pre ����� EOF - ���� ���� ����� �� ���� �� �����������, ��� ����� ��� ������ �����
         ��������� ������ ����� ����� ������������� �� \n, � ������ ��������� ���� - ��� ��� ����� � ����� ���������� pre */

        if (pre == EOF) {   // ���� ���� ������
            std::cout << "[���� ������!]" << std::endl;
            return 0;
        }
        else if (pre != '\n') ++counter;   // ���� pre �������� � ���� �� ������� ������, � ���� �� ������, �� ����������� ������� �����
    }

    if (counter % 10 != 0) {    // �� 1 �������� 10 ����� ����������
        std::cout << "[������ � ����� �� ������!]";
        return 0;               // �������, ��� ���������� ������ ���������
    }
    return counter;
}

// ������� �������� ���� ���� ������ �� ����������
void StudyGroupList::CreateBinaryFile() {
    std::ofstream out("DB.bin", std::ios::binary | std::ios::out);
    if (!out.is_open()) {
        std::cout << "[�������� ���� �� ������� �������.]" << std::endl;
        return;
    }
    std::ifstream in("DB.txt");
    if (!in.is_open()) {
        std::cout << "[��������� ���� �� ������� �������.]" << std::endl;
        return;
    }

    int count_line = CountLinesInFile();    // ������� ����� ����� � ��������� �����
    if (count_line == 0) return;            // ����� ������� ����� ������, ��� ���������� ������ ���������

    Student students_from_file;             // ������ ��������� ���������, ��� ������ �� �����
    
    int count_student = count_line / 10;    // ������� ���-�� �������� Student
    for (int i = 0; i < count_student; i++) {
        in.getline(students_from_file.name_, str_size__);
        in.getline(students_from_file.surname_, str_size__);
        in.getline(students_from_file.patronymic_, str_size__);
        in.getline(students_from_file.group_, str_size__);
        in >> students_from_file.course_;
        in >> students_from_file.grades_.maths_;
        in >> students_from_file.grades_.geometry_;
        in >> students_from_file.grades_.phys_�ult_;
        in >> students_from_file.grades_.programming_;
        in >> students_from_file.grades_.history_;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');           // ���������� ������ �������� ������

        out.write((char*)&students_from_file, sizeof(students_from_file));      // ���������� ��������� Student � �������� ����
    }

    in.close();
    out.close();

    std::cout << "[���� ������ �� ���������� ����� ������� ��������� � �������� �����.]" << std::endl;
}

// ��������� ���� ������ �� ��������� �����
void StudyGroupList::LoadFromBinaryFile() {
    std::ifstream in("DB.bin", std::ios::binary | std::ios::in);
    if (!in.is_open()) {
        std::cout << "[�������� ���� �� ������� �������.]" << std::endl;
        return;
    }

    if (ind_next_ != 0) {   // ���������, ���� �� ������
        std::cout << "[�� ������ �������� ������ ����� ��������� ������ �� �����?]\n[1 - ��]" << std::endl;
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

    // ���������� ���������� �������� � �����
    in.seekg(0, in.end);                    // ���������� ��������� ������ � ����� �����
    unsigned int tripsCount = in.tellg();   // ���������� ������� ��������� � ����������, ��� ����� ���������� ���� � �����
    tripsCount /= sizeof(Student);          // ����� ����� ���������� ���� � ����� �� ���������� ���� ���������� ����� ����������
    in.seekg(0, in.beg);                    // ���������� ��������� ������ � ������ �����

    int ind_next = ind_next_;
    for (int i = ind_next; i < tripsCount + ind_next; i++) {
        in.read((char*)&students_[i], sizeof(students_[i]));
        ++ind_next_;
    }

    std::cout << "[���� ������ �� ��������� ����� ������� ���������.]" << std::endl;
}

// ������� ������ � ��������, ������� ������������ ������� ����
void StudyGroupList::PrintMostSuccessfulStudent() {
    int successful_student_id = 0;
    float gpa = 0, gpa_max = -1.0;
    for (int i = 0; i < ind_next_; i++) {
        gpa = (students_[i].grades_.maths_ + students_[i].grades_.geometry_
            + students_[i].grades_.phys_�ult_ + students_[i].grades_.programming_
            + students_[i].grades_.history_) / 5;
        if (gpa_max < gpa) {
            gpa_max = gpa;
            successful_student_id = i;
        }
    }

    // ��������� ������ �������� ��� �������
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

    std::cout << std::setw(ind_s + 1) << '|' << std::setw(alignment_student) << std::left << "�������" << '|' << std::right << std::setw(18) << "������" << std::setw(18) << '|' << '\n';
    std::cout << std::setw(ind_s + 1) << '|' << std::setw(name_max_s) << std::left << "���" << '|' << std::setw(group_max_s + 1) << "������" << '|' << "����" << '|' << "���." << '|' << "����." << '|' << "���.�����." << '|' << "�������." << '|' << "���." << '|' << '\n';
    PrintOne(successful_student_id, ind_s, name_max_s, group_max_s);
    std::cout << line__ << std::endl;

    std::cout << "[������� ����: " << gpa_max << "]\n" << line__ << std::endl;
}