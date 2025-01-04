# Database Viewer Project

## Overview
This project provides a command-line tool to manage a simple database of employees stored in a binary file. It enables you to create, read, update, and delete employee records in the database. The tool operates by loading the database file into memory, performing operations on it, and writing the results back to disk.

## Project Structure
```
├── bin
│   └── dbview             # Compiled binary for the database viewer
├── include
│   ├── common.h           # Common constants and utility macros
│   ├── file.h             # File handling functions declarations
│   └── parse.h            # Parsing and database manipulation declarations
├── Makefile               # Build system file for compiling the project
├── mynewdb.db             # Example database file
├── obj
│   ├── file.o             # Compiled object file for file.c
│   ├── main.o             # Compiled object file for main.c
│   └── parse.o            # Compiled object file for parse.c
├── README.md              # Project documentation (this file)
└── src
    ├── file.c             # Implementation of file handling functions
    ├── main.c             # Main program entry point
    └── parse.c            # Implementation of parsing and manipulation functions
```

## Workflow: From Disk to Memory and Back
1. **Opening or Creating the Database File**:
   - The `main.c` file handles command-line arguments to determine if a new database file should be created or an existing one opened.
   - The `create_db_file` and `open_db_file` functions in `file.c` manage the interaction with the filesystem.

2. **Validating and Loading the Database Header**:
   - If a new file is created, `create_db_header` initializes the database header.
   - For existing files, `validate_db_header` ensures the file integrity by checking its header.

3. **Reading Employee Records into Memory**:
   - The `read_employees` function in `parse.c` loads employee records from the database file into memory. It also handles necessary endian conversions for portability.

4. **Performing Operations on the Database in Memory**:
   - Depending on the command-line arguments:
     - Adding an employee (`add_employee`)
     - Listing all employees (`list_employees`)
     - Updating an employee’s record (`update_employee`)
     - Removing an employee’s record (`remove_employee`)
   - These operations manipulate the in-memory representation of the database.

5. **Writing Changes Back to Disk**:
   - After all operations are complete, the `output_file` function writes the updated database header and employee records back to the file.
   - The file size is adjusted using `ftruncate` if records are removed.

## Features
- **Add Employee**:
  Add a new employee with their name, address, and working hours using the `-a` option.
  ```
  ./bin/dbview -f mynewdb.db -a "John Doe, 123 Elm St, 40"
  ```

- **List Employees**:
  Display all employees in the database with the `-l` option.
  ```
  ./bin/dbview -f mynewdb.db -l
  ```

- **Update Employee**:
  Update the working hours of a specific employee using the `-u` option.
  ```
  ./bin/dbview -f mynewdb.db -u
  ```
  Follow the prompts to specify the employee and new hours.

- **Remove Employee**:
  Remove an employee from the database using the `-r` option with the employee's name.
  ```
  ./bin/dbview -f mynewdb.db -r "John Doe"
  ```

- **Create New Database**:
  Create a new database file with the `-n` option.
  ```
  ./bin/dbview -n -f mynewdb.db
  ```

## Build Instructions
1. Ensure you have a C compiler installed (e.g., `gcc`).
2. Run the `Makefile` to compile the project:
   ```bash
   make
   ```
3. The compiled binary will be available in the `bin/` directory as `dbview`.

## File Descriptions
### Header Files (`include/`)
- `common.h`: Contains common constants and return status macros.
- `file.h`: Declares functions for file handling (e.g., creating, opening database files).
- `parse.h`: Declares functions for manipulating database records (e.g., add, remove, update).

### Source Files (`src/`)
- `file.c`: Implements file handling functions to manage interaction with the filesystem.
- `main.c`: The entry point of the program; handles argument parsing and orchestrates database operations.
- `parse.c`: Implements database manipulation functions, including reading, writing, and updating records.

## Example Usage
1. **Create a New Database**:
   ```bash
   ./bin/dbview -n -f mynewdb.db
   ```

2. **Add an Employee**:
   ```bash
   ./bin/dbview -f mynewdb.db -a "Alice, 456 Maple St, 35"
   ```

3. **List Employees**:
   ```bash
   ./bin/dbview -f mynewdb.db -l
   ```

4. **Update an Employee**:
   ```bash
   ./bin/dbview -f mynewdb.db -u
   ```

5. **Remove an Employee**:
   ```bash
   ./bin/dbview -f mynewdb.db -r "Alice"
   ```

## Notes
- Ensure the database file (`mynewdb.db`) is not deleted or corrupted, as this could result in data loss or program errors.
- The database uses a simple binary format; manual edits to the file may corrupt it.
