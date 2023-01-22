#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>


int main() {
  SetConsoleOutputCP(65001);
  std::ifstream fin_1("f.txt");
  
  std::string str;

  std::vector<std::string> names_client;
  std::vector<std::string> haircut_client;

  int kol_client = 0;
  while (!fin_1.eof()) {
    str.erase();
    names_client.resize(kol_client + 1);
    haircut_client.resize(kol_client + 1);
    std::getline(fin_1, str);
    bool ff = false;
    for (int i = 0; i < str.size(); ++i) {
      if (str[i] == ' ') {
        ff = true;
        continue;
      } else if (ff == false) {
        names_client[kol_client] += str[i];
      } else if (ff == true) {
        haircut_client[kol_client] += str[i];
      }
    }
    ++kol_client;
  }
  fin_1.close();
  


  std::ifstream fin_2("g.txt");

  str = "";
  int kol_hairdres = 0;
  std::vector<std::string> hairdres(1);
  std::vector<int> freedom(2);

  while (!fin_2.eof()) {
    hairdres.resize(kol_hairdres + 1);
    freedom.resize(kol_hairdres + 1);
    str.erase();
    std::getline(fin_2, str);
    int i = 0;
    while (str[0] != ' ') {
      str.erase(0, 1);
    }
    hairdres[kol_hairdres] = str;
    freedom[kol_hairdres] = 0;
    kol_hairdres += 1;
  }
  freedom.resize(kol_hairdres);

  fin_2.close();



  std::ofstream fout("r.txt");

  int time = 0, num_hairdres = 0;

  for (int i = 0; i < kol_client; ++i) {

    bool ff = false;
    str = "";
    for (int j = 0; j < hairdres[num_hairdres].size(); ++j) {
      if (hairdres[num_hairdres][j] == ' ') {
        if (ff == false) {
          str = "";
          continue;
        } else {
          break;
        }
      } else {
        str += hairdres[num_hairdres][j];
        if (str == haircut_client[i]) {
          ff = true;
          str = "";
          ++j;
          continue;
        }
      }
    }
    // std::cout << str << std::endl;
    time += stoi(str);
    int hour = 0, min = 0;
    hour = time / 60;
    min = time - hour * 60;
    std::string s;
    fout << names_client[i] << " ";
    if (hour + 8 < 10) fout << "0";
    fout << hour + 8 << ":";
    if (min < 10) fout << "0";
    fout << min << "\n";

    freedom[num_hairdres] = time;
    for (int j = 0; j < kol_hairdres; ++j) {
      if (time > freedom[j]) {
        time = freedom[j];
        num_hairdres = j;
      }
    }
  }

  fout.close();

  return 0;
}