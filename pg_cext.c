#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"


PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(add_nums);
PG_FUNCTION_INFO_V1(mul_nums);
PG_FUNCTION_INFO_V1(sub_nums);
PG_FUNCTION_INFO_V1(divide_nums);
PG_FUNCTION_INFO_V1(hello_extension);
PG_FUNCTION_INFO_V1(hows_your_day);
PG_FUNCTION_INFO_V1(reverse_string);
PG_FUNCTION_INFO_V1(capitalize_text);
PG_FUNCTION_INFO_V1(count_words);

Datum add_nums(PG_FUNCTION_ARGS)
{
    int32 arg1 = PG_GETARG_INT32(0);
    int32 arg2 = PG_GETARG_INT32(1);

    PG_RETURN_INT32(arg1 + arg2);
}

Datum mul_nums(PG_FUNCTION_ARGS)
{
    int32 arg1 = PG_GETARG_INT32(0);
    int32 arg2 = PG_GETARG_INT32(1);

    PG_RETURN_INT32(arg1 * arg2);
}

Datum sub_nums(PG_FUNCTION_ARGS)
{
    int32 arg1 = PG_GETARG_INT32(0);
    int32 arg2 = PG_GETARG_INT32(1);

    PG_RETURN_INT32(arg1 - arg2);
}

Datum divide_nums(PG_FUNCTION_ARGS)
{
    int32 arg1 = PG_GETARG_INT32(0);
    int32 arg2 = PG_GETARG_INT32(1);

    if (arg2 == 0)
        ereport(ERROR,
                (errcode(ERRCODE_DIVISION_BY_ZERO),
                 errmsg("division by zero")));

    PG_RETURN_INT32(arg1 / arg2);
}

Datum hello_extension(PG_FUNCTION_ARGS)
{
    text *input_text = PG_GETARG_TEXT_PP(0);
    char *c_string = text_to_cstring(input_text);
    char *result_c_string = psprintf("Hello, %s!", c_string);
    text *result_text = cstring_to_text(result_c_string);

    PG_RETURN_TEXT_P(result_text);
}

// Get the input text, convert to C string, format a response, and return as text
Datum hows_your_day(PG_FUNCTION_ARGS)
{
    text*input_text = PG_GETARG_TEXT_PP(0);
    char*c_string = text_to_cstring(input_text);
    char*result_c_string = psprintf("Today my day is , %s?", c_string);
    text*result_text = cstring_to_text(result_c_string);

    PG_RETURN_TEXT_P(result_text);
}

// Get the input text, convert to C string, reverse it, and return as text
Datum reverse_string(PG_FUNCTION_ARGS)
{
    text *input_text = PG_GETARG_TEXT_PP(0);
    char *c_string = text_to_cstring(input_text);
    int len = strlen(c_string);
    char *rev_c_string = palloc(len + 1);

    for (int i = 0; i < len; i++)
    {
        rev_c_string[i] = c_string[len - 1 - i];
    }
    rev_c_string[len] = '\0';

    text *result_text = cstring_to_text(rev_c_string);

    PG_RETURN_TEXT_P(result_text);
}

// Capitalize the first letter of each word in the input text
Datum capitalize_text(PG_FUNCTION_ARGS)
{
    text *input_text = PG_GETARG_TEXT_PP(0);
    char *c_string = text_to_cstring(input_text);
    int len = strlen(c_string);
    char *cap_c_string = palloc(len + 1);

    bool capitalize_next = true;
    for (int i = 0; i < len; i++)
    {
        if (capitalize_next && isalpha(c_string[i]))
        {
            cap_c_string[i] = toupper(c_string[i]);
            capitalize_next = false;
        }
        else
        {
            cap_c_string[i] = c_string[i];
            capitalize_next = (c_string[i] == ' ');
        }
    }
    cap_c_string[len] = '\0';

    text *result_text = cstring_to_text(cap_c_string);

    PG_RETURN_TEXT_P(result_text);
}

// Count the number of words in the input text
Datum count_words(PG_FUNCTION_ARGS)
{
    text *input_text = PG_GETARG_TEXT_PP(0);
    char *c_string = text_to_cstring(input_text);
    int len = strlen(c_string);
    int word_count = 0;
    bool in_word = false;

    for (int i = 0; i < len; i++)
    {
        if (isspace(c_string[i]))
        {
            if (in_word)
            {
                word_count++;
                in_word = false;
            }
        }
        else
        {
            in_word = true;
        }
    }

    if (in_word)
    {
        word_count++;
    }

    PG_RETURN_INT32(word_count);
}