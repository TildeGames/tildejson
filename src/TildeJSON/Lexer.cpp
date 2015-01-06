#include <TildeJSON/Lexer.hpp>

char Lexer::ch = ' ';
int  Lexer::sym = -1;
float Lexer::num = 0;
std::string Lexer::str = "";
std::map<std::string,int> Lexer::symbols;

void Lexer::init()
{
	Lexer::symbols["true"]  = Lexer::STRUE;
	Lexer::symbols["false"] = Lexer::SFALSE;
	Lexer::symbols["null"]  = Lexer::SNULL;
}

void Lexer::next_ch()
{
	ch = std::cin.get();
}

void Lexer::syntax_error()
{
	std::cerr << "Syntax error" << std::endl;
	exit(1);
}

void Lexer::next_sym()
{
		while (ch == ' ' || ch == '\n' || ch == '\t')
			next_ch();

		switch (ch)
		{
			case '{': sym = LBRACE;   next_ch(); break;
			case '}': sym = RBRACE;   next_ch(); break;
			case '[': sym = LBRACKET; next_ch(); break;
			case ']': sym = RBRACKET; next_ch(); break;
			case ':': sym = COLON;    next_ch(); break;
			case ',': sym = COMMA;    next_ch(); break;
			case EOF: sym = EOI;      next_ch(); break;
			// STRING, NUMBER, STRUE, SFALSE, SNULL
			default:
			{
				// NUMBER
				if ((ch >= '0' && ch <= '9') || ch == '-')
				{
					bool neg = false;
					if (ch == '-')
					{
						neg = true;
						next_ch();
					}
					// To prevent only '-'
					if (ch < '0' || ch > '9')
						syntax_error();

					// TODO : only int for now
					num = 0;
					while (ch >= '0' && ch <= '9')
					{
						num = num*10 + (ch - '0');
						next_ch();
					}

					sym = NUMBER;
				}
				// STRING
				else if (ch == '\"')
				{
					std::stringstream ss;
					next_ch();
					while (ch != '\"') // TODO: fin prématurée (EOF,...?) et symboles échappés
					{
						ss << ch;
						next_ch();
					}

					next_ch();
					sym = STRING;
					str = ss.str();
				}
				// SYMBOLS
				else if (ch >= 'a' && ch <= 'z')
				{
					std::stringstream ss;

					while (ch >= 'a' && ch <= 'z')
					{
						ss << ch;
						next_ch();
					}

					if (symbols.count(ss.str()) == 1)
						sym = symbols[ss.str()];
					else
						syntax_error();
				}
				// SYNTAX ERROR
				else
					syntax_error();
			}
		}
	}