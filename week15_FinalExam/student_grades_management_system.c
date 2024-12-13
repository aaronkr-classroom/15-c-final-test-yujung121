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
        printf(".dat 파일을 열 수 없습니다.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("데이터를 성공적으로 읽었습니다.\n");
}

void writeToFile() {
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf(".dat 파일을 열 수 없습니다.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("데이터를 성공적으로 저장했습니다.\n");
}

void addStudent() {
    if (student_count >= 100) {
        printf("더 이상 학생 정보를 추가할 수 없습니다.\n");
        return;
    }

    Student new_student;

    printf("학생 이름: ");
    scanf_s("%s", new_student.name, (unsigned)_countof(new_student.name));
    printf("국어 점수: ");
    scanf_s("%d", &new_student.korean);
    printf("영어 점수: ");
    scanf_s("%d", &new_student.english);
    printf("수학 점수: ");
    scanf_s("%d", &new_student.math);

    new_student.total = new_student.korean + new_student.english + new_student.math;
    new_student.average = (float)new_student.total / 3;

    students[student_count] = new_student;
    student_count++;

    printf("학생 정보를 추가했습니다.\n");
}

void displayStudents() {
    printf("이름\t국어\t영어\t수학\t총점\t평균\n");
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
        printf("[Menu]\n1. .dat 파일에서 데이터 읽기\n2. 추가 학생 정보 입력\n3. .dat 파일 저장\n4. 성적 확인 (평균 계산 등)\n5. 종료\n-------------------\n선택(1~5): ");
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
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
