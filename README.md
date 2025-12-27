# pg_cext - PostgreSQL C Extension

This is a simple PostgreSQL extension written in C, named `pg_cext` (short for PostgreSQL C Extension). It serves as a learning example for creating custom extensions in PostgreSQL. The extension provides basic arithmetic operations, mathematical functions, string manipulation, and array operations.

## Files in the Project

### pg_cext.c
This is the main C source file containing the implementation of the extension's functions:
- `add_nums(int, int)`: Adds two integers.
- `mul_nums(int, int)`: Multiplies two integers.
- `sub_nums(int, int)`: Subtracts the second integer from the first.
- `divide_nums(int, int)`: Divides the first integer by the second (with division by zero check).
- `factorial(int)`: Calculates the factorial of a non-negative integer (max 12 to avoid overflow).
- `is_prime(int)`: Checks if an integer is prime.
- `safe_divide(float8, float8)`: Safely divides two floats, returning NULL for division by zero or NULL inputs.
- `power_float(float8, float8)`: Raises the first float to the power of the second float.
- `arr_sum(float8[])`: Calculates the sum of all elements in a float8 array.
- `arr_max(float8[])`: Finds the maximum value in a float8 array.
- `hello_extension(text)`: Returns a greeting message prefixed with "Hello, " followed by the input text.
- `hows_your_day(text)`: Returns a response about the day's mood based on input text.
- `reverse_string(text)`: Reverses the input string.
- `capitalize_text(text)`: Capitalizes the first letter of each word in the input text.
- `count_words(text)`: Counts the number of words in the input text.

The file includes necessary PostgreSQL headers and uses the PG_MODULE_MAGIC macro to identify it as a PostgreSQL module.

### pg_cext.control
This is the control file for the PostgreSQL extension. It provides metadata about the extension:
- `default_version = '1.0'`: Specifies the default version of the extension.
- `comment = 'Learning extension for PostgreSQL'`: A brief description of the extension's purpose.
- `module_pathname = '$libdir/pg_cext'`: The path to the compiled shared library (usually installed in PostgreSQL's lib directory).
- `relocatable = true`: Indicates that the extension can be installed in any schema.

The control file is essential for PostgreSQL to recognize and manage the extension during installation and upgrades.

### pg_cext--1.0.sql
This SQL script file defines the functions in the PostgreSQL catalog. It creates each function using the `CREATE OR REPLACE FUNCTION` statement, linking them to the corresponding C functions in the shared library via `MODULE_PATHNAME`. The functions are declared as `LANGUAGE C STRICT`, meaning they are implemented in C and handle NULL inputs strictly.

### Makefile
The Makefile is used to build the extension. It defines:
- `MODULES = pg_cext`: The name of the module to build.
- `EXTENSION = pg_cext`: The extension name.
- `DATA = pg_cext--1.0.sql`: The SQL file to install.
- It uses `pg_config` to locate PostgreSQL's build system (PGXS) for compilation.

Running `make` will compile the C code into a shared library (typically `pg_cext.so`).

### pg_cext.bc
This appears to be a compiled bytecode file, possibly generated during the build process if using LLVM or JIT compilation features in PostgreSQL. It may be an intermediate or optimized version of the compiled code.

### LICENSE
The license file contains the terms under which this software is distributed. (Note: The actual content of the license is not detailed here; refer to the file for specifics.)

## Building and Installing the Extension

1. Ensure you have PostgreSQL development headers installed.
2. Run `make` to build the extension.
3. Run `make install` (as superuser) to install the extension into PostgreSQL.
4. In PostgreSQL, run `CREATE EXTENSION pg_cext;` to enable the extension.

## Usage

After installation, you can use the functions in SQL queries:

```sql
-- Arithmetic operations
SELECT add_nums(5, 3);  -- Returns 8
SELECT mul_nums(5, 3);  -- Returns 15
SELECT sub_nums(5, 3);  -- Returns 2
SELECT divide_nums(6, 3);  -- Returns 2

-- Mathematical functions
SELECT factorial(5);  -- Returns 120
SELECT is_prime(7);  -- Returns true
SELECT is_prime(10);  -- Returns false
SELECT safe_divide(10.0, 2.0);  -- Returns 5.0
SELECT safe_divide(10.0, 0.0);  -- Returns NULL
SELECT power_float(2.0, 3.0);  -- Returns 8.0

-- Array operations
SELECT arr_sum(ARRAY[1.0, 2.0, 3.0, 4.0]);  -- Returns 10.0
SELECT arr_max(ARRAY[1.0, 5.0, 3.0, 9.0, 2.0]);  -- Returns 9.0

-- Greeting functions
SELECT hello_extension('World');  -- Returns 'Hello, World!'
SELECT hows_your_day('great');  -- Returns 'Today my day is , great?'

-- String manipulation
SELECT reverse_string('hello world');  -- Returns 'dlrow olleh'
SELECT capitalize_text('hello world from postgres');  -- Returns 'Hello World From Postgres'
SELECT count_words('hello world from postgres');  -- Returns 4
```

## Purpose

This extension demonstrates the basics of writing PostgreSQL extensions in C, including:
- Defining C functions with PostgreSQL's function manager interface.
- Creating the necessary control and SQL files.
- Building and installing the extension.
- Implementing various data types: integers, floats, booleans, text strings, and arrays.
- Handling NULL values and error conditions.

It's intended for educational purposes to help developers learn how to extend PostgreSQL with custom functionality.