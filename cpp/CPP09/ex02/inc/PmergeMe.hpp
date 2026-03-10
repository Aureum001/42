#pragma once

#include <deque>
#include <exception>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class PmergeMe {
public:
  explicit PmergeMe(const std::vector<int> &input);
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);
  ~PmergeMe();

  void sort();

  class DuplicateNumber : public std::exception {
    const char *what() const throw();
  };

private:
  PmergeMe();

  std::vector<int> _vec;
  std::deque<int>  _deq;

  static void sortVec(std::vector<int> &seq);
  static void sortDeq(std::deque<int> &seq);
};
