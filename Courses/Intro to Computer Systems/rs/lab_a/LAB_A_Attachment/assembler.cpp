#include "assembler.h"

void label_map_tp::AddLabel(const std::string &str, const value_tp &val) {
  labels_.insert({str, val});
}

value_tp label_map_tp::GetValue(const std::string &str) const {
  return labels_.find(str) == labels_.end() ? value_tp(vAddress, -1)
                                            : labels_.at(str);
}

std::ostream &operator<<(std::ostream &os, const StringType &item) {
  switch (item) {
    case sComment:
      os << "Comment ";
      break;
    case sLabel:
      os << "Label";
      break;
    case sValue:
      os << "Value";
      break;
    case sOpcode:
      os << "Opcode";
      break;
    case sOperand:
      os << "Operand";
      break;
    default:
      os << "Error";
      break;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const ValueType &val) {
  switch (val) {
    case vAddress:
      os << "Address";
      break;
    case vValue:
      os << "Value";
      break;
    default:
      os << "Error";
      break;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const value_tp &value) {
  if (value.type_ == vValue)
    os << "[ " << value.type_ << " -- " << value.val_ << " ]";
  else
    os << "[ " << value.type_ << " -- " << std::hex << "0x" << value.val_
       << " ]";
  return os;
}

std::ostream &operator<<(std::ostream &os, const label_map_tp &label_map) {
  for (auto item : label_map.labels_)
    os << "Name: " << item.first << " " << item.second << std::endl;
  return os;
}

std::string assembler::TranslateOperand(int current_address,
                                        const std::string &str,
                                        int opcode_length) {
  int val;
  auto item = label_map.GetValue(str);
  if (item.getVal() != -1) {
    val = item.getVal() - current_address - 1;
    return -val > 1 << opcode_length - 1 || val + 1 > 1 << opcode_length - 1
               ? ""
               : NumberToAssemble(val).substr(16 - opcode_length);
  }
  if (str[0] == 'R') {
    val = std::stoi(str.substr(1));
    return val < 0 || val > 7
               ? ""
               : NumberToAssemble(val).substr(16 - opcode_length);
  }
  val = RecognizeNumberValue(str);
  return -val > 1 << opcode_length - 1 || val + 1 > 1 << opcode_length - 1
             ? ""
             : NumberToAssemble(val).substr(16 - opcode_length);
}

int assembler::assemble(const std::string &input_filename,
                        std::string &output_filename) {
  std::vector<std::string> file_content;
  std::vector<std::string> origin_file;
  std::vector<LineStatusType> file_tag;
  std::vector<std::string> file_comment;
  std::vector<int> file_address;
  int orig_address = -1;
  std::string line;
  std::ifstream input_file(input_filename);
  if (!input_file.is_open()) {
    if (gIsErrorLogMode)
      std::cout << "Unable to open file: " << input_filename << std::endl;
    return -1;
  }
  // Scan 0
  while (std::getline(input_file, line)) {
    origin_file.push_back(line);
    file_address.push_back(-1);
    std::transform(line.begin(), line.end(), line.begin(), ::toupper);
    auto comment_position = line.find(";");
    if (comment_position == std::string::npos) {
      file_content.push_back(line);
      file_comment.push_back("");
      Trim(line);
      file_tag.push_back(line.empty() ? lComment : lPending);
    } else {
      auto comment_str = line.substr(comment_position);
      auto content_str = line.substr(0, comment_position);
      file_content.push_back(content_str);
      file_comment.push_back(comment_str);
      Trim(content_str);
      file_tag.push_back(content_str.empty() ? lComment : lPending);
    }
  }
  // Scan 1
  int line_address = -1;
  for (int line_index = 0; line_index < file_content.size(); ++line_index) {
    if (file_tag[line_index] == lComment) continue;
    auto line = file_content[line_index];
    auto line_stringstream = std::stringstream(line);
    std::string word;
    line_stringstream >> word;
    if (word == ".ORIG") {
      if (line_address == -1) {
        file_tag[line_index] = lPseudo;
        line_stringstream >> word;
        orig_address = RecognizeNumberValue(word);
        if (orig_address == std::numeric_limits<int>::max()) {
          if (gIsErrorLogMode)
            std::cout << "Invalid address at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -2;
        }
        file_address[line_index] = -1;
        line_address = orig_address;
        continue;
      } else {
        if (gIsErrorLogMode)
          std::cout << "Invalid .ORIG at line " << line_index << ": "
                    << origin_file[line_index] << std::endl;
        return -666;
      }
    } else if (line_address == -1) {
      if (gIsErrorLogMode)
        std::cout << "Program begins before .ORIG at line " << line_index
                  << ": " << origin_file[line_index] << std::endl;
      return -3;
    }
    if (word[0] == '.') {
      file_tag[line_index] = lPseudo;
      if (word == ".END")
        file_address[line_index] = line_address = -1;
      else if (word == ".STRINGZ") {
        std::getline(line_stringstream >> std::ws, word);
        if (word[0] != '\"' || word[word.size() - 1] != '\"') {
          if (gIsErrorLogMode)
            std::cout << "String format error at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -6;
        }
        file_address[line_index] = line_address;
        line_address += word.size() - 1;
      } else if (word == ".FILL") {
        line_stringstream >> word;
        auto num_temp = RecognizeNumberValue(word);
        if (num_temp == std::numeric_limits<int>::max()) {
          if (gIsErrorLogMode)
            std::cout << "Invalid number input at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -4;
        }
        if (num_temp > 65535 || num_temp < -65536) {
          if (gIsErrorLogMode)
            std::cout << "Too large or too small value at line " << line_index
                      << ": " << origin_file[line_index] << std::endl;
          return -5;
        }
        file_address[line_index] = line_address++;
      } else if (word == ".BLKW") {
        line_stringstream >> word;
        auto num_temp = RecognizeNumberValue(word);
        if (num_temp == std::numeric_limits<int>::max()) {
          if (gIsErrorLogMode)
            std::cout << "Invalid number input at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -4;
        }
        file_address[line_index] = line_address;
        line_address += num_temp;
      } else {
        if (gIsErrorLogMode)
          std::cout << "Unknown pseudo command at line " << line_index << ": "
                    << origin_file[line_index] << std::endl;
        return -100;
      }
      continue;
    }
    if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1) {
      file_tag[line_index] = lOperation;
      file_address[line_index] = line_address++;
      continue;
    }
    label_map.AddLabel(word, value_tp(vAddress, line_address));
    line_stringstream >> word;
    if (word == ".ORIG" || word == ".END") {
      if (gIsErrorLogMode)
        std::cout << "Invalid label at line " << line_index << ": "
                  << origin_file[line_index] << std::endl;
      return -667;
    }
    if (word[0] == '.') {
      file_tag[line_index] = lPseudo;
      if (word == ".STRINGZ") {
        std::getline(line_stringstream >> std::ws, word);
        if (word[0] != '\"' || word[word.size() - 1] != '\"') {
          if (gIsErrorLogMode)
            std::cout << "String format error at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -6;
        }
        file_address[line_index] = line_address;
        line_address += word.size() - 1;
      } else if (word == ".FILL") {
        line_stringstream >> word;
        auto num_temp = RecognizeNumberValue(word);
        if (num_temp == std::numeric_limits<int>::max()) {
          if (gIsErrorLogMode)
            std::cout << "Invalid number input at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -4;
        }
        if (num_temp > 65535 || num_temp < -65536) {
          if (gIsErrorLogMode)
            std::cout << "Too large or too small value at line " << line_index
                      << ": " << origin_file[line_index] << std::endl;
          return -5;
        }
        file_address[line_index] = line_address++;
      } else if (word == ".BLKW") {
        line_stringstream >> word;
        auto num_temp = RecognizeNumberValue(word);
        if (num_temp == std::numeric_limits<int>::max()) {
          if (gIsErrorLogMode)
            std::cout << "Invalid number input at line " << line_index << ": "
                      << origin_file[line_index] << std::endl;
          return -4;
        }
        file_address[line_index] = line_address;
        line_address += num_temp;
      } else {
        if (gIsErrorLogMode)
          std::cout << "Unknown pseudo command at line " << line_index << ": "
                    << origin_file[line_index] << std::endl;
        return -100;
      }
      continue;
    }
    file_tag[line_index] = lOperation;
    file_address[line_index] = line_address++;
  }
  if (line_address != -1) {
    if (gIsErrorLogMode) std::cout << "Program ends before .END" << std::endl;
    return -668;
  }
  if (gIsDebugMode) {
    std::cout << std::endl
              << "Label Map: " << std::endl
              << label_map << std::endl;
    for (auto index = 0; index < file_content.size(); ++index)
      if (file_address[index] != -1)
        std::cout << std::hex << file_address[index] << " "
                  << file_content[index] << std::endl;
  }
  // Scan 2
  if (output_filename.empty()) {
    output_filename = input_filename;
    auto pos = output_filename.rfind(".");
    if (pos != std::string::npos)
      output_filename = output_filename.substr(0, pos);
    output_filename = output_filename + ".asm";
  }
  std::ofstream output_file(output_filename);
  if (!output_file.is_open()) {
    if (gIsErrorLogMode)
      std::cout << "Cannot open output file " << output_filename << std::endl;
    return -20;
  }
  for (int line_index = 0; line_index < file_content.size(); ++line_index) {
    if (file_address[line_index] == -1 || file_tag[line_index] == lComment)
      continue;
    if (gIsDebugMode)
      output_file << std::hex << file_address[line_index] << ": ";
    auto line = file_content[line_index];
    auto line_stringstream = std::stringstream(line);
    std::string word;
    line_stringstream >> word;
    if (file_tag[line_index] == lPseudo) {
      if (word[0] != '.') line_stringstream >> word;
      if (word == ".FILL") {
        line_stringstream >> word;
        auto output_line = NumberToAssemble(word);
        if (gIsHexMode) output_line = ConvertBin2Hex(output_line);
        output_file << output_line << std::endl;
      } else if (word == ".BLKW") {
        line_stringstream >> word;
        auto num_temp = RecognizeNumberValue(word);
        std::string output_line = gIsHexMode ? "0000" : "0000000000000000";
        for (int i = 0; i < num_temp; ++i)
          output_file << output_line << std::endl;
      } else if (word == ".STRINGZ") {
        std::getline(line_stringstream >> std::ws, word);
        for (int i = 1; i < word.size() - 1; ++i) {
          std::string output_line = NumberToAssemble(word[i]);
          if (gIsHexMode) output_line = ConvertBin2Hex(output_line);
          output_file << output_line << std::endl;
        }
        output_file << (gIsHexMode ? "0000" : "0000000000000000") << std::endl;
      }
      continue;
    }
    if (file_tag[line_index] == lOperation) {
      if (IsLC3Command(word) == -1 && IsLC3TrapRoutine(word) == -1)
        line_stringstream >> word;
      auto current_address = file_address[line_index];
      auto command_name = word;
      std::string parameter_str;
      std::getline(line_stringstream, parameter_str);
      std::replace(parameter_str.begin(), parameter_str.end(), ',', ' ');
      auto parameter_stream = std::stringstream(parameter_str);
      std::vector<std::string> parameter_list;
      while (parameter_stream >> word) parameter_list.push_back(word);
      auto parameter_list_size = parameter_list.size();
      std::string result_line;
      auto command_tag = IsLC3Command(command_name);
      if (command_tag != -1) {
        switch (command_tag) {
          case 0:
            // "ADD"
            if (parameter_list_size != 3) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "0001" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1]) +
                (parameter_list[2][0] == 'R' ? "0" : "1") +
                TranslateOperand(current_address, parameter_list[2], 5);
            break;
          case 1:
            // "AND"
            if (parameter_list_size != 3) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "0101" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1]) +
                (parameter_list[2][0] == 'R' ? "0" : "1") +
                TranslateOperand(current_address, parameter_list[2], 5);
            break;
          case 2:
            // "BR"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000111" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 3:
            // "BRN"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000100" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 4:
            // "BRZ"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000010" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 5:
            // "BRP"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000001" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 6:
            // "BRNZ"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000110" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 7:
            // "BRNP"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000101" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 8:
            // "BRZP"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000011" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 9:
            // "BRNZP"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0000111" + TranslateOperand(current_address,
                                                       parameter_list[0], 9);
            break;
          case 10:
            // "JMP"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "1100000" +
                          TranslateOperand(current_address, parameter_list[0]) +
                          "000000";
            break;
          case 11:
            // "JSR"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "01001" + TranslateOperand(current_address,
                                                     parameter_list[0], 11);
            break;
          case 12:
            // "JSRR"
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "0100000" +
                          TranslateOperand(current_address, parameter_list[0]) +
                          "000000";
            break;
          case 13:
            // "LD"
            if (parameter_list_size != 2) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "0010" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1], 9);
            break;
          case 14:
            // "LDI"
            if (parameter_list_size != 2) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "1010" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1], 9);
            break;
          case 15:
            // "LDR"
            if (parameter_list_size != 3) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "0110" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1]) +
                TranslateOperand(current_address, parameter_list[2], 6);
            break;
          case 16:
            // "LEA"
            if (parameter_list_size != 2) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "1110" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1], 9);
            break;
          case 17:
            // "NOT"
            if (parameter_list_size != 2) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "1001" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1]) + "111111";
            break;
          case 18:
            // RET
            if (parameter_list_size != 0) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "1100000111000000";
            break;
          case 19:
            // RTI
            if (parameter_list_size != 0) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "1000000000000000";
            break;
          case 20:
            // ST
            if (parameter_list_size != 2) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "0011" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1], 9);
            break;
          case 21:
            // STI
            if (parameter_list_size != 2) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "1011" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1], 9);
            break;
          case 22:
            // STR
            if (parameter_list_size != 3) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line =
                "0111" + TranslateOperand(current_address, parameter_list[0]) +
                TranslateOperand(current_address, parameter_list[1]) +
                TranslateOperand(current_address, parameter_list[2], 6);
            break;
          case 23:
            // TRAP
            if (parameter_list_size != 1) {
              if (gIsErrorLogMode)
                std::cout << "Parameter numbers error at line " << line_index
                          << ": " << origin_file[line_index] << std::endl;
              return -30;
            }
            result_line = "11110000" + TranslateOperand(current_address,
                                                        parameter_list[0], 8);
            break;
          default:
            if (gIsErrorLogMode)
              std::cout << "Unknown command at line " << line_index << ": "
                        << origin_file[line_index] << std::endl;
            return -50;
            break;
        }
      } else {
        command_tag = IsLC3TrapRoutine(command_name);
        switch (command_tag) {
          case 0:
            // x20
            result_line = "1111000000100000";
            break;
          case 1:
            // x21
            result_line = "1111000000100001";
            break;
          case 2:
            // x22
            result_line = "1111000000100010";
            break;
          case 3:
            // x23
            result_line = "1111000000100011";
            break;
          case 4:
            // x24
            result_line = "1111000000100100";
            break;
          case 5:
            // x25
            result_line = "1111000000100101";
            break;
          default:
            if (gIsErrorLogMode)
              std::cout << "Unknown command at line " << line_index << ": "
                        << origin_file[line_index] << std::endl;
            return -50;
            break;
        }
      }
      if (result_line.size() != 16) {
        if (gIsErrorLogMode)
          std::cout << "Invalid parameter at line " << line_index << ": "
                    << origin_file[line_index] << std::endl;
        return -669;
      }
      if (gIsHexMode) result_line = ConvertBin2Hex(result_line);
      output_file << result_line << std::endl;
    }
  }
  return 0;
}
