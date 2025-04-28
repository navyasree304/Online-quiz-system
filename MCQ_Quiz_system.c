
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_QUESTIONS 3
#define FILENAME_HIGHSCORE "highscore.txt"

typedef struct {
    char question[256];
    char options[4][100];
    char answer;
} MCQ;

void loadSampleQuestions(MCQ q[]) {
    // Question 1
    strcpy(q[0].question, "Which of the following is not a valid data type in C language?\n");
    strcpy(q[0].options[0], "A) int\n");
    strcpy(q[0].options[1], "B) float\n");
    strcpy(q[0].options[2], "C) real\n");
    strcpy(q[0].options[3], "D) char\n");
    q[0].answer = 'C';

    // Question 2
    strcpy(q[1].question, "Which operator is used to access the value at a specific memory address?\n");
    strcpy(q[1].options[0], "A) &\n");
    strcpy(q[1].options[1], "B) *\n");
    strcpy(q[1].options[2], "C) $\n");
    strcpy(q[1].options[3], "D) %\n");
    q[1].answer = 'B';

    // Question 3
    strcpy(q[2].question, "Which header file is required to use the printf and scanf functions in C?\n");
    strcpy(q[2].options[0], "A) stdlib.h\n");
    strcpy(q[2].options[1], "B) string.h\n");
    strcpy(q[2].options[2], "C) math.h\n");
    strcpy(q[2].options[3], "D) stdio.h\n");
    q[2].answer = 'D';
}

void saveHighScore(const char *name, int score) {
    FILE *fp = fopen(FILENAME_HIGHSCORE, "a");
    if (fp) {
        fprintf(fp, "%s %d\n", name, score);
        fclose(fp);
    }
}

void showHighScores() {
    char name[50];
    int score;
    FILE *fp = fopen(FILENAME_HIGHSCORE, "r");
    if (!fp) {
        printf("No high scores yet.\n");
        return;
    }
    printf("\n--- High Scores ---\n");
    while (fscanf(fp, "%s %d", name, &score) != EOF) {
        printf("%s - %d\n", name, score);
    }
    fclose(fp);
}

int main() {
    MCQ questions[MAX_QUESTIONS];
    char choice, name[50];
    int score = 0;
    int useTimer;

    loadSampleQuestions(questions);

    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enable timer? (1 = Yes / 0 = No): ");
    scanf("%d", &useTimer);
    getchar(); // consume newline

    time_t start = time(NULL);

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        printf("\nQ%d: %s", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++)
            printf("%s", questions[i].options[j]);

        printf("Your answer (A/B/C/D): ");
        scanf(" %c", &choice);

        if (toupper(choice) == questions[i].answer)
            score++;

        if (useTimer && difftime(time(NULL), start) > 60) {
            printf("\nTime's up!\n");
            break;
        }
    }

    printf("\nYour score: %d/%d\n", score, MAX_QUESTIONS);
    saveHighScore(name, score);
    showHighScores();

    return 0;
}
