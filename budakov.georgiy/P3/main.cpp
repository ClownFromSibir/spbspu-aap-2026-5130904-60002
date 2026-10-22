#include<iostream>
#include<string>
#include<fstream>
const int stack_mode = 1;
const int heap_mode = 2;
const int MAX_SIZE = 100;
bool isNumber(char* arg)
{
  int dummy_num;
  char dummy_char;
  return std::sscanf(arg, "%d", &dummy_num, &dummy_char) == 1;
}
void readFile(int& x, std::ifstream& file)
{
  file >> x;
  if (file.fail())
  {
    if (file.eof())
    {
      throw std::invalid_argument("Reached the end of file\n");
    }
    throw std::invalid_argument("Invalid argument\n");
  }
}
void initMatrix(int matrix[][MAX_SIZE], int rows, int cols, std::ifstream& inpf)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::invalid_argument("Rows or cols <= 0 \n");
  }
  if (rows > MAX_SIZE || cols > MAX_SIZE)
  {
    throw std::invalid_argument("Rows or cols > max size\n");
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      readFile(matrix[i][j], inpf);
    }
  }
}
void initMatrix(int** matrix, int rows, int cols, std::ifstream& inpf)
{
  if (rows <= 0 || cols <= 0)
  {
    return;
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      readFile(matrix[i][j], inpf);
    }
  }
}
void spiralAdd(int matrix[][MAX_SIZE], int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    return;
  }
  int addend = 1;
  int left = 0;
  int right = cols - 1;
  int top = 0;
  int bottom = rows - 1;
  while (left <= right && top <= bottom)
  {
    for (int i = top; i <= bottom; i++)
    {
      matrix[i][left] += addend;
      addend++;
    }
    left++;
    for (int i = left; i <= right; i++)
    {
      matrix[bottom][i] += addend;
      addend++;
    }
    bottom--;
    for (int i = bottom; i >= top; i--)
    {
      matrix[i][right] += addend;
      addend++;
    }
    right--;
    for (int i = right; i >= left; i--)
    {
      matrix[top][i] += addend;
      addend++;
    }
    top++;
  }
}
void spiralAdd(int** matrix, int rows, int cols)
{
  if (matrix == nullptr)
  {
    return;
  }
  int addend = 1;
  int left = 0;
  int right = cols - 1;
  int top = 0;
  int bottom = rows - 1;
  while (left <= right && top <= bottom)
  {
    for (int i = top; i <= bottom; i++)
    {
      matrix[i][left] += addend;
      addend++;
    }
    left++;
    for (int i = left; i <= right; i++)
    {
      matrix[bottom][i] += addend;
      addend++;
    }
    bottom--;
    for (int i = bottom; i >= top; i--)
    {
      matrix[i][right] += addend;
      addend++;
    }
    right--;
    for (int i = right; i >= left; i--)
    {
      matrix[top][i] += addend;
      addend++;
    }
    top++;
  }
}
void printMatrix(int matrix[][MAX_SIZE], int rows, int cols, std::ofstream& outf)
{
  if (rows <= 0 || cols <= 0)
  {
    return;
  }
  outf << rows << " " << cols;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      outf << " " << matrix[i][j];
    }
  }
  outf << "\n";
}
void printMatrix(int** matrix, int rows, int cols, std::ofstream& outf)
{
  if (matrix == nullptr)
  {
    return;
  }
  outf << rows << " " << cols;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      outf << " " << matrix[i][j];
    }
  }
  outf << "\n";
}
int** allocateMatrix(int rows, int cols)
{
  int** matrix = nullptr;
  if (rows <= 0 || cols <= 0)
  {
    return matrix;
  }
  try{
    matrix = new int* [rows] ();
    for (int i = 0; i < rows; i++)
    {
      matrix[i] = new int[cols] ();
    }
  }
  catch (...)
  {
    for (int i = 0; i < rows; i++)
    {
      delete matrix[i];
      matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
    throw;
  }
  return matrix;
}
void freeMatrix(int** matrix, int rows, int cols)
{
  if (matrix == nullptr)
  {
    return;
  }
  for (int i = 0; i < rows; i++)
  {
    delete matrix[i];
    matrix[i] = nullptr;
  }
  delete[] matrix;
  matrix = nullptr;
}
int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  else if (!isNumber(argv[1]))
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  else if (1 > std::stoi(argv[1]) || std::stoi(argv[1]) > 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  if(!input.is_open())
  {
    std::cerr << "Couldn't open the file\n";
    return 2;
  }
  int rows;
  int cols;
  try
  {
    readFile(rows, input);
    readFile(cols, input);
  }
  catch (std::invalid_argument& e)
  {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 2;
  }
  if (std::stoi(argv[1]) == stack_mode)
  {
    int array[MAX_SIZE][MAX_SIZE]{};
    try
    {
      initMatrix(array, rows, cols, input);
      spiralAdd(array, rows, cols);
      printMatrix(array, rows, cols, output);
    }
    catch (std::invalid_argument& e)
    {
      std::cerr << "ERROR: " << e.what() << "\n";
      return 2;
    }
    catch (...)
    {
      std::cerr << "ERROR: Unknown error\n";
    }
    if (!input.eof())
    {
      std::cerr << "Didn't reach the end of file\n";
      return 2;
    }
  }
  else if (std::stoi(argv[1]) == heap_mode)
  {
    int** array = nullptr;
    try
    {
      array = allocateMatrix(rows, cols);
      initMatrix(array, rows, cols, input);
      spiralAdd(array, rows, cols);
      printMatrix(array, rows, cols, output);
      freeMatrix(array, rows, cols);
    }
    catch (std::invalid_argument& e)
    {
      std::cerr << "ERROR: " << e.what() << "\n";
      return 2;
    }
    catch (...)
    {
      std::cerr << "ERROR: Unknown error\n";
    }
    if (!input.eof())
    {
      std::cerr << "Didn't reach the end of file\n";
      return 2;
    }
  }
  return 0;
}
