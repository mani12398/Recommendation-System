#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

void prod_of_array(int arr[], int brr[], int crr[], int size)
{
    int index;
    for (index = 0; index < size; index++)
    {
        crr[index] = arr[index] * brr[index];
    }
}

int sum_of_array(int arr[], int size)
{
    int index;
    int sum = 0;
    for (index = 0; index < size; index++)
    {
        sum = sum + arr[index];
    }
    return sum;
}

float cosine_similarity(int arr[], int brr[], int size)
{
    float result;
    int crr[7];
    int drr[7];
    int err[7];
    prod_of_array(arr, brr, crr, size);
    int sum_1 = sum_of_array(crr, size);
    prod_of_array(arr, arr, drr, size);
    int sum_2 = sum_of_array(drr, size);
    prod_of_array(brr, brr, err, size);
    int sum_3 = sum_of_array(err, size);
    float c = sqrt(sum_2) * sqrt(sum_3);
    result = sum_1 / c;
    return result;
}

void get_a_row_for_user_similarity(float ratings[][7], int arr[], int row)
{
    for (int index = 0; index < 7; index++)
    {
        arr[index] = ratings[row][index];
    }
}

void get_a_col_for_item_similarity(float ratings[][7], int arr[], int col)
{
    for (int index = 0; index < 6; index++)
    {
        arr[index] = ratings[index][col];
    }
}

void find_user_similarity(float ratings[][7], float user_similarity[][6])
{
    int arr[10], brr[10];
    for (int index = 0; index < 6; index++)
    {
        get_a_row_for_user_similarity(ratings, arr, index);
        for (int index_1 = 0; index_1 < 6; index_1++)
        {
            get_a_row_for_user_similarity(ratings, brr, index_1);
            user_similarity[index][index_1] = cosine_similarity(arr, brr, 7);
        }
    }
}

void find_item_similarity(float ratings[][7], float item_similarity[][7])
{
    int arr[10], brr[10];
    for (int index = 0; index < 7; index++)
    {
        get_a_col_for_item_similarity(ratings, arr, index);
        for (int index1 = 0; index1 < 7; index1++)
        {
            get_a_col_for_item_similarity(ratings, brr, index1);
            item_similarity[index][index1] = cosine_similarity(arr, brr, 6);
        }
    }
}

int first_maximum_of_user_and_item_similarity(float ratings[], int same_index, int size)
{

    float firstmaximum = -1;
    int location = 0;
    for (int index = 0; index < size; index++)
    {
        if (index != same_index && firstmaximum < ratings[index])
        {
            firstmaximum = ratings[index];
            location = index;
        }
    }
    return location;
}

int second_maximum_of_user_and_item_similarity(float ratings[], int first_maximum, int same_index, int size)
{
    float secondmaximum = -1;
    int location = 0;
    for (int index = 0; index < size; index++)
    {
        if (index != same_index && index != first_maximum && secondmaximum < ratings[index])
        {
            secondmaximum = ratings[index];
            location = index;
        }
    }
    return location;
}

void find_first_maximum_and_second_maximum_index_user_similarity(float user_similarity[][6], int order_of_user_similarity[6][2])
{
    int firstmaximum, secondmaximum;
    for (int index = 0; index < 6; index++)
    {
        firstmaximum = first_maximum_of_user_and_item_similarity(user_similarity[index], index, 6);
        order_of_user_similarity[index][0] = firstmaximum;
        secondmaximum = second_maximum_of_user_and_item_similarity(user_similarity[index], firstmaximum, index, 6);
        order_of_user_similarity[index][1] = secondmaximum;
    }
}

void find_first_maximum_and_second_maximum_index_item_similarity(float item_similarity[][7], int order_of_item_similarity[7][2])
{
    int firstmaximum, secondmaximum;
    for (int index = 0; index < 7; index++)
    {
        firstmaximum = first_maximum_of_user_and_item_similarity(item_similarity[index], index, 7);
        order_of_item_similarity[index][0] = firstmaximum;
        secondmaximum = second_maximum_of_user_and_item_similarity(item_similarity[index], firstmaximum, index, 7);
        order_of_item_similarity[index][1] = secondmaximum;
    }
}

void print_user_similarity(float user_similarity[][6])
{
    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << endl;

    SetConsoleTextAttribute(colour, 3);

    cout << "\n\t-----------------------------------------" << endl << endl;

    SetConsoleTextAttribute(colour, 6);

    cout << "\n\tUser to User Similarities: " << endl;
    cout << "\n";

    SetConsoleTextAttribute(colour, 10);

    for (int index = 0; index < 6; index++)
    {
        cout << "\n\t";
        for (int index_1 = 0; index_1 < 6; index_1++)
        {
            cout << user_similarity[index][index_1] << "   ";
        }
        cout << endl;
    }
}

void print_item_similarity(float item_similarity[][7])
{
    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << endl;

    SetConsoleTextAttribute(colour, 3);

    cout << "\n\t-----------------------------------------" << endl << endl;

    SetConsoleTextAttribute(colour, 6);

    cout << "\n\tItem to Item Similarities: " << endl;
    cout << "\n";

    SetConsoleTextAttribute(colour, 10);

    for (int index = 0; index < 7; index++)
    {
        cout << "\n\t";
        for (int index_1 = 0; index_1 < 7; index_1++)
        {
            cout << item_similarity[index][index_1] << "   ";
        }
        cout << endl;
    }
}

void print_first_maximum_and_second_maximum_index_user_similarity(int order_of_user_similarity[][2])
{
    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(colour, 6);

    cout << endl;
    cout << "\n\tFirst & Second Maximum of Every User: " << endl;
    cout << "\n";

    SetConsoleTextAttribute(colour, 10);

    for (int index = 0; index < 6; index++)
    {
        cout << "\n\t";
        for (int index_1 = 0; index_1 < 2; index_1++)
        {
            cout << order_of_user_similarity[index][index_1] << "  ";
        }
        cout << endl;
    }
}

void print_first_maximum_and_second_maximum_index_item_similarity(int order_of_item_similarity[][2])
{
    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << endl;

    SetConsoleTextAttribute(colour, 6);

    cout << "\n\tFirst & Second Maximum of Every Item: " << endl;
    cout << "\n";

    SetConsoleTextAttribute(colour, 10);

    for (int index = 0; index < 7; index++)
    {
        cout << "\n\t";
        for (int index_1 = 0; index_1 < 2; index_1++)
        {
            cout << order_of_item_similarity[index][index_1] << "  ";
        }
        cout << endl;
    }
}

void collaborative_filtering(float ratings[][7], int row, int order_of_item_similarity[][2])
{

    for (int index = 0; index < 7; index++)
    {

        if (ratings[row][index] == 0)
        {

            ratings[row][index] = (ratings[row][order_of_item_similarity[index][0]] + ratings[row][order_of_item_similarity[index][1]]) / 2;

        }

    }
}

void print_original_ratings(float original_ratings[][7])
{
    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(colour, 6);

    cout << "\n\n\tOriginal Ratings Matrix: " << endl << endl;
    cout << endl;

    SetConsoleTextAttribute(colour, 10);

    for (int index = 0; index < 6; index++)
    {
        cout << "\t";
        for (int index_1 = 0; index_1 < 7; index_1++)
        {

            cout << original_ratings[index][index_1] << "  ";


        }

        cout << endl;

    }

}

void print_ratings_result(float ratings[][7])
{

    for (int index = 0; index < 6; index++)
    {
        cout << "\t";
        for (int index_1 = 0; index_1 < 7; index_1++)
        {

            cout << ratings[index][index_1] << "  ";


        }

        cout << endl;

    }

}

void Setup()
{

    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colour, 3);

    cout << endl << endl;
    cout << "\t\t\t\t\tWelcome To PT Recommendation System Project" << endl << endl;
    cout << "\n\n\tFALL-2020 BSCS" << endl;
    cout << "\tSECTION B" << endl;
    cout << "\tGroup 2" << endl << endl;
    cout << "\tGroup Members: " << endl << endl;
    cout << "\tMuhammad Abdur-Rehman-022" << endl;
    cout << "\tMuhammad Ammar Zaid-014" << endl;
    cout << "\tMohammad Ali-052" << endl << endl << endl;


    cout << "\t";
    system("PAUSE");
    system("cls");

}


int main()
{
    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

    float original_ratings[6][7] =
    {

                          { 2, 2, 5, 5, 2, 2, 5 },
                          { 5, 5, 5, 1, 5, 1, 2 },
                          { 2, 2, 3, 5, 2, 2, 5 },
                          { 4, 5, 5, 5, 5, 5, 2 },
                          { 2, 5, 3, 2, 5, 2, 2 },
                          { 5, 1, 5, 5, 1, 5, 1 }
    };

    float ratings_result[6][7] =
    {
                          { 2, 0, 5, 0, 2, 0, 5 },
                          { 5, 5, 5, 1, 5, 1, 2 },
                          { 2, 2, 3, 5, 2, 2, 5 },
                          { 4, 5, 5, 5, 5, 5, 2 },
                          { 2, 5, 3, 2, 5, 2, 2 },
                          { 5, 1, 5, 5, 1, 5, 1 }
    };

    int row = 0;

    Setup();

    print_original_ratings(original_ratings);

    float user_similarity[6][6];
    float item_similarity[7][7];

    int order_of_user_similarity[6][2];
    int order_of_item_similarity[7][2];

    find_user_similarity(ratings_result, user_similarity);
    find_item_similarity(ratings_result, item_similarity);

    find_first_maximum_and_second_maximum_index_user_similarity(user_similarity, order_of_user_similarity);
    find_first_maximum_and_second_maximum_index_item_similarity(item_similarity, order_of_item_similarity);

    print_user_similarity(user_similarity);
    print_first_maximum_and_second_maximum_index_user_similarity(order_of_user_similarity);

    print_item_similarity(item_similarity);
    print_first_maximum_and_second_maximum_index_item_similarity(order_of_item_similarity);

    cout << endl;

    SetConsoleTextAttribute(colour, 3);

    cout << "\n\t-----------------------------------------" << endl << endl;

    SetConsoleTextAttribute(colour, 6);

    cout << "\n\tCosider 0 As User Gives No Rating to Specific Item: " << endl << endl;
    cout << endl;

    SetConsoleTextAttribute(colour, 4);

    print_ratings_result(ratings_result);

    collaborative_filtering(ratings_result, row, order_of_item_similarity);

    SetConsoleTextAttribute(colour, 3);

    cout << "\n\t-----------------------------------------" << endl << endl;

    SetConsoleTextAttribute(colour, 6);

    cout << "\n\tBy Using Item Based Collaborative Filtering We can Find the Missing Ratings of User 0: " << endl << endl;
    cout << endl;

    SetConsoleTextAttribute(colour, 10);

    print_ratings_result(ratings_result);

    cout << endl << endl;

    SetConsoleTextAttribute(colour, 3);

}