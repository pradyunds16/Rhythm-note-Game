#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/* ---------- DELAY FUNCTION ---------- */
void sleep_ms(int ms)
{
    Sleep(ms);
}

/* ---------- MAIN FUNCTION ---------- */
int main()
{
    int totalBeats = 10;        // Total number of beats
    int beatInterval;           // Time gap between beats
    int hitWindow;              // Allowed reaction time window

    int score = 0;
    int combo = 0;
    int maxCombo = 0;
    int level;
    int i;

    clock_t startTime, endTime;
    double reactionTime;

    /* ---------- GAME INTRO ---------- */
    printf("====================================\n");
    printf("        CONSOLE RHYTHM GAME\n");
    printf("====================================\n");
    printf("Press SPACE when you hear the beep\n\n");

    /* ---------- DIFFICULTY SELECTION ---------- */
    printf("Select Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter choice: ");
    scanf("%d", &level);

    if (level == 1)
    {
        beatInterval = 1000;
        hitWindow = 250;
    }
    else if (level == 2)
    {
        beatInterval = 800;
        hitWindow = 180;
    }
    else
    {
        beatInterval = 600;
        hitWindow = 120;
    }

    printf("\nGet Ready...\n");
    sleep_ms(2000);

    /* ---------- RHYTHM LOOP ---------- */
    for (i = 1; i <= totalBeats; i++)
    {
        printf("\nBeat %d\n", i);
        sleep_ms(beatInterval);

        /* Audible beat */
        Beep(1000, 200);

        printf(">>> HIT NOW! <<<\n");

        startTime = clock();

        while (!kbhit()) {}
        getch();

        endTime = clock();

        /* ---------- TIME CALCULATION ---------- */
        reactionTime = (double)(endTime - startTime)
                       / CLOCKS_PER_SEC * 1000;

        /* ---------- SCORING ---------- */
        if (reactionTime <= hitWindow)
        {
            printf("Perfect! (%.0f ms)\n", reactionTime);
            score += 10 + combo;
            combo++;
        }
        else if (reactionTime <= hitWindow * 2)
        {
            printf("Good! (%.0f ms)\n", reactionTime);
            score += 5;
            combo++;
        }
        else
        {
            printf("Miss! (%.0f ms)\n", reactionTime);
            combo = 0;
        }

        if (combo > maxCombo)
            maxCombo = combo;
    }

    /* ---------- FINAL RESULT ---------- */
    printf("\n====================================\n");
    printf("            GAME OVER\n");
    printf("====================================\n");
    printf("Final Score : %d\n", score);
    printf("Max Combo   : %d\n", maxCombo);

    if (score >= 120)
        printf("Performance : Excellent Rhythm!\n");
    else if (score >= 80)
        printf("Performance : Good Timing!\n");
    else
        printf("Performance : Needs Practice\n");

    return 0;
}
