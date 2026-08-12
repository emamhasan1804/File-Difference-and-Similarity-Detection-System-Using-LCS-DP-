# File Difference and Similarity Detection System Using LCS Dynamic Programming

A C++ command-line application for comparing two text files using the **Longest Common Subsequence (LCS)** algorithm and **Dynamic Programming**. The system identifies unchanged, added, and removed lines and calculates an overall similarity percentage.

## Features

- Compare two text files line by line
- Detect unchanged lines
- Detect added lines
- Detect removed lines
- Calculate file similarity percentage
- LCS-based comparison
- Dynamic Programming implementation
- Command-line execution
- No external diff libraries required

## Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Application development |
| `fstream` | Reading files |
| `vector` | Storing file lines |
| `string` | Representing text |
| Dynamic Programming | Computing LCS |
| LCS | Finding the longest common sequence |
| Backtracking | Reconstructing differences |
| Command Line | Providing file inputs |

## System Architecture

```text
File Input
    ↓
Read and Store Lines
    ↓
LCS Dynamic Programming
    ↓
Backtracking & Diff Generation
    ↓
Similarity Calculation
    ↓
Output
```

## How It Works

The user provides two filenames through the command line:

```bash
./diff old.txt new.txt
```

The first file is considered the original version, while the second file is considered the modified version.

Each file is opened using `ifstream`. Every line is read and stored in a `vector<string>`.

## Longest Common Subsequence

The central algorithm used in the project is the **Longest Common Subsequence (LCS)** algorithm.

A subsequence is a sequence obtained by deleting zero or more elements from another sequence while preserving the order of the remaining elements.

Example:

```text
A = A B C D E
B = A B X D E

LCS = A B D E
```

In this project, each element represents an entire line rather than an individual character.

## Dynamic Programming Approach

Suppose:

```text
N = number of lines in File A
M = number of lines in File B
```

The program creates a two-dimensional DP table of size:

```text
(N + 1) × (M + 1)
```

### Recurrence

If the current lines match:

```text
if A[i-1] == B[j-1]
    dp[i][j] = dp[i-1][j-1] + 1
```

Otherwise:

```text
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

## Backtracking

The program backtracks from `dp[N][M]` toward `dp[0][0]` to reconstruct the actual differences.

### Matching Lines

If:

```text
A[i-1] == B[j-1]
```

the algorithm moves diagonally:

```text
(i, j) → (i-1, j-1)
```

The line is marked as unchanged.

### Removed Lines

If the DP value above the current cell is greater than the value to the left:

```text
(i, j) → (i-1, j)
```

The corresponding line from the original file is marked as removed.

### Added Lines

If the value to the left is greater than or equal to the value above:

```text
(i, j) → (i, j-1)
```

The corresponding line from the modified file is marked as added.

Because backtracking starts from the end, the reconstructed result is reversed before displaying.

## Diff Representation

The system uses three symbols:

```text
  unchanged
- removed
+ added
```

Example:

```diff
  Hello
  This is line two
- This is line three
+ This is a new line
  Goodbye
+ See you
```

## Similarity Calculation

Let:

- `L` = length of the LCS
- `N` = number of lines in the first file
- `M` = number of lines in the second file

The similarity formula is:

```text
Similarity = (2 × L / (N + M)) × 100
```

Example:

```text
First file  = 4 lines
Second file = 5 lines
LCS         = 4 lines

Similarity = (2 × 4 / 9) × 100
           ≈ 88.89%
```

This is a structural line-level similarity measure. It does not measure semantic similarity and should not by itself be considered a complete plagiarism detector.

## Algorithm

```text
1. Start
2. Read the first file
3. Read the second file
4. Store the lines of both files in vectors
5. Create an LCS DP table
6. Initialize the first row and first column to zero
7. Compare every pair of lines
8. Fill the DP table using the LCS recurrence
9. Start backtracking from the bottom-right cell
10. Mark matching lines as unchanged
11. Mark lines present only in the first file as removed
12. Mark lines present only in the second file as added
13. Reverse the reconstructed result
14. Display the diff
15. Calculate the similarity percentage
16. Display the similarity
17. End
```

## Pseudocode

```text
READ file A
READ file B

n = number of lines in A
m = number of lines in B

CREATE dp[n+1][m+1]

FOR i = 1 TO n
    FOR j = 1 TO m

        IF A[i-1] == B[j-1]
            dp[i][j] = dp[i-1][j-1] + 1
        ELSE
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])

START i = n
START j = m

WHILE i > 0 OR j > 0

    IF i > 0 AND j > 0 AND A[i-1] == B[j-1]
        MARK line as UNCHANGED
        i--
        j--

    ELSE IF j > 0 AND (i == 0 OR dp[i][j-1] >= dp[i-1][j])
        MARK B[j-1] as ADDED
        j--

    ELSE
        MARK A[i-1] as REMOVED
        i--

REVERSE result
DISPLAY result

L = dp[n][m]

Similarity = (2 × L / (n + m)) × 100

DISPLAY similarity
```

## Complexity Analysis

Let:

```text
N = number of lines in File 1
M = number of lines in File 2
```

### Time Complexity

The DP table has `(N + 1) × (M + 1)` cells, and each cell is calculated once.

```text
O(N × M)
```

The backtracking phase takes:

```text
O(N + M)
```

Therefore, the overall time complexity remains:

```text
O(N × M)
```

### Space Complexity

The complete two-dimensional DP table is stored in memory:

```text
O(N × M)
```

Additional storage is required for the two file-line vectors and the reconstructed diff.

## Installation

Clone the repository:

```bash
git clone <repository-url>
cd <repository-folder>
```

## Compilation

Compile using G++:

```bash
g++ -std=c++17 main.cpp -o diff
```

On macOS:

```bash
g++ -std=c++17 main.cpp -o diff
```

## Usage

Run the program with two text files:

```bash
./diff old.txt new.txt
```

Where:

```text
old.txt → Original file
new.txt → Modified file
```

## Example

### `old.txt`

```text
Hello
This is line two
This is line three
Goodbye
```

### `new.txt`

```text
Hello
This is line two
This is a new line
Goodbye
See you
```

### Output

```text
========== DIFF ==========

  Hello
  This is line two
- This is line three
+ This is a new line
  Goodbye
+ See you

===========================

Similarity: 77.7778%
```

## Testing

### Test Case 1: Identical Files

File A:

```text
Hello
World
```

File B:

```text
Hello
World
```

Expected:

```text
Hello
World

Similarity: 100%
```

### Test Case 2: Completely Different Files

File A:

```text
Apple
Banana
```

File B:

```text
Car
Dog
```

Expected:

```diff
- Apple
- Banana
+ Car
+ Dog
```

Similarity:

```text
0%
```

### Test Case 3: Addition

File A:

```text
A
B
C
```

File B:

```text
A
B
C
D
```

Expected:

```diff
  A
  B
  C
+ D
```

### Test Case 4: Removal

File A:

```text
A
B
C
D
```

File B:

```text
A
B
D
```

Expected:

```diff
  A
  B
- C
  D
```

### Test Case 5: Modification

File A:

```text
A
B
C
```

File B:

```text
A
B
X
```

Expected:

```diff
  A
  B
- C
+ X
```

## Applications

### Software Development

Compare different versions of source-code files and identify modifications.

### Document Comparison

Compare different versions of reports, notes, assignments, and other documents.

### Version Control

Sequence comparison is a fundamental concept behind file-difference systems used in version-control software.

### Plagiarism Detection

LCS-based comparison can identify substantial matching sequences between documents or source-code files. A production plagiarism detector would require additional semantic and structural analysis.

### Data Analysis

Sequential datasets can be compared to identify common ordered structures.

### Educational Tools

The project demonstrates:

- Dynamic Programming
- Sequence comparison
- Recurrence relations
- Backtracking
- DP table construction

## Advantages

1. Uses a well-established Dynamic Programming algorithm.
2. Provides a clear line-by-line representation of differences.
3. Does not require external diff libraries.
4. Is relatively simple to understand and implement.
5. Demonstrates both DP table construction and reconstruction.
6. Provides a quantitative similarity measurement.
7. Can serve as a foundation for more advanced comparison systems.

## Limitations

1. Comparison is performed at the complete-line level.
2. Small changes within a line are treated as a modification of the entire line.
3. The `O(N × M)` memory requirement can become expensive for very large files.
4. The similarity score does not represent semantic similarity.
5. The system does not understand programming-language syntax.
6. It does not detect meaning-preserving code transformations.
7. It does not provide an advanced visual interface.
8. Multiple equally optimal LCS solutions may exist, so the exact diff can depend on the tie-breaking rule used during backtracking.

## Future Improvements

- Word-level comparison
- Character-level comparison
- Side-by-side diff output
- Ignore-whitespace option
- Ignore-case option
- Directory comparison
- Recursive directory comparison
- HTML diff report generation
- Exporting results to a file
- More memory-efficient LCS implementations
- Unified diff format similar to Git
- Syntax highlighting for source-code files
- Programming-language-aware comparison
- Advanced visual interface

## Project Structure

```text
file-diff/
│
├── main.cpp
├── old.txt
├── new.txt
├── README.md
│
└── test/
    ├── test1.txt
    ├── test2.txt
    └── ...
```

## Course Information

**Course:** CSE-2212 Design and Analysis of Algorithms-I Lab

**Department:** Department of Computer Science and Engineering

**University:** Netrokona University, Netrokona

## Author

**Md. Emam Hasan**

- Roll: 408
- Session: 2022-23
- Registration No: 202204008
- Department of Computer Science and Engineering
- Netrokona University

## License

This project was developed as an academic project for the **CSE-2212 Design and Analysis of Algorithms-I Lab** course.
