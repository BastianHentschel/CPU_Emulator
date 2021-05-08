//
// Created by basti on 08/05/2021.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include "main.h"

using namespace std;


void writeData(pair<Word, DATA_TYPE> parsed_value, ofstream &file);

pair<Word, DATA_TYPE> parseByteOrWord(string string1);;


int main(int argc, char *argv[]) {
    //Preparing files

    const char *filename;
    if (argc == 2) {
        filename = "out.bin";
    } else if (argc == 3) {
        filename = argv[2];
    } else {
        return 1;
    }
    ifstream input_file(argv[1]);;
    ofstream output_file(filename, ios::binary);

    mode = CODE;


    try {
        while (!input_file.eof()) {
            string token;
            input_file >> token;
            transform(token.begin(), token.end(), token.begin(), ::toupper);
            if (token.empty()) { //test for EOF (basically)
                break;
            }

            if (token == ".DATA") {
                mode = DATA;
                continue;
            } else if (token == ".CODE") {
                mode = CODE;
                continue;
            }

            if (mode == CODE) {
                if (token == "LDA") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(LDA_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(LDA_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(LDA_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "STA") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(STA);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(STA_REL);
                            break;
                        case IMMEDIATE:
                            throw invalid_argument("STX can't be immediate");
                    }
                    writeData(parsed, output_file);
                } else if (token == "PLA") {
                    output_file.put(PLA);
                } else if (token == "PHA") {
                    output_file.put(PHA);
                } else if (token == "INA") {
                    output_file.put(INA);
                } else if (token == "DEA") {
                    output_file.put(DEA);
                } else if (token == "CMP") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(CMP_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(CMP_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(CMP_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "LDX") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(LDX_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(LDX_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(LDX_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "STX") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(STX);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(STX_REL);
                            break;
                        case IMMEDIATE:
                            throw invalid_argument("STX can't be immediate");
                    }
                    writeData(parsed, output_file);
                } else if (token == "PLX") {
                    output_file.put(PLX);
                } else if (token == "PHX") {
                    output_file.put(PHX);
                } else if (token == "INX") {
                    output_file.put(INX);
                } else if (token == "DEX") {
                    output_file.put(DEX);
                } else if (token == "CMX") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(CMX_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(CMX_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(CMX_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "LDY") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(LDY_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(LDY_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(LDY_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "STY") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(STY);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(STY_REL);
                            break;
                        case IMMEDIATE:
                            throw invalid_argument("STX can't be immediate");
                    }
                    writeData(parsed, output_file);
                } else if (token == "PLY") {
                    output_file.put(PLY);
                } else if (token == "PHY") {
                    output_file.put(PHY);
                } else if (token == "INY") {
                    output_file.put(INY);
                } else if (token == "DEY") {
                    output_file.put(DEY);
                } else if (token == "CMY") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(CMY_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(CMY_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(CMY_REL);
                            break;

                    }
                    writeData(parsed, output_file);

                } else if (token == "INC") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(INC);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(INC_REL);
                            break;
                        case IMMEDIATE:
                            throw invalid_argument("INC can't be immediate.");
                    }
                    writeData(parsed, output_file);
                } else if (token == "DEC") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(DEC);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(DEC_REL);
                            break;
                        case IMMEDIATE:
                            throw invalid_argument("DEC can't be immediate.");
                    }
                    writeData(parsed, output_file);
                } else if (token == "ADD") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(ADD_ABS);
                            break;
                        case IMMEDIATE:
                            output_file.put(ADD_IMM);
                            break;
                        case VAR:
                            data_addresses[token].push_back((int) output_file.tellp() + 1);
                        case RELATIVE:
                            output_file.put(ADD_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "PRC") {
                    output_file.put(PRC);
                } else if (token == "PRD") {
                    output_file.put(PRD);
                } else if (token == "PRN") {
                    output_file.put(PRN);
                } else if (token == "PRH") {
                    output_file.put(PRH);
                } else if (token == "BEQ") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(BEQ_ABS);
                            break;
                        case VAR:
                            label_from_addresses[token].push_back((int) output_file.tellp() + 1);
                        case IMMEDIATE:
                            output_file.put(BEQ_IMM);
                            break;
                        case RELATIVE:
                            output_file.put(BEQ_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "BNE") {
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    switch (parsed.second) {
                        case ABSOLUTE:
                            output_file.put(BNE_ABS);
                            break;
                        case VAR:
                            label_from_addresses[token].push_back((int) output_file.tellp() + 1);
                        case IMMEDIATE:
                            output_file.flush();
                            output_file.put(BNE_IMM);
                            output_file.flush();
                            break;
                        case RELATIVE:
                            output_file.put(BNE_REL);
                            break;
                    }
                    writeData(parsed, output_file);
                } else if (token == "JMP") {
                    output_file.put(JMP);
                    input_file >> token;
                    auto parsed = parseByteOrWord(token);
                    writeData(parsed, output_file);
                } else if (token == "ZRO") {
                    output_file.put(ZRO);
                } else if (token == "STP") {
                    output_file.put(STP);
                } else if (token.back() == ':') {
                    label_addresses[token.substr(0, token.length() - 1)] = output_file.tellp();
                } else {
                    string error_msg = "Invalid Command: " + token;
                    throw invalid_argument(error_msg);
                }

            } else {
                string name = token;
                input_file >> token;
                auto parsed = parseByteOrWord(token);
                data_values[name] = parsed.first;
            }


        }

        for (const auto &name_value: data_values) {
            Byte data_pos = output_file.tellp();
            output_file.put(data_values[name_value.first]);
            for (Word address:data_addresses[name_value.first]) {
                output_file.seekp(address);
                output_file.put((char) (data_pos - address));
            }
            output_file.seekp(data_pos + 1);
        }

        for (const auto &label_address: label_addresses) {
            for (Word address:label_from_addresses[label_address.first]) {
                output_file.seekp(address);
                output_file.put((char) (label_address.second - address));
            }
        }

    } catch (invalid_argument e) {
        output_file.close();
        remove(filename);
        cerr << e.what();
        return 1;
    }
}

void writeData(pair<Word, DATA_TYPE> parsed_value, ofstream &file) {
    if (parsed_value.second == ABSOLUTE) {
        file.put(parsed_value.first >> 8);
    }
    file.put(parsed_value.first & 0xFF);
}

pair<Word, DATA_TYPE> parseByteOrWord(string string1) {
    DATA_TYPE type;
    if (find(LETTERS, LETTERS + 26, string1.front()) != LETTERS + 26) {
        return pair(0, VAR);
    }
    if (string1.front() == '[' && string1.back() == ']') {
        type = ABSOLUTE;
        string1 = string1.substr(1, string1.length() - 2);
    } else if (string1.front() == '&') {
        type = RELATIVE;
        string1 = string1.substr(1, string1.length() - 2);
    } else {
        type = IMMEDIATE;
    }
    return pair(stoi(string1, nullptr, 0), type);
}
