#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

enum class InstructionType { HLF, TPL, INC, JMP, JIE, JIO };
int registers[2] = {1, 0};

struct Instruction {
  InstructionType type;
  int reg{-1};
  int offset{1000000000};
  void execute(size_t &cur) {
    switch (type) {
    case InstructionType::HLF:
      registers[reg] >>= 1;
      cur++;
      break;
    case InstructionType::TPL:
      registers[reg] *= 3;
      cur++;
      break;
    case InstructionType::INC:
      registers[reg]++;
      cur++;
      break;
    case InstructionType::JMP:
      if (offset < 0 && abs(offset) > cur) {
        cur = 0;
      } else {
        cur += offset;
      }
      break;
    case InstructionType::JIE:
      if (registers[reg] % 2 == 0) {
        if (offset < 0 && abs(offset) > cur) {
          cur = 0;
        } else {
          cur += offset;
        }
      } else {
        cur++;
      }
      break;
    case InstructionType::JIO:
      if (registers[reg] == 1) {
        if (offset < 0 && abs(offset) > cur) {
          cur = 0;
        } else {
          cur += offset;
        }
      } else {
        cur++;
      }
      break;
    default:
      throw std::runtime_error("Strange instruction");
    }
  }
};

auto parseSimple(const std::string &cmd, std::stringstream &ss) -> Instruction {
  Instruction res;
  char reg;
  ss >> reg;
  if (reg == 'a') {
    res.reg = 0;
  } else {
    res.reg = 1;
  }
  if (cmd == "hlf") {
    res.type = InstructionType::HLF;
  } else if (cmd == "tpl") {
    res.type = InstructionType::TPL;
  } else {
    res.type = InstructionType::INC;
  }
  return res;
}

auto parseJmp(const std::string & /*cmd*/,
              std::stringstream &ss) -> Instruction {
  Instruction res{.type = InstructionType::JMP};
  ss >> res.offset;
  return res;
}

auto parseJI(const std::string &cmd, std::stringstream &ss) -> Instruction {
  Instruction res;
  std::string tmp;
  ss >> tmp;
  if (tmp[0] == 'a') {
    res.reg = 0;
  } else {
    res.reg = 1;
  }
  ss >> res.offset;
  if (cmd == "jio") {
    res.type = InstructionType::JIO;
  } else {
    res.type = InstructionType::JIE;
  }
  return res;
}

int main() {
  std::ifstream in("../day23.txt");
  std::string s;
  std::vector<Instruction> instructions;
  std::map<std::string,
           std::function<Instruction(const std::string &, std::stringstream &)>>
      parser;
  parser["hlf"] = &parseSimple;
  parser["tpl"] = &parseSimple;
  parser["inc"] = &parseSimple;
  parser["jmp"] = &parseJmp;
  parser["jie"] = &parseJI;
  parser["jio"] = &parseJI;
  while (std::getline(in, s)) {
    std::stringstream ss(s);
    std::string cmd;
    ss >> cmd;
    instructions.emplace_back(parser[cmd](cmd, ss));
  }
  for (size_t cur = 0; cur < instructions.size();) {
    instructions[cur].execute(cur);
  }
  std::cout << registers[0] << ' ' << registers[1] << '\n';

  return 0;
}
