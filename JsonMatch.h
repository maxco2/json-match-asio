#pragma once
#include <utility>
#include <cctype>
#include <stack>
#include <map>
#include <cstring>
#include <boost/asio/read_until.hpp>
#include <boost/type_traits.hpp>




class JsonMatch
{
public:
	enum class json_symbols {
		//terminal
		STR,
		NUM,
		NUL,
		BOOLEAN,
		COMMA,
		LEFT_BRACT,
		RIGHT_BRACT,
		LEFT_CURLY,
		RIGHT_CURLY,
		COLON,
		JSON_ERROR,
		LEXING,

		//non-terminal
		S,
		ARRAY,
		OBJECT,
		VALUES,
		NON_EMPTY_VALUES,
		ADDITITON_VALUES,
		MEMBERS,
		NON_EMPTY_MEMBERS,
		ADDITITON_MEMBERS,
		MEMBER,
		VALUE,
		END
	};

	void prettyPrintSymbol(json_symbols j)
	{
		switch (j)
		{
		case JsonMatch::json_symbols::STR:
			std::cout << "STR";
			break;
		case JsonMatch::json_symbols::NUM:
			std::cout << "NUM";
			break;
		case JsonMatch::json_symbols::NUL:
			std::cout << "NUL";
			break;
		case JsonMatch::json_symbols::BOOLEAN:
			std::cout << "BOOLEAN";
			break;
		case JsonMatch::json_symbols::COMMA:
			std::cout << "COMMA";
			break;
		case JsonMatch::json_symbols::LEFT_BRACT:
			std::cout << "LEFT_BRACT";
			break;
		case JsonMatch::json_symbols::RIGHT_BRACT:
			std::cout << "RIGHT_BRACT";
			break;
		case JsonMatch::json_symbols::LEFT_CURLY:
			std::cout << "LEFT_CURLY";
			break;
		case JsonMatch::json_symbols::RIGHT_CURLY:
			std::cout << "RIGHT_CURLY";
			break;
		case JsonMatch::json_symbols::COLON:
			std::cout << "COLON";
			break;
		case JsonMatch::json_symbols::JSON_ERROR:
			std::cout << "JSON_ERROR";
			break;
		case JsonMatch::json_symbols::LEXING:
			std::cout << "LEXING"; break;
		case JsonMatch::json_symbols::S:
			std::cout << "S"; break;
		case JsonMatch::json_symbols::ARRAY:
			std::cout << "ARRAY"; break;
		case JsonMatch::json_symbols::OBJECT:
			std::cout << "OBJECT"; break;
		case JsonMatch::json_symbols::VALUES:
			std::cout << "VALUES"; break;
		case JsonMatch::json_symbols::NON_EMPTY_VALUES:
			std::cout << "NON_EMPTY_VALUES"; break;
		case JsonMatch::json_symbols::ADDITITON_VALUES:
			std::cout << "ADDITITON_VALUES"; break;
		case JsonMatch::json_symbols::MEMBERS:
			std::cout << "MEMBERS"; break;
		case JsonMatch::json_symbols::NON_EMPTY_MEMBERS:
			std::cout << "NON_EMPTY_MEMBERS"; break;
		case JsonMatch::json_symbols::ADDITITON_MEMBERS:
			std::cout << "ADDITITON_MEMBERS"; break;
		case JsonMatch::json_symbols::MEMBER:
			std::cout << "MEMBER"; break;
		case JsonMatch::json_symbols::VALUE:
			std::cout << "VALUE"; break;
		case JsonMatch::json_symbols::END:
			std::cout << "END"; break;
		default:
			break;
		}
	}
#endif
	std::stack<json_symbols> stack_;
	std::map<json_symbols, std::map<json_symbols, int>> parseTable_;

	JsonMatch()
	{
		stack_.emplace(json_symbols::END);
		stack_.emplace(json_symbols::S);
		parseTable_[json_symbols::S][json_symbols::LEFT_BRACT] = 1;
		parseTable_[json_symbols::S][json_symbols::LEFT_CURLY] = 2;
		parseTable_[json_symbols::ARRAY][json_symbols::LEFT_BRACT] = 3;
		parseTable_[json_symbols::OBJECT][json_symbols::LEFT_CURLY] = 4;
		parseTable_[json_symbols::VALUES][json_symbols::STR] = 5;
		parseTable_[json_symbols::VALUES][json_symbols::NUM] = 5;
		parseTable_[json_symbols::VALUES][json_symbols::NUL] = 5;
		parseTable_[json_symbols::VALUES][json_symbols::BOOLEAN] = 5;
		parseTable_[json_symbols::VALUES][json_symbols::LEFT_CURLY] = 5;
		parseTable_[json_symbols::VALUES][json_symbols::LEFT_BRACT] = 5;

		parseTable_[json_symbols::VALUES][json_symbols::COMMA] = 6;
		parseTable_[json_symbols::VALUES][json_symbols::RIGHT_BRACT] = 6;
		parseTable_[json_symbols::VALUES][json_symbols::RIGHT_CURLY] = 6;
		parseTable_[json_symbols::VALUES][json_symbols::COLON] = 6;

		parseTable_[json_symbols::NON_EMPTY_VALUES][json_symbols::STR] = 7;
		parseTable_[json_symbols::NON_EMPTY_VALUES][json_symbols::NUM] = 7;
		parseTable_[json_symbols::NON_EMPTY_VALUES][json_symbols::NUL] = 7;
		parseTable_[json_symbols::NON_EMPTY_VALUES][json_symbols::BOOLEAN] = 7;
		parseTable_[json_symbols::NON_EMPTY_VALUES][json_symbols::LEFT_BRACT] = 7;
		parseTable_[json_symbols::NON_EMPTY_VALUES][json_symbols::LEFT_CURLY] = 7;

		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::NUM] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::NUL] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::BOOLEAN] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::LEFT_BRACT] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::RIGHT_BRACT] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::LEFT_CURLY] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::RIGHT_CURLY] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::COLON] = 8;
		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::STR] = 8;

		parseTable_[json_symbols::ADDITITON_VALUES][json_symbols::COMMA] = 9;
		parseTable_[json_symbols::MEMBERS][json_symbols::STR] = 10;

		parseTable_[json_symbols::MEMBERS][json_symbols::NUM] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::NUL] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::BOOLEAN] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::COMMA] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::LEFT_BRACT] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::RIGHT_BRACT] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::LEFT_CURLY] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::RIGHT_CURLY] = 11;
		parseTable_[json_symbols::MEMBERS][json_symbols::COLON] = 11;

		parseTable_[json_symbols::NON_EMPTY_MEMBERS][json_symbols::STR] = 12;

		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::NUM] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::NUL] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::BOOLEAN] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::LEFT_BRACT] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::RIGHT_BRACT] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::LEFT_CURLY] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::RIGHT_CURLY] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::COLON] = 13;
		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::STR] = 13;


		parseTable_[json_symbols::ADDITITON_MEMBERS][json_symbols::COMMA] = 14;
		parseTable_[json_symbols::MEMBER][json_symbols::STR] = 15;
		parseTable_[json_symbols::VALUE][json_symbols::STR] = 16;
		parseTable_[json_symbols::VALUE][json_symbols::NUM] = 17;
		parseTable_[json_symbols::VALUE][json_symbols::NUL] = 18;
		parseTable_[json_symbols::VALUE][json_symbols::BOOLEAN] = 19;
		parseTable_[json_symbols::VALUE][json_symbols::LEFT_CURLY] = 20;
		parseTable_[json_symbols::VALUE][json_symbols::LEFT_BRACT] = 21;
	}

	void clean_stack()
	{
		while (!stack_.empty())
		{
			stack_.pop();
		}
		stack_.emplace(json_symbols::END);
		stack_.emplace(json_symbols::S);
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lex_num(Iterator begin, Iterator end)
	{
		enum class state {
			SIGN,
			INTGRAL_PART,
			ZERO_INTGRAL_PART, NON_ZERO_INTGRAL_PART_2,
			RADIX_DIGIT,
			E_SIGN,
			E_DIGIT
		};
		auto start = begin;
		state s = state::SIGN;
		while (begin != end)
		{
			switch (s)
			{
			case state::SIGN:
				switch (*begin)
				{
				case '-':
					s = state::INTGRAL_PART;
					break;
				case '0':
					s = state::ZERO_INTGRAL_PART;
					break;
				default:
					if (*begin >= '1' && *begin <= '9')
					{
						s = state::NON_ZERO_INTGRAL_PART_2;
						break;
					}
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case state::INTGRAL_PART:
				switch (*begin)
				{
				case '0':
					s = state::ZERO_INTGRAL_PART;
					break;
				default:
					if (*begin >= '1' && *begin <= '9')
					{
						s = state::NON_ZERO_INTGRAL_PART_2;
						break;
					}
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case state::ZERO_INTGRAL_PART:
				switch (*begin)
				{
				case '.':
					s = state::RADIX_DIGIT;
					break;
				case 'e':
				case 'E':
					s = state::E_SIGN;
					break;
				default:
					break;
				}
				break;
			case state::NON_ZERO_INTGRAL_PART_2:
				switch (*begin)
				{
				case '.':
					s = state::RADIX_DIGIT;
					break;
				case 'e':
				case 'E':
					s = state::E_SIGN;
					break;
				default:
					if (std::isalnum(*begin))
					{
						s = state::NON_ZERO_INTGRAL_PART_2;
						break;
					}
					return{ --begin,json_symbols::NUM };
				}
				break;
			case state::RADIX_DIGIT:
				switch (*begin)
				{
				case 'e':
				case 'E':
					s = state::E_SIGN;
					break;
				default:
					if (std::isalnum(*begin))
					{
						break;
					}
					return{ --begin,json_symbols::NUM };
				}
				break;
			case state::E_SIGN:
				switch (*begin)
				{
				case '+':
				case '-':
					s = state::E_DIGIT;
					break;
				default:
					if (std::isalnum(*begin))
					{
						s = state::E_DIGIT;
						break;
					}
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case state::E_DIGIT:
				if (std::isalnum(*begin))
				{
					break;
				}
				else
				{
					return{ --begin,json_symbols::NUM };
				}
				break;
			default:
				break;
			}
			++begin;
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lex_true(Iterator begin, Iterator end)
	{
		enum state { T, R, U, E };
		auto start = begin;
		state s = T;
		while (begin != end)
		{
			switch (s)
			{
			case T:
				switch (*begin)
				{
				case 't':
					s = R;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case R:
				switch (*begin)
				{
				case 'r':
					s = U;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case U:
				switch (*begin)
				{
				case 'u':
					s = E;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case E:
				switch (*begin)
				{
				case 'e':
					return{ begin,json_symbols::BOOLEAN };
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			default:
				return{ begin,json_symbols::JSON_ERROR };
			}
			++begin;
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lex_false(Iterator begin, Iterator end)
	{
		enum state { F, A, L, S, E };
		auto start = begin;
		state s = F;
		while (begin != end)
		{
			switch (s)
			{
			case F:
				switch (*begin)
				{
				case 'f':
					s = A;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case A:
				switch (*begin)
				{
				case 'a':
					s = L;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case L:
				switch (*begin)
				{
				case 'l':
					s = S;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case S:
				switch (*begin)
				{
				case 's':
					s = E;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case E:
				switch (*begin)
				{
				case 'e':
					return{ begin,json_symbols::BOOLEAN };
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			default:
				return{ begin,json_symbols::JSON_ERROR };
			}
			++begin;
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lex_boolean(Iterator begin, Iterator end)
	{
		auto start = begin;
		while (begin != end)
		{
			switch (*begin)
			{
			case 't':
				return lex_true(begin, end);
			case 'f':
				return lex_false(begin, end);
			default:
				return{ begin,json_symbols::JSON_ERROR };
			}
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lex_string(Iterator begin, Iterator end)
	{
		auto start = begin;
		enum state { START, ESCAPE, NORMAL, HEX };
		state s = START;
		auto hexCount = 0;
		while (begin != end)
		{
			switch (s)
			{
			case START:
				switch (*begin)
				{
				case '"':
					s = NORMAL;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case ESCAPE:
				switch (*begin)
				{
				case '"':
				case '\\':
				case '/':
				case 'b':
				case 't':
				case 'f':
				case 'n':
				case 'r':
					s = NORMAL;
					break;
				case 'u':
					s = HEX;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case NORMAL:
				switch (*begin)
				{
				case '\\':
					s = ESCAPE;
					break;
				case '"':
					return{ begin,json_symbols::STR };
				default:
					break;
				}
				break;
			case HEX:
				if ((*begin >= 'a' && *begin <= 'f')
					|| (*begin >= 'A' && *begin <= 'F')
					|| std::isalnum(*begin)
					)
				{
					hexCount += 1;
					if (hexCount == 4)
					{
						s = NORMAL;
						hexCount = 0;
					}
				}
				else
					return{ begin,json_symbols::JSON_ERROR };
				break;
			default:
				break;
			}
			++begin;
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lex_null(Iterator begin, Iterator end)
	{
		enum state { N, U, L_1, L_2 };
		auto start = begin;
		state s = N;
		while (begin != end)
		{
			switch (s)
			{
			case N:
				switch (*begin)
				{
				case 'n':
					s = U;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case U:
				switch (*begin)
				{
				case 'u':
					s = L_1;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case L_1:
				switch (*begin)
				{
				case 'l':
					s = L_2;
					break;
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			case L_2:
				switch (*begin)
				{
				case 'l':
					return{ begin,json_symbols::NUL };
				default:
					return{ begin,json_symbols::JSON_ERROR };
				}
				break;
			default:
				return{ begin,json_symbols::JSON_ERROR };
			}
			++begin;
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, json_symbols> lexer(Iterator begin, Iterator end)
	{
		auto start = begin;
		while (begin != end)
		{
			switch (*begin)
			{
			case '[':
				return{ begin,json_symbols::LEFT_BRACT };
			case ']':
				return{ begin,json_symbols::RIGHT_BRACT };
			case '{':
				return{ begin,json_symbols::LEFT_CURLY };
			case '}':
				return{ begin,json_symbols::RIGHT_CURLY };
			case ',':
				return{ begin,json_symbols::COMMA };
			case ':':
				return{ begin,json_symbols::COLON };
			case '-':
				return{ begin,json_symbols::NUM };
			case '"':
				return lex_string(begin, end);
			case 'n':
				return lex_null(begin, end);
			case 't':
				return lex_boolean(begin, end);
			case 'f':
				return lex_boolean(begin, end);
			default:
				if (std::isalnum(*begin))
					return lex_num(begin, end);
				else if (std::isspace(*begin))
				{
					break;
				}
				return{ start,json_symbols::JSON_ERROR };
			}
			++begin;
		}
		return{ start,json_symbols::LEXING };
	}

	template<typename Iterator>
	std::pair<Iterator, bool> parse(Iterator begin, Iterator end)
	{
		std::pair<Iterator, json_symbols> lexResult;
		if (begin != end)
		{
			lexResult = lexer(begin, end);
			begin = lexResult.first;
		}
		while (begin != end)
		{
			if (stack_.top() == json_symbols::END)
			{
				clean_stack();
				return{ begin,true };
			}
			else if (stack_.top() == lexResult.second)
			{
				stack_.pop();
				++begin;
				lexResult = lexer(begin, end);
				if (lexResult.second == json_symbols::JSON_ERROR)
				{
					return{ lexResult.first,false };
				}
				begin = lexResult.first;
			}
			else
			{
				switch (parseTable_[stack_.top()][lexResult.second])
				{
				case 1:
					stack_.pop();
					stack_.emplace(json_symbols::ARRAY);
					break;
				case 2:
					stack_.pop();
					stack_.emplace(json_symbols::OBJECT);
					break;
				case 3:
					stack_.pop();
					stack_.emplace(json_symbols::RIGHT_BRACT);
					stack_.emplace(json_symbols::VALUES);
					stack_.emplace(json_symbols::LEFT_BRACT);
					break;
				case 4:
					stack_.pop();
					stack_.emplace(json_symbols::RIGHT_CURLY);
					stack_.emplace(json_symbols::MEMBERS);
					stack_.emplace(json_symbols::LEFT_CURLY);
					break;
				case 5:
					stack_.pop();
					stack_.emplace(json_symbols::NON_EMPTY_VALUES);
					break;
				case 6:
					stack_.pop();
					break;
				case 7:
					stack_.pop();
					stack_.emplace(json_symbols::ADDITITON_VALUES);
					stack_.emplace(json_symbols::VALUE);
					break;
				case 8:
					stack_.pop();
					break;
				case 9:
					stack_.pop();
					stack_.emplace(json_symbols::NON_EMPTY_VALUES);
					stack_.emplace(json_symbols::COMMA);
					break;
				case 10:
					stack_.pop();
					stack_.emplace(json_symbols::NON_EMPTY_MEMBERS);
					break;
				case 11:
					stack_.pop();
					break;
				case 12:
					stack_.pop();
					stack_.emplace(json_symbols::ADDITITON_MEMBERS);
					stack_.emplace(json_symbols::MEMBER);
					break;
				case 13:
					stack_.pop();
					break;
				case 14:
					stack_.pop();
					stack_.emplace(json_symbols::NON_EMPTY_MEMBERS);
					stack_.emplace(json_symbols::COMMA);
					break;
				case 15:
					stack_.pop();
					stack_.emplace(json_symbols::VALUE);
					stack_.emplace(json_symbols::COLON);
					stack_.emplace(json_symbols::STR);
					break;
				case 16:
					stack_.pop();
					stack_.emplace(json_symbols::STR);
					break;
				case 17:
					stack_.pop();
					stack_.emplace(json_symbols::NUM);
					break;
				case 18:
					stack_.pop();
					stack_.emplace(json_symbols::NUL);
					break;
				case 19:
					stack_.pop();
					stack_.emplace(json_symbols::BOOLEAN);
					break;
				case 20:
					stack_.pop();
					stack_.emplace(json_symbols::OBJECT);
					break;
				case 21:
					stack_.pop();
					stack_.emplace(json_symbols::ARRAY);
					break;
				default:
					return{ lexResult.first,false };
					/*error*/
					break;
				}
			}
		}
		if (stack_.top() == json_symbols::END)
		{
			clean_stack();
			return{ begin,true };
		}
		clean_stack();
		return{ lexResult.first,false };
	}

	template <typename Iterator>
	std::pair<Iterator, bool> operator()(
		Iterator begin, Iterator end)
	{
		return parse(begin, end);
	}

};
namespace boost
{
	namespace asio 
	{
		template <> struct is_match_condition<JsonMatch>
			: public boost::true_type {};
	} 
}