#include "JackTokenizer.h"
#include "const.h"

#include <iostream>
#include <fstream>

Token* JackTokenizer::tokenize(char *p)
{
    Token* head = new Token();
    Token* cur = head;

    while (*p) {
        // skip whitespace
        if (isspace(*p)) {
            p++;
            continue;
        }
        
        // symbol
        if (symbols.count(*p)) {
            std::string symbol;
            if (*p == '<') {
                symbol = "&lt;";
            }
            else if (*p == '>') {
                symbol = "&gt;";
            }
            else if (*p == '"') {
                symbol = "&quot;";
            }
            else if (*p == '&') {
                symbol = "&amp;";
            }
            else {
                symbol = std::string(1, *p);
            }
            cur->next = new Token(SYMBOL, nullptr, symbol);
            cur = cur->next;
            p++;
            continue;
        }

        // integer constant
        if (isdigit(*p)) {
            char* start = p;
            while (isdigit(*p)) p++;
            cur->next = new Token(INT_CONST, nullptr, std::string(start, p - start));
            cur = cur->next;
            continue;
        }

        // string constant
        if (*p == '"') {
            p++;
            char* start = p;
            while (*p != '"' && *p) p++;
            cur->next = new Token(STRING_CONST, nullptr, std::string(start, p - start));
            cur = cur->next;
            if (*p == '"') p++;
            continue;
        }

        // keyword and identifier
        if (isalpha(*p) || *p == '_') {
            char* start = p;
            while (isalnum(*p) || *p == '_') p++;
            std::string word(start, p - start);
            if (keywords.count(word)) {
                cur->next = new Token(KEYWORD, nullptr, word);
            }
            else {
                cur->next = new Token(IDENTIFIER, nullptr, word);
            }
            cur = cur->next;
            continue;
        }

        std::cerr << "Invalid character found." << std::endl;
        delete head;
        return nullptr;
    }

    cur->next = new Token(TK_EOF, nullptr, "");
    return head->next;
}

void JackTokenizer::compile(std::ofstream& output, Token* head)
{
    output << "<tokens>\n";

    while (head->type != TK_EOF) {
        output << "<" << types.at(head->type) << ">" << getToken(head) << "</" << types.at(head->type) << ">\n";
        head = head->next;
    }

    output << "</tokens>\n";
}

std::string JackTokenizer::getToken(Token* token)
{
    switch (token->type) {
    case KEYWORD:
        return token->keyword;
    case SYMBOL:
        return token->symbol;
    case IDENTIFIER:
        return token->identifier;
    case INT_CONST:
        return std::to_string(token->value);
    case STRING_CONST:
        return token->str;
    }

    return std::string();
}