#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

int kol;

std::string SearchLar(std::string &str, int pos, std::vector<int>& arr) {
  std::string out;
  std::string word_lar;
  for (int i = pos; i < pos + 5; ++i) {
    word_lar += str[i];
  }
  if (word_lar != "Larec") return word_lar;
  if (!isdigit(str[pos + 5])) return word_lar;

  pos += 5;
  bool ff = false;
  std::string num_lar;
  for (int i = pos; i < str.size(); ++i) {
    if (str[i] == ',') {
      ff = true;
      break;
    } else if (!isdigit(str[i])) {
      num_lar += str[i];
      ff = false;
      break;
    } else {
      num_lar += str[i];
      if (i == str.size() - 1) {
        ff = true;
      }
    }
  }
  if (ff == false) return word_lar + num_lar;
  int num = stoi(num_lar);
  
  // std::cout << num << std::endl;

  ff = false;
  int num_str_lar;
  for (int i = 0; i < kol; ++i) {
    // std::cout << arr[i] << " " << num << std::endl;
    if (arr[i] == num) {
      ff = true;
      num_str_lar = i;
      break;
    }
  }
  if (ff == false) return word_lar + num_lar;

  str.erase(pos - 5, 5 + num_lar.size());
  // std::cout << "str " << str << std::endl;

  std::ifstream f("f.txt");

  getline(f, out);
  for (int i = 0; i <= num_str_lar; ++i) {
    getline(f, out);
  }


  while (out[0] != ' ') {
    out.erase(0, 1);
  }
  if (out[0] == ' ') out.erase(0, 1);

  str.insert(pos - 5, out);

  // std::cout << "str " << str << std::endl;

  f.close();

  return out;
}

int main() {
  SetConsoleOutputCP(65001);
  std::ifstream fin("f.txt");

  std::string str;
  getline(fin, str);
  kol = stoi(str);

  int num_lar;
  std::cin >> num_lar;

  std::vector<int> arr(kol);
  int i = 0;

  while (i != kol) {
    str.erase();
    getline(fin, str);
    std::string str_num;
    for (int i = 5; i < str.size(); ++i) {
      if (str[i] == ':') break;
      str_num += str[i];
    }
    if (str_num.empty()) {
      std::cout << "Error!!!";
      return 0;
    }
    int num = stoi(str_num);
    arr[i] = num;
    ++i;
  }


  bool ff = false;
  int num_str_lar = 0;
  for (int i = 0; i < kol; ++i) {
    if (arr[i] == num_lar) {
      ff = true;
      num_str_lar = i;
      break;
    }
  }
  if (ff == false) {
    std::cout << "Error!!!";
    return 0;
  }

  fin.close();
  str.erase();
  fin.open("f.txt");

  getline(fin, str);

  for (int i = 0; i <= num_str_lar; ++i) {
    getline(fin, str);
  }

  std::cout << str << std::endl;

  while (str[0] != ' ') {
    str.erase(0, 1);
  }
  if (str[0] == ' ') str.erase(0, 1);

  ff = false;
  for (int i = 0; i < str.size(); ++i) {
      if (str[i] == 'L') {
        std::string s = SearchLar(str, i, arr);
        i += s.size() - 1;
      }
  }

  std::cout << str << std::endl;

  fin.close();

  return 0;
}