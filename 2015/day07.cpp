#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Circuit {
private:
  enum class Type { OP, VAR, ARROW, VAL };
  struct Word {
    std::string val;
    Type type;
    bool negate;
  };

  struct Sentence {
    std::vector<Word> words;
    int nVar{0};
  };

  std::vector<Sentence> sentences_;

  std::unordered_map<std::string, int> valMap_;
  std::unordered_set<std::string> reservedKeywords_ = {"NOT", "AND", "OR",
                                                       "LSHIFT", "RSHIFT"};
  std::unordered_map<std::string, std::vector<int>> adj_;
  std::queue<int> queue_;
  std::vector<bool> visited_;

  auto preprocess(const std::vector<std::string> &tokens) -> Sentence {
    Sentence sentence;
    for (auto &token : tokens) {
      if (reservedKeywords_.contains(token)) {
        sentence.words.emplace_back(token, Type::OP);
      } else if (token == "->") {
        sentence.words.emplace_back(token, Type::ARROW);
      } else if (std::any_of(token.begin(), token.end(),
                             [](const char &c) { return !std::isdigit(c); })) {
        bool neg = false;
        if (!sentence.words.empty() && sentence.words.back().val == "NOT") {
          neg = true;
          sentence.words.pop_back();
        }
        valMap_[token] = 0;
        sentence.words.emplace_back(token, Type::VAR, neg);
        sentence.nVar++;
      } else {
        sentence.words.emplace_back(token, Type::VAL);
      }
    }
    return sentence;
  }

  void buildGraph(const std::vector<Sentence> &sentences) {
    visited_.assign(sentences_.size(), false);
    for (int i = 0; i < sentences.size(); ++i) {
      const auto &sentence = sentences[i];
      for (const auto &word : sentence.words) {
        if (word.type == Type::VAR) {
          adj_[word.val].push_back(i);
        }
      }
      if (sentence.nVar == 1) {
        queue_.push(i);
        visited_[i] = true;
      }
    }
  }

public:
  auto solve(const std::vector<std::string> &inputStrs) {
    for (auto &s : inputStrs) {
      std::vector<std::string> tokens;
      boost::split(tokens, s, boost::is_any_of(" "));
      sentences_.push_back(preprocess(tokens));
    }
    buildGraph(sentences_);
    while (!queue_.empty()) {
      auto u = queue_.front();
      queue_.pop();
      const auto &sentence = sentences_[u];
      const auto &dest = sentence.words.back().val;
      if (sentence.words.size() == 3) {
        const auto &a = sentence.words.front();
        auto valA = (a.type == Type::VAL) ? std::stoi(a.val) : valMap_[a.val];
        valMap_[dest] = a.negate ? (~valA) : valA;
      } else {
        const auto &a = sentence.words[0];
        const auto &b = sentence.words[2];
        auto valA = (a.type == Type::VAL) ? std::stoi(a.val) : valMap_[a.val];
        valA = a.negate ? ~valA : valA;
        auto valB = (b.type == Type::VAL) ? std::stoi(b.val) : valMap_[b.val];
        valB = b.negate ? ~valB : valB;

        const auto &op = sentence.words[1];
        // Too lazy now :(
        if (op.val == "AND") {
          valMap_[dest] = valA & valB;
        } else if (op.val == "OR") {
          valMap_[dest] = valA | valB;
        } else if (op.val == "LSHIFT") {
          valMap_[dest] = valA << valB;
        } else {
          valMap_[dest] = valA >> valB;
        }
      }
      for (auto i : adj_[dest]) {
        sentences_[i].nVar--;
        if (!visited_[i] && sentences_[i].nVar == 1) {
          visited_[i] = true;
          queue_.push(i);
        }
      }
    }
    return valMap_["a"];
  }
};

int main() {
  std::ifstream in("../day07_input.txt");
  std::string s;
  std::vector<std::string> inputStrs;
  while (std::getline(in, s)) {
    inputStrs.push_back(std::move(s));
  }
  Circuit c;
  std::cerr << c.solve(inputStrs);
  return 0;
}