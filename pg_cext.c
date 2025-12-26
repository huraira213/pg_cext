#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"


PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(add_nums);
PG_FUNCTION_INFO_V1(mul_nums);
PG_FUNCTION_INFO_V1(sub_nums);
PG_FUNCTION_INFO_V1(divide_nums);
PG_FUNCTION_INFO_V1(hello_extension);

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