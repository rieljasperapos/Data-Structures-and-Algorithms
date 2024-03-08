#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
  char FN[20];
  char LN[20];
  char MI;
} NameType;

typedef struct {
  NameType name;
  char ID[10];
  char program[8];
  int year;
  char department[8];
} studRec;

typedef struct arr {
  studRec student[MAX];
  int count; // the actual # of elements in the list
} arrList;

typedef struct node {
  studRec student;
  struct node *link;
} *LList;


void readFile();
void writeFile(arrList studArr);
void insertStudent(arrList *studArr, studRec stud);
void displayArrList(arrList studArr);
void initArrList(arrList *studArr);

int main() {
  arrList S;
  initArrList(&S);
  studRec stud1 = {{"Riel", "Apos", 'A'}, "22105020", "BSCS", 2, "DCISM"};
  studRec stud2 = {{"John", "Ectarcio", 'A'}, "12345678", "BSCS", 2, "DCISM"};
  studRec stud3 = {{"Prince", "Tennis", 'A'}, "16821623", "BSCS", 2, "DCISM"};
  studRec stud4 = {{"Arima", "Kana", 'A'}, "18273610", "BSCS", 2, "DCISM"};
  studRec stud5 = {{"Jay", "Doe", 'A'}, "91825927", "BSCS", 2, "DCISM"};
  studRec stud6 = {{"Peanut", "Butter", 'A'}, "46112920", "BSCS", 2, "DCISM"};
  insertStudent(&S, stud1);
  insertStudent(&S, stud2);
  insertStudent(&S, stud3);
  insertStudent(&S, stud4);
  insertStudent(&S, stud5);
  insertStudent(&S, stud6);

  // displayArrList(S);
  writeFile(S);
  readFile();

}

void initArrList(arrList *studArr) {
  int indx;
  for (indx = 0; indx < MAX; indx++) {
    strcpy(studArr->student[indx].ID, "EMPTY");
  }
  studArr->count = 0;
}

void insertStudent(arrList *studArr, studRec stud) {
  if (studArr->count != MAX) {
    studArr->student[studArr->count++] = stud;
  }
}

void displayArrList(arrList studArr) {
  int indx;
  for (indx = 0; indx < studArr.count; indx++) {
    printf("\n%s, %s, %s", studArr.student[indx].name.LN, studArr.student[indx].name.FN, studArr.student[indx].ID);
  }
}

void writeFile(arrList studArr) {
  FILE *fp;
  fp = fopen("studentrec.txt", "wb");
  if (fp != NULL) {
    fwrite(studArr.student, sizeof(studRec), studArr.count, fp);
  }

  fclose(fp);
}

void readFile() {
  FILE *fp;
  studRec stud;
  fp = fopen("studentrec.txt", "rb");
  if (fp != NULL) {
    printf("READING FROM FILE\n");
    while (fread(&stud, sizeof(studRec), 1, fp)) {
      printf("%s, %s, %s - %s\n", stud.name.LN, stud.name.FN, stud.ID, stud.program);
    }
  }
}
