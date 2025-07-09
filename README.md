# Static File Analyzer

A simple tool built for analyzing memory vulnerabilities or unsafe/insecure C file contents. Built entirely using C and stdlib.

## Directory Structure

```text
Static Analyzer/
├── .gitignore
├── outputs/
├── README.md
├── src/
│   ├── analyze.exe
│   ├── build.bat
│   ├── export.c
│   ├── export.h
│   ├── main.c
│   ├── patterns.c
│   ├── patterns.h
│   ├── scanner.c
│   ├── scanner.h
├── test/
│   ├── bad_code.c
│   ├── nested/
│   │   ├── insecure_code.c
```

## Usage

Make sure you have `gcc` installed (e.g., via MSYS2 or MinGW on Windows).

### 🔧 Build

You can compile the project manually:

```PowerShell
gcc main.c scanner.c patterns.c export.c -o analyze.exe
```

Or, use the provided build.bat script on Windows:

```powershell
./build.bat
```

### Run

```PowerShell
./analyze.exe <target_path> [--summary] [--output json|csv]
```

Arguments:

- <target_path>: Path to a .c file or directory containing .c files to use the tool on

- --summary: Show a total count of detected issues at the end.

- --output json|csv: Export results to results.json or results.csv.

## Features

- Scans C source files for insecure patterns such as:

- Use of gets(), strcpy(), scanf() without length checks

- Dangerous format strings in printf(), etc.

- Recursively scans directories

- Supports output in JSON and CSV

- Summary mode for quick insights

- Modular design for easy extensibility

## Example Output

CLI Output:

```PowerShell

[INFO] Scanning: ../test\vuln.c
    [WARNING] Line 6: gets( --> Use of 'gets' is insecure, use 'fgets' instead.
    [WARNING] Line 10: system( --> Use of 'system' may lead to command injection.

Total warnings: 2
```

JSON Output (results.json)

```json
[
  {
    "file": "test/vuln.c",
    "line": 6,
    "pattern": "gets",
    "message": "Use of 'gets' is insecure, use 'fgets' instead"
  },
  {
    "file": "test/vuln.c",
    "line": 10,
    "pattern": "system",
    "message": "system( --> Use of 'system' may lead to command injection."
  }
]
```

## Contributing

Pull requests and issues are welcome!

- Fork this repo

- Create a new branch (git checkout -b feature/your-feature)

- Commit your changes

- Push and create a PR

Please ensure your code is clean and well-documented. 

## 📜 License

MIT License © 2025 AndyFerns
