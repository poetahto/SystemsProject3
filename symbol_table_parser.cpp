#include <string>
#include <fstream>
#include <vector>
#include "types.hpp"
#include "string_parsing_tools.hpp"

// Extracts symbol and literal information from a symbol table file.
bool parseSymbolTableFile(const std::string& fileName, SymbolTableData& outData)
{
    std::ifstream symbolFileStream {fileName};
    std::string line {};

    // Extract all symbols
    {
        auto* symbols = new std::vector<Symbol>();

        // Skip the header
        std::getline(symbolFileStream, line);
        std::getline(symbolFileStream, line);

        while (std::getline(symbolFileStream, line))
        {
            bool failure {false};

            Symbol symbol {};
            StringParsingTools::tryGetArg(line, 0, &symbol.name);
            failure |= !StringParsingTools::tryGetArg(line, 1, &symbol.addressHex);
            failure |= !StringParsingTools::tryGetArg(line, 2, &symbol.flags);
            failure |= !StringParsingTools::tryGetInt(symbol.addressHex, symbol.addressValue);

            if (failure)
                break;

            symbols->emplace_back(symbol);
        }

        outData.symbolCount = symbols->size();
        outData.symbols = symbols->data();
    }

    // Extract all the constants and literals
    {
        auto* constants = new std::vector<Constant>();
        auto* literals = new std::vector<Literal>();

        // Skip the header
        std::getline(symbolFileStream, line);
        std::getline(symbolFileStream, line);

        while (std::getline(symbolFileStream, line))
        {
            bool failure {false};

            std::string value {};
            StringParsingTools::tryGetArg(line, 1, &value);

            if (value[0] == '=') { // we have a literal
                Literal literal {};
                literal.value = value;
                StringParsingTools::tryGetArg(line, 2, &literal.lengthHex);
                failure |= !StringParsingTools::tryGetArg(line, 3, &literal.addressHex);
                failure |= !StringParsingTools::tryGetInt(literal.addressHex, literal.addressValue);
                failure |= !StringParsingTools::tryGetInt(literal.lengthHex, literal.lengthValue);

                if (failure) {
                    break;
                }
                literals->emplace_back(literal);
            }
            else { // we have a constant
                Constant constant {};
                constant.value = value;
                StringParsingTools::tryGetArg(line, 0, &constant.name);
                failure |= !StringParsingTools::tryGetArg(line, 2, &constant.lengthHex);
                failure |= !StringParsingTools::tryGetArg(line, 3, &constant.addressHex);
                failure |= !StringParsingTools::tryGetInt(constant.addressHex, constant.addressValue);
                failure |= !StringParsingTools::tryGetInt(constant.lengthHex, constant.lengthValue);

                if (failure) {
                    break;
                }
                constants->emplace_back(constant);
            }
        }

        outData.constantCount = constants->size();
        outData.constants = constants->data();

        outData.literalCount = literals->size();
        outData.literals = literals->data();
    }

    return true;
}
