#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

vector<int> initial{8, 3, 9, 5, 14, 11, 23, 2, 6};

void splitVector()
{
  vector<int> even, odd;
  for (int value : initial)
  {
    if (value % 2 == 0)
      even.push_back(value);
    else
      odd.push_back(value);
  }

  for (int value : even)
    cout << value << " ";
  cout << endl;
  for (int value : odd)
    cout << value << " ";
}

void sortedAddition()
{
  int number = 0;
  vector<int> nums;

  while (true)
  {
    cout << "Please enter a positive number (-1 to quit): ";
    cin >> number;
    if (number == -1)
      break;

    if (nums.size() == 0 || number >= nums[nums.size() - 1])
      nums.push_back(number);
    else
    {
      int initialSize = nums.size();
      for (int i = 0; i < initialSize; ++i)
        if (number <= nums[i])
          nums.insert(nums.begin() + i, number);
    }
  }

  for (int value : nums)
    cout << value << endl;
}

double average(vector<int> &grades)
{
  int sum = 0;
  for (int grade : grades)
    sum += grade;
  return (double)sum / (double)grades.size();
}

double requiredAverage(double currentAverage, int currentNumberOfQuarters, int desiredGrade)
{
  return (double)((desiredGrade * 4) - (currentAverage * currentNumberOfQuarters)) / (double)(4 - currentNumberOfQuarters);
}

void finalGradeCalculator()
{
  vector<int> quarterlyGrades;
  int quarterlyGrade = 0;

  while (true)
  {
    cout << "Please enter your quarterly grade (-1 when finished): ";
    cin >> quarterlyGrade;

    if (quarterlyGrade == -1)
      break;

    quarterlyGrades.push_back(quarterlyGrade);
  }

  double currentAverage = average(quarterlyGrades);

  int currentLetterGradeValue = 0;
  char currentLetter;
  if (currentAverage >= 90)
  {
    currentLetterGradeValue = 90;
    currentLetter = 'A';
  }
  else if (currentAverage >= 80)
  {
    currentLetterGradeValue = 80;
    currentLetter = 'B';
  }
  else if (currentAverage >= 70)
  {
    currentLetterGradeValue = 70;
    currentLetter = 'C';
  }
  else
  {
    currentLetterGradeValue = 60;
    currentLetter = 'D';
  }

  double requiredAverageToMaintain = requiredAverage(currentAverage, quarterlyGrades.size(), currentLetterGradeValue);
  double requiredAverageForNextGrade = 0;
  if (currentLetterGradeValue == 90)
    requiredAverageForNextGrade = requiredAverageToMaintain;
  else
    requiredAverageForNextGrade = requiredAverage(currentAverage, quarterlyGrades.size(), currentLetterGradeValue + 10);

  cout << "To get a " << (currentLetter == 'A' ? 'A' : static_cast<char>(int(currentLetter) - 1)) << " for the year, you will need to average: " << requiredAverageForNextGrade << endl;
  cout << "To get a " << currentLetter << " for the year, you will need to average: " << requiredAverageToMaintain << endl;
}

int main()
{
  return 0;
}
