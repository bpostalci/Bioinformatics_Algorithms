#include "BurrowsWheelerTransform.h"
#include "Typedefs.h"
#include "FileHelper.h"
#include <string.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <sstream>

struct suffix;
char *generate_column(int *suffix_arr, char *text, uint_t text_len);
int *generate_suffix_array(char *text, uint_t text_len, char *first_column);
std::unordered_map<char, int> generate_count_map(char *bwt, uint_t bwt_len);
char *compress_bwt(char *bwt, uint_t bwt_len);
uint_t get_num_of_digits(int num);
void generate_rank_table(const char *pattern, const char *file_name, const char *extension);
void generate_occurence_table(const char *bwt, const char *file_name, const char *extension);

void transform(const char *pattern, const char *index_file)
{
    uint_t new_pattern_len = strlen(pattern) + 1;

    char *new_pat = (char *)malloc(sizeof(char) * new_pattern_len);
    strcpy(new_pat, pattern);
    new_pat[new_pattern_len - 1] = '$';
    new_pat[new_pattern_len] = '\0';

    char *first_column = (char *)malloc(sizeof(char) * (new_pattern_len + 2));
    int *suffix_arr = generate_suffix_array(new_pat, new_pattern_len, first_column);
    first_column[new_pattern_len + 1] = '\0';
    write_buffer_1d(first_column, index_file, ".fm", "a");

    char *bwt = generate_column(suffix_arr, new_pat, new_pattern_len);
    write_buffer_1d(bwt, index_file, ".bwt", "w");

    generate_occurence_table(bwt, index_file, ".fm");
    generate_rank_table(pattern, index_file, ".fm");

    char **suffix_str_arr = (char **)malloc(sizeof(char *) * (new_pattern_len + 1));
    for (uint_t i = 0; i < new_pattern_len; i++)
    {
        int nod = get_num_of_digits(suffix_arr[i]);
        suffix_str_arr[i] = (char *)malloc(sizeof(char) * (nod + 2));
        sprintf(suffix_str_arr[i], "%d", suffix_arr[i]);
        if (i != new_pattern_len - 1)
        {
            suffix_str_arr[i][nod] = ',';
            suffix_str_arr[i][nod + 1] = '\0';
        }
        else
        {
            suffix_str_arr[i][nod] = '\0';
        }
    }
    suffix_str_arr[new_pattern_len] = (char *)malloc(sizeof(char) * 2);
    strcpy(suffix_str_arr[new_pattern_len], "\n");
    write_buffer_2d(suffix_str_arr, new_pattern_len + 1, index_file, ".fm", "a");

    // free
    for (uint_t i = 0; i < new_pattern_len; i++)
    {
        free(suffix_str_arr[i]);
    }
    free(suffix_str_arr);

    std::unordered_map<char, int> occurence_map = generate_count_map(bwt, new_pattern_len);

    // write count table to file
    FILE *outfp = NULL;
    std::stringstream ss;
    ss << index_file << ".fm";
    outfp = fopen(ss.str().c_str(), "a");

    if (outfp == NULL)
    {
        printf("file cannot be opened...\n");
        exit(1);
    }

    std::unordered_map<char, int>::iterator it = occurence_map.begin();
    while (it != occurence_map.end())
    {
        fprintf(outfp, "%c%d", (*it).first, (*it).second);
        if ((++it) != occurence_map.end())
        {
            fprintf(outfp, ",");
        }
    }
    fprintf(outfp, "\n");
    fclose(outfp);
    // write count table to file

    // char *compressed_bwt = compress_bwt(bwt, new_pattern_len); // good for large texts and text should not contain any digits

    free(new_pat);
    free(suffix_arr);
    free(bwt);
    free(first_column);
}

struct suffix
{
public:
    char *suf; // suffix
    uint_t i;  // index
    suffix() : suf(NULL) {}
    suffix(char *_suf, uint_t _i) : suf(_suf), i(_i) {}
};

int cmp(const void *s1, const void *s2)
{
    return strcmp(((suffix *)s1)->suf, ((suffix *)s2)->suf);
}

int *generate_suffix_array(char *text, uint_t text_len, char *first_column)
{
    suffix suffix_arr[text_len];
    int *indexes = (int *)malloc(sizeof(int) * text_len);

    for (uint_t i = 0; i < text_len; i++)
    {
        suffix_arr[i].suf = (text + i);
        suffix_arr[i].i = i;
    }

    qsort(suffix_arr, text_len, sizeof(suffix), cmp);

    for (uint_t i = 0; i < text_len; i++)
    {
        first_column[i] = suffix_arr[i].suf[0]; // get first column
        indexes[i] = suffix_arr[i].i;
    }
    first_column[text_len] = '\n';

    return indexes;
}

char *generate_column(int *suffix_arr, char *text, uint_t text_len)
{
    char *bwt = (char *)malloc(sizeof(char) * text_len);
    for (uint_t i = 0; i < text_len; i++)
    {
        int j = suffix_arr[i] - 1;
        bwt[i] = text[(j < 0) ? (j + text_len) : j];
    }
    bwt[text_len] = '\0';

    return bwt;
}

std::unordered_map<char, int> generate_count_map(char *bwt, uint_t bwt_len)
{
    std::unordered_map<char, int> occurence_map;
    for (uint_t i = 0; i < bwt_len; i++)
    {
        if (occurence_map.find(bwt[i]) == occurence_map.end())
        {
            occurence_map.insert({bwt[i], 1});
        }
        else
        {
            ++occurence_map.at(bwt[i]);
        }
    }

    return occurence_map;
}

char *compress_bwt(char *bwt, uint_t bwt_len)
{
    std::stringstream buff;

    for (uint_t i = 0; i < bwt_len; i++)
    {
        uint_t j = i;
        uint_t cnt = 0;
        while (bwt[i] == bwt[j])
        {
            ++j;
            ++cnt;
        }
        i = j - 1; // undo last control
        buff << cnt << bwt[i];
    }

    uint_t buff_size = buff.str().length();
    char *compressed_bwt = (char *)malloc(sizeof(char) * buff_size);
    memcpy(compressed_bwt, buff.str().c_str(), sizeof(char) * buff_size);

    return compressed_bwt;
}

uint_t get_num_of_digits(int num)
{
    if (num == 0)
        return 1;
    uint_t cnt = 0;
    while (num != 0)
    {
        ++cnt;
        num /= 10;
    }
    return cnt;
}

void generate_rank_table(const char *pattern, const char *file_name, const char *extension)
{
    std::unordered_map<char, int> count_map;
    uint_t len = strlen(pattern);

    std::stringstream ss;
    ss << file_name << extension;

    FILE *fp = NULL;
    fp = fopen(ss.str().c_str(), "a");
    if (fp == NULL)
    {
        printf("file cannot be opened...\n");
        exit(1);
    }

    for (uint_t i = 0; i < len; i++)
    {
        if (count_map.find(pattern[i]) == count_map.end())
        {
            count_map.insert({pattern[i], i});
            fprintf(fp, "%c%d", pattern[i], i);
            fprintf(fp, ",");
        }
    }
    fseek(fp, -1L, SEEK_CUR); // undo last ","
    fprintf(fp, "\n");
    fclose(fp);
}

void generate_occurence_table(const char *bwt, const char *file_name, const char *extension)
{
    uint_t bwt_len = strlen(bwt);
    std::unordered_map<char, int *> table;
    for (uint_t i = 0; i < bwt_len; i++)
    {
        if (table.find(bwt[i]) == table.end())
        {
            int *list = (int *)calloc(bwt_len, sizeof(int));
            for (uint_t j = 0; j < bwt_len; j++)
            {
                if (bwt[i] == bwt[j])
                {
                    list[j] = (j > 0) ? list[j - 1] + 1 : 1;
                }
                else
                {
                    list[j] = (j > 0) ? list[j - 1] : list[j];
                }
            }
            table.insert({bwt[i], list});
        }
    }

    std::stringstream ss;
    ss << file_name << extension;

    FILE *fp = NULL;
    fp = fopen(ss.str().c_str(), "w");

    if (fp == NULL)
    {
        printf("file cannot be opened...\n");
        exit(1);
    }

    std::unordered_map<char, int *>::iterator it = table.begin();
    while (it != table.end())
    {
        fprintf(fp, "%c:", (*it).first);
        for (uint_t i = 0; i < bwt_len; i++)
        {
            fprintf(fp, "%d", (*it).second[i]);
            fprintf(fp, ",");
        }
        fseek(fp, -1L, SEEK_CUR); // undo last ","
        fprintf(fp, "-");
        ++it;
    }
    fseek(fp, -1L, SEEK_CUR); // undo last ","
    fprintf(fp, "\n");
    fclose(fp);
}