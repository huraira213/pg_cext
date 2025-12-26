# pg_cext - PostgreSQL C Extension

This is a simple PostgreSQL extension written in C, named `pg_cext` (short for PostgreSQL C Extension). It serves as a learning example for creating custom extensions in PostgreSQL. The extension provides basic arithmetic operations (addition, subtraction, multiplication, division) and a greeting function.

## Files in the Project

### pg_cext.c
This is the main C source file containing the implementation of the extension's functions:
- `add_nums(int, int)`: Adds two integers.
- `mul_nums(int, int)`: Multiplies two integers.
- `sub_nums(int, int)`: Subtracts the second integer from the first.
- `divide_nums(int, int)`: Divides the first integer by the second (with division by zero check).
- `hello_extension(text)`: Returns a greeting message prefixed with "Hello, " followed by the input text.

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
SELECT add_nums(5, 3);  -- Returns 8
SELECT hello_extension('World');  -- Returns 'Hello, World!'
```

## Purpose

This extension demonstrates the basics of writing PostgreSQL extensions in C, including:
- Defining C functions with PostgreSQL's function manager interface.
- Creating the necessary control and SQL files.
- Building and installing the extension.

It's intended for educational purposes to help developers learn how to extend PostgreSQL with custom functionality.