#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
    @returns void
 *   @param const int width
 *   @param const int height
 *   @param int array
 *
 * @note
 * Prints '\\n' in the end.
 */
void print2dArray(const int height, const int width, int array[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void populate2dArray(const int height, const int width, int array[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            array[i][j] = rand() % 100;
        }
    }
}


/**
 *
 \n Отражение матрицы по вертикали
 *   @returns void
 *   @param const int width
 *   @param const int height
 *   @param int array
 *
 */
void flipVertical2dArray(const int height, const int width, int array[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {

            // для вертикального отзеркаливания необходима только половина ширины массива

            // формула arr[i][width - j - 1] берёт элемент, зеркальный по вертикали
            // элементу arr[i][j]

            int temp = array[i][j];
            array[i][j] = array[i][width - j - 1];
            array[i][width - j - 1] = temp;
        }
    }
}

/**
 *
 \n Отражение матрицы по горизонтали
 *
 *   @returns void
 *   @param const int width
 *   @param const int height
 *   @param int array
 *
 */
void flipHorizontal2dArray(const int height, const int width, int array[height][width]) {

    // для горизонтального отзеркаливания необходима только половина длинны массива

    for (int i = 0; i < height / 2; i++) {
        for (int j = 0; j < width; j++) {

            int temp = array[i][j];

            // формула arr[h - i - 1][j] берёт элемент, зеркальный по горизонтали
           // элементу arr[i][j]
            array[i][j] = array[height - i - 1][j];

            // flip
            array[height - i - 1][j] = temp;
        }
    }
}


/**
 *
 * @param &height
 * @param &width
 * @param int array
 *
 @note
 * This function switches height and width
 * so when it's done,
 * height = width, and
 * width = height
 @Transposition_example
 *
 \n         1 2 3 4 => 1 4 7
 \n         4 5 6 0 => 2 5 8
 \n         7 8 9 1 => 3 6 9
 \n     ---------   => 4 0 1

 */
void transpose2dArray(int *height, int *width, int array[*height][*width]) {

    // временный массив. Костыль, но по-другому не получилось..
    int tempArr[*width][*height];

    // заполнение временного массива данными из переданного в функцию массива.
    // но с отзеркальенными данными, где array[1][2] будет tempArr[2][1].

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            tempArr[j][i] = array[i][j];
        }
    }

    // замена одного массива другим.

    memcpy(array, tempArr, sizeof(tempArr));

    // замена height на width, и наоборот
    int temp = *height;
    *height = *width;
    *width = temp;
}

/**
 *
 * @param &height
 * @param &width
 * @param int array
 * @param int howManyTimes
 *
 @note
 * This function may switch height and width places
 * when rotation is either 90 deg or -90 deg; \n
 * So when it's done:
 \n  height = width
 \n  width = height.

 */
void rotate90(int *height, int *width, int array[*height][*width], int howManyTimes) {

    // берём остаток от деления на 4
    howManyTimes %= 4;

    if (howManyTimes == 0) return;

    if (howManyTimes == 2 || howManyTimes == -2) {
        // нет разницы во вращении на 180 или -180 градусов
        // всё что нужно сделать - отразить массив вертикально

        // 1 2 3    3 2 1
        // 4 5 6 => 6 5 4
        // 7 8 9    9 8 7

        // и горизонтально

        // 3 2 1    9 8 7
        // 6 5 4 => 6 5 4
        // 9 8 7    3 2 1

        // порядок не имеет значения.

        flipVertical2dArray(*height, *width, array);
        flipHorizontal2dArray(*height, *width, array);

    } else if (howManyTimes == 1 || howManyTimes == -3) {
        // если вращение на 90 градусов по часовой стрелке - необходимо транспонировать,

        // 1 2 3    1 4 7
        // 4 5 6 => 2 5 8
        // 7 8 9    3 6 9

        // и отразить массив по вертикали.

        // 1 4 7    7 4 1
        // 2 5 8 => 8 5 2
        // 3 6 9    9 6 3

        transpose2dArray(height, width, array);
        flipVertical2dArray(*height, *width, array);
    } else if (howManyTimes == 3 || howManyTimes == -1) {
        // если вращение на 270 градусов по часовой стрелке - необходимо транспонировать,

        // 1 2 3    1 4 7
        // 4 5 6 => 2 5 8
        // 7 8 9    3 6 9

        // и отразить массив по горизонтали.

        // 1 4 7    3 6 9
        // 2 5 8 => 2 5 8
        // 3 6 9    1 4 7

        transpose2dArray(height, width, array);
        flipHorizontal2dArray(*height, *width, array);
    }
}

int main() {


    // a) - программа принимает 2 параметра - height, width.
    int h = 3, w = 4;
    int arr[h][w];

    // б) - далее программа заполняет массив случайными числами от 0 до 99.
    printf("Заполнение массивa случайными числами от 0 до 99.\n");
    populate2dArray(h, w, arr);
    print2dArray(h,w,arr);

    // в) После данный массив последовательно передаётся как аргумент в
    //реализуемые функции

    /*
     * После каждого вызова функции выводить массив в консоль.
     * Следить за переполнением консоли данными
     *
    */

    // 1. Функция fliplr(A). Отражение матрицы по вертикали.

    printf("Отражение матрицы по вертикали.\n");
    flipVertical2dArray(h, w, arr);
    print2dArray(h, w, arr);

    //2. Функция transpose(A). Транспонирование матрицы.

    printf("Транспонирование матрицы.\n");
    transpose2dArray(&h, &w, arr);
    print2dArray(h, w, arr);

    // 3. rot90(A,k) – функция поворота матрицы на 90 k раз.
    // Если k отрицательное - поворот против часовой стрелки.

    printf("Функция поворота матрицы на 90 k раз.\n");

    printf("\nповорот на 90: 0 раз.\n");
    rotate90(&h, &w, arr, 0);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: 1 раз.\n");
    rotate90(&h, &w, arr, 1);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: 2 раза.\n");
    rotate90(&h, &w, arr, 2);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: 3 раза.\n");
    rotate90(&h, &w, arr, 3);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: 4 раза.\n");
    rotate90(&h, &w, arr, 3);
    print2dArray(h, w, arr);


    printf("\nповорот на 90: -1 раз.\n");
    rotate90(&h, &w, arr, 1);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: -2 раза.\n");
    rotate90(&h, &w, arr, 2);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: -3 раза.\n");
    rotate90(&h, &w, arr, 3);
    print2dArray(h, w, arr);

    printf("\nповорот на 90: -4 раза.\n");
    rotate90(&h, &w, arr, 3);
    print2dArray(h, w, arr);



    /*
     * Разработать 3 набора тестов, проверяющих корректность работы каждой
    функции, с выдачей результата в человеко-читаемом протокольном виде. Тесты
    должны:
    - покрыть все уловные ветвления в функциях, если они есть
    - выйти из каждого выхода функции
    - проверить работу функции при некорректных входных параметрах, то
    есть параметрах, выходящих за ограничения.

     */


    return 0;
}
