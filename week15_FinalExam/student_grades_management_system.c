#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[12];
    int korean;
    int english;
    int math;
    int total;
    float average;
    int rank;
} Student;

Student students[100];
int student_count = 0;

void readFromFile() {
    FILE* file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf(".dat ������ �� �� �����ϴ�.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("�����͸� ���������� �о����ϴ�.\n");
}

void writeToFile() {
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf(".dat ������ �� �� �����ϴ�.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("�����͸� ���������� �����߽��ϴ�.\n");
}

void addStudent() {
    if (student_count >= 100) {
        printf("�� �̻� �л� ������ �߰��� �� �����ϴ�.\n");
        return;
    }

    Student new_student;

    printf("�л� �̸�: ");
    scanf_s("%s", new_student.name, (unsigned)_countof(new_student.name));
    printf("���� ����: ");
    scanf_s("%d", &new_student.korean);
    printf("���� ����: ");
    scanf_s("%d", &new_student.english);
    printf("���� ����: ");
    scanf_s("%d", &new_student.math);

    new_student.total = new_student.korean + new_student.english + new_student.math;
    new_student.average = (float)new_student.total / 3;

    students[student_count] = new_student;
    student_count++;

    printf("�л� ������ �߰��߽��ϴ�.\n");
}

void displayStudents() {
    printf("�̸�\t����\t����\t����\t����\t���\n");
    for (int i = 0; i < student_count; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%.2f\n",
            students[i].name, students[i].korean, students[i].english, students[i].math,
            students[i].total, students[i].average);
    }
}

void rankStudents() {
    for (int i = 0; i < student_count; i++) {
        students[i].rank = 1;
        for (int j = 0; j < student_count; j++) {
            if (students[i].total < students[j].total) {
                students[i].rank++;
            }
        }
    }
}

void menu() {
    int choice;
    while (1) {
        printf("[Menu]\n1. .dat ���Ͽ��� ������ �б�\n2. �߰� �л� ���� �Է�\n3. .dat ���� ����\n4. ���� Ȯ�� (��� ��� ��)\n5. ����\n-------------------\n����(1~5): ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            readFromFile();
            break;
        case 2:
            addStudent();
            rankStudents();
            break;
        case 3:
            writeToFile();
            break;
        case 4:
            displayStudents();
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
