

---

# Mole File Tracker and Editor

**Mole** is a Bash script that tracks file editing sessions and provides several convenient ways to open and manage files based on your editing history. It records each file edit event into a log file (specified by the `MOLE_RC` environment variable) and allows you to:

- Open a specified file and optionally assign it to a group.
- Open the latest or the most frequently edited file in a directory.
- List tracked files with their associated groups.
- Filter files by date or group.
- Generate a compressed secret log of edit events.

---

## Prerequisites

- **Bash**: This script is written in Bash.
- **Environment Variables**:
  - **`MOLE_RC`**: Must be set to the path of the log file where file edit events are stored. If the file doesn’t exist, the script will create it.
  - **`EDITOR`** or **`VISUAL`**: Optionally set your preferred text editor. If neither is set, the script defaults to `vi`.

---

## Installation

1. **Set the Environment Variables**

   In your shell configuration file (e.g., `.bashrc` or `.profile`), add:
   ```bash
   export MOLE_RC="$HOME/.mole_rc"
   export EDITOR="nano"  # Or your preferred editor
   ```

2. **Place the Script**

   Save the script as `mole` (or any name you prefer) and make it executable:
   ```bash
   chmod +x mole
   ```
   You can add the script’s directory to your `PATH` or run it from its location.

---

## Usage

### 1. Open a Specific File

Assign a file to a group (or leave the group unspecified):
```bash
mole -g <GROUP> <FILE>
```
- **Example:**
  ```bash
  mole -g work ~/projects/report.txt
  ```

### 2. Open a File by Editing History

Open a file from a directory based on your editing history:
```bash
mole [FILTERS] [DIRECTORY]
```
- **Default Behavior:** Opens the latest edited file in the specified (or current) directory.
- **Using `-m` Option:** Opens the file that has been edited most frequently.
  
- **Examples:**
  - Open the latest edited file in the current directory:
    ```bash
    mole .
    ```
  - Open the most frequently edited file in a directory:
    ```bash
    mole -m /path/to/directory
    ```

### 3. Filter Files by Date

Use date filters to narrow down file selection:
- **`-a <DATE>`**: Only consider files edited on or after `<DATE>`.
- **`-b <DATE>`**: Only consider files edited on or before `<DATE>`.

Dates should match the format used in the log (e.g., `YYYY-MM-DD-HH-MM-SS`).

### 4. List Tracked Files

Display a list of files (with groups) that have been tracked:
```bash
mole list [FILTERS] [DIRECTORY]
```
- **Example:**
  ```bash
  mole list /path/to/directory
  ```

### 5. Generate a Secret Log

Generate a compressed (bz2) secret log containing the file edit history from one or more directories:
```bash
mole secret-log [DIRECTORY]...
```
- **Example:**
  ```bash
  mole secret-log /projects /documents
  ```

---

## Options Summary

- **`-h`**: Display help information.
- **`-g <GROUP>`**: Open a file and assign it to the specified group.
- **`-m`**: Open the most frequently edited file.
- **`-a <DATE>`**: Filter for files edited on or after a given date.
- **`-b <DATE>`**: Filter for files edited on or before a given date.
- **`list`**: List all tracked files in a directory.
- **`secret-log`**: Generate a compressed log of edit events.

---

## Examples

1. **Open a file and assign it to a group:**
   ```bash
   mole -g work ~/documents/notes.txt
   ```

2. **Open the latest edited file in the current directory:**
   ```bash
   mole .
   ```

3. **Open the most frequently edited file in `/projects`:**
   ```bash
   mole -m /projects
   ```

4. **List all tracked files in `/documents`:**
   ```bash
   mole list /documents
   ```

5. **Generate a secret log for `/projects` and `/documents`:**
   ```bash
   mole secret-log /projects /documents
   ```

---

## Notes

- The script logs each edit event with a timestamp, file name, file path, associated group (if any), and an edit count.
- Ensure that the `MOLE_RC` variable points to a valid file path and that directories/files you reference exist.
- Date filters and group filters help refine the selection when multiple files have been edited.

---
