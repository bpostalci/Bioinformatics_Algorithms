/**
 * @description   score matrix utilities
 * @author        Berat Postalcioglu - 21401769 
 **/

#pragma once

#define GET_NUM(ch) (ch == 'A' ? 0 : ch == 'C' ? 1 : ch == 'G' ? 2 : ch == 'T' ? 3 : 0)

struct score_item
{
  int score;
  char pos;
};

const int score_matrix[4][4] =
    //  a   c   g   t
    {{2, -3, -3, -3},  // a
     {-3, 2, -3, -3},  // c
     {-3, -3, 2, -3},  // g
     {-3, -3, -3, 2}}; // t


     
// void write_alignment(char *s1, char *s2, char *title1, char *title2, int score, const char *filename)
// {
//     FILE *fp = NULL;
//     fp = fopen(filename, "w");

//     if (fp == NULL)
//     {
//         printf("output file '%s' cannot be opened. exiting...\n", filename);
//         exit(1);
//     }

//     printf("output file => %s\n", filename);

//     u32 partition_len = 60;
//     u32 str_len = strlen(s1); // we assume two strings have equal size
//     u32 title1_len = strlen(title1);
//     u32 title2_len = strlen(title2);

//     u32 limit = (str_len / partition_len) + 1;
//     limit = str_len % partition_len == 0 ? limit - 1 : limit;

//     fprintf(fp, "Score = %d\n\n", score);

//     // calculate space after titles
//     u32 space = 5;
//     u32 title1_space, title2_space;
//     if (title1_len > title2_len)
//     {
//         title1_space = space;
//         title2_space = (title1_len - title2_len) + space;
//     }
//     else
//     {
//         title2_space = space;
//         title1_space = (title2_len - title1_len) + space;
//     }

//     u32 i, j;
//     for (i = 0; i < limit; i++)
//     {
//         u32 current_limit = (str_len > (i + 1) * partition_len ? (i + 1) * partition_len : str_len);
//         for (j = 0; j < title1_len; j++)
//         {
//             fprintf(fp, "%c", title1[j]);
//         }
//         for (j = 0; j < title1_space; j++)
//         {
//             fprintf(fp, " ");
//         }
//         for (j = i * partition_len; j < current_limit; j++)
//         {
//             fprintf(fp, "%c", s1[j]);
//         }
//         fprintf(fp, "\n");

//         for (j = 0; j < title2_len; j++)
//         {
//             fprintf(fp, "%c", title2[j]);
//         }
//         for (j = 0; j < title2_space; j++)
//         {
//             fprintf(fp, " ");
//         }
//         for (j = i * partition_len; j < current_limit; j++)
//         {
//             fprintf(fp, "%c", s2[j]);
//         }
//         fprintf(fp, "\n\n");
//     }

//     fclose(fp);
// }

// void output_result(score_item **matrix, u32 row, u32 col, char *s1, char *s2, const char *filename)
// {
//     string str;
//     str.reserve(row + col); // eliminate heap allocation overhead
//     stringstream s1_stream(str);
//     stringstream s2_stream(str);
//     u32 i = row;
//     u32 j = col;

//     while (i > 0 || j > 0)
//     {
//         if (matrix[i][j].pos == '-') // we reached the edge
//         {
//             while (j > 0)
//             {
//                 s1_stream << '-';
//                 s2_stream << s2[j--];
//             }
//             while (i > 0)
//             {
//                 s2_stream << '-';
//                 s1_stream << s1[i--];
//             }
//             break;
//         }

//         switch (matrix[i][j].pos)
//         {
//         case 'd':
//             s1_stream << s1[i - 1];
//             s2_stream << s2[j - 1];
//             --i;
//             --j;
//             break;
//         case 'u':
//             s1_stream << s1[--i];
//             s2_stream << '-';
//             break;
//         case 'l':
//             s1_stream << '-';
//             s2_stream << s2[--j];
//             break;
//         }
//     }

//     string title1_str = string(">title1").erase(0, 1);
//     string title2_str = string(">title2").erase(0, 1);

//     string s1_str = s1_stream.str();
//     reverse(s1_str.begin(), s1_str.end());
//     string s2_str = s2_stream.str();
//     reverse(s2_str.begin(), s2_str.end());

//     write_alignment((char *)s1_str.c_str(), (char *)s2_str.c_str(), (char *)title1_str.c_str(), (char *)title2_str.c_str(), matrix[row][col].score, filename);
// }