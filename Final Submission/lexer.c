// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include "lexer.h"
#include <string.h>
#include <stdlib.h>

int state = 0;
int fwdptr = 0;
int bwdptr = 0;
int line_no = 1;
int buffer_no = 1;
int retract = 0;
char buffer1[1024];
char buffer2[1024];
char lexeme[100];
char *ptr_strtod; // Declared for string to double function. 
int buffer_size; 


void ht_init(map mp)
{
    insert_hashtable(mp, "integer", "INTEGER");
    insert_hashtable(mp, "real", "REAL");
    insert_hashtable(mp, "boolean", "BOOLEAN");
    insert_hashtable(mp, "of", "OF");
    insert_hashtable(mp, "array", "ARRAY");
    insert_hashtable(mp, "start", "START");
    insert_hashtable(mp, "end", "END");
    insert_hashtable(mp, "declare", "DECLARE");
    insert_hashtable(mp, "module", "MODULE");
    insert_hashtable(mp, "driver", "DRIVER");
    insert_hashtable(mp, "program", "PROGRAM");
    insert_hashtable(mp, "get_value", "GET_VALUE");
    insert_hashtable(mp, "print", "PRINT");
    insert_hashtable(mp, "use", "USE");
    insert_hashtable(mp, "with", "WITH");
    insert_hashtable(mp, "parameters", "PARAMETERS");
    insert_hashtable(mp, "takes", "TAKES");
    insert_hashtable(mp, "input", "INPUT");
    insert_hashtable(mp, "returns", "RETURNS");
    insert_hashtable(mp, "for", "FOR");
    insert_hashtable(mp, "in", "IN");
    insert_hashtable(mp, "switch", "SWITCH");
    insert_hashtable(mp, "case", "CASE");
    insert_hashtable(mp, "break", "BREAK");
    insert_hashtable(mp, "default", "DEFAULT");
    insert_hashtable(mp, "while", "WHILE");
    insert_hashtable(mp, "AND", "AND");
    insert_hashtable(mp, "OR", "OR");
    insert_hashtable(mp, "true", "TRUE");
    insert_hashtable(mp, "false", "FALSE");
}

// custom function for obtaining substring of specific size
char *substring(int buffer_num, int ptr1, int size)
{
    char *k = (char *)malloc(size * sizeof(char));
    if (buffer_num == 1)
    {
        for (int i = 0; i < size; i++)
        {
            k[i] = buffer1[ptr1 + i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            k[i] = buffer2[ptr1 + i];
        }
    }
    return k;
}

// function for concatenating string
char *concat(char *ch1, int size1, char *ch2, int size2)
{
    char *ch = (char *)malloc((size1 + size2) * sizeof(char));
    int j = 0;
    for (int i = 0; i < size1; i++)
    {
        ch[j] = ch1[i];
        j++;
    }
    for (int i = 0; i < size2; i++)
    {
        ch[j] = ch2[i];
        j++;
    }
    return (char *)ch;
}

// Function for loading input in the buffer
void buffer_input(FILE *fptr)
{
    if (buffer_no == 1)
    {
        for (int i = 0; i < 1024; i++)
        {
            char c;
            if ((c = fgetc(fptr)) != EOF)
            {
                buffer1[i] = c;
            }
            else
            {
                buffer1[i] = EOF;
                break;
            }
        }
    }
    else if (buffer_no == 2)
    {
        for (int i = 0; i < 1024; i++)
        {
            char c;
            if ((c = fgetc(fptr)) != EOF)
            {
                buffer2[i] = c;
            }
            else
            {
                buffer2[i] = EOF;
                break;
            }
        }
    }
}

// Function for discarding extra input char read in the DFA
void discard()
{
    fwdptr--;
    if (fwdptr < 0)
    {
        retract = 1;
        fwdptr = 1023;
        if (buffer_no == 1)
            buffer_no = 2;
        else
            buffer_no = 1;
    }
    else if (fwdptr == 0)
    {
        retract = 1;
    }
}

// wrapper function to fill the buffer
void fill_buffer_int(FILE *fp)
{
    buffer_input(fp);
}

// Function to obatin a character from the buffer
char get_char(FILE *fp)
{
    char c;
    if (fwdptr == 0)
    {
        if (retract == 1)
        {
            retract = 0;
        }
    }

    if (buffer_no == 1)
    {
        c = buffer1[fwdptr];
        fwdptr = (fwdptr + 1) % 1024;
        if (fwdptr == 0)
        {
            buffer_no = 2;
            if (retract == 0)
            {
                buffer_input(fp);
            }
        }
    }

    else if (buffer_no == 2)
    {
        c = buffer2[fwdptr];
        fwdptr = (fwdptr + 1) % 1024;
        if (fwdptr == 0)
        {
            buffer_no = 1;
            if (retract == 0)
            {
                buffer_input(fp);
            }
        }
    }

    return c;
}

// Returns the lexeme value for a token in the form of a string
char *tokenizer()
{
    int n = fwdptr - bwdptr;
    char *ch = (char *)malloc(n * sizeof(char));

    if (fwdptr > bwdptr)
    {
        if (buffer_no == 1)
            ch = substring(1, bwdptr, n);
        else
            ch = substring(2, bwdptr, n);

        bwdptr = fwdptr;
    }
    else
    {
        char *ch1 = (char *)malloc((1024 - bwdptr) * sizeof(char));
        char *ch2 = (char *)malloc(fwdptr * sizeof(char));

        if (buffer_no == 1)
        {
            ch1 = substring(2, bwdptr, 1024 - bwdptr);
            ch2 = substring(1, 0, fwdptr);
            ch = concat(ch1, 1024 - bwdptr, ch2, fwdptr);
            bwdptr = fwdptr;
        }
        else
        {
            ch1 = substring(1, bwdptr, 1024 - bwdptr);
            ch2 = substring(2, 0, fwdptr);
            // ch = strcat(ch1, ch2);
            ch = concat(ch1, 1024 - bwdptr, ch2, fwdptr);
            bwdptr = fwdptr;
        }
    }
    return ch;
}

// Function for removing the comments from the file
void remove_comments_from_file(FILE *fptr1)
{
    fill_buffer_int(fptr1);
    int curr_state = 0;
    char current_char = get_char(fptr1);

    char arr[1024];
    int no_of_buffer_chars = 0;

    arr[no_of_buffer_chars++] = '*';
    arr[no_of_buffer_chars++] = '*';

    while (current_char != EOF)
    {
        if (curr_state == 0)
        {
            if (current_char == '*')
            {
                curr_state = 1;
            }
            else
            {
                printf("%c", current_char);
            }
        }
        else if (curr_state == 1)
        {
            if (current_char == '*')
            {
                curr_state = 2;
            }
            else
            {
                printf("*");
                printf("%c", current_char);
                curr_state = 0;
            }
        }
        else if (curr_state == 2)
        {
            if (current_char == '*')
            {
                curr_state = 3;
            }
            else
            {
                arr[no_of_buffer_chars++] = current_char;
                if (current_char == '\n')
                {
                    printf("%c", current_char);
                }
            }
        }
        else if (curr_state == 3)
        {
            if (current_char == '*')
            {
                memset(arr, '\0', sizeof(arr));
                no_of_buffer_chars = 0;
                arr[no_of_buffer_chars++] = '*';
                arr[no_of_buffer_chars++] = '*';
                curr_state = 0;
            }
            else
            {
                arr[no_of_buffer_chars++] = '*';
                arr[no_of_buffer_chars++] = current_char;
                curr_state = 2;
            }
        }
        current_char = get_char(fptr1);
    }

    if (no_of_buffer_chars != 2)
    {
        for (int i = 0; i < no_of_buffer_chars; i++)
        {
            printf("%c", arr[i]);
        }
    } 
}

// Check if the char passed as argument is a letter
int letter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
    {
        return 1;
    }
    else
        return 0;
}

// Check if the char passed as argument is a digit
int digit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    else
        return 0;
}

// Function for obtaining the next Token
TOKEN getNextToken(FILE *fp, map mp)
{
    char ch;
    TOKEN mytkn;

    while (1)
    {
        mytkn.line_num = line_no;
        switch (state)
        {
        case 0:
            ch = get_char(fp);
            if (letter(ch))
                state = 1;
            else if (digit(ch))
                state = 3;
            else if (ch == '<')
                state = 31;
            else if (ch == ':')
                state = 37;
            else if (ch == ';')
                state = 40;
            else if (ch == ',')
                state = 41;
            else if (ch == '[')
                state = 42;
            else if (ch == ']')
                state = 43;
            else if (ch == '(')
                state = 44;
            else if (ch == ')')
                state = 45;
            else if (ch == '+')
                state = 13;
            else if (ch == '-')
                state = 14;
            else if (ch == '!')
                state = 15;
            else if (ch == '/')
                state = 17;
            else if (ch == '>')
                state = 18;
            else if (ch == '=')
                state = 24;
            else if (ch == '*')
                state = 26;
            else if (ch == '.')
                state = 49;
            else if (ch == ' ' || ch == '\n' || ch == '\t')
            {
                mytkn.value_num = ch;
                if (ch == '\n')
                    line_no++;
                state = 46;
            }
            else if (ch == EOF)
            {
                mytkn.token = "ENDFILE";  
                return mytkn;
            }
            else
                state = 48;
            break;

        case 1:
            ch = get_char(fp);
            if (letter(ch) || digit(ch))
                state = 1;
            else
                state = 2;
            break;

        case 2:
            discard();
            mytkn.line_num = line_no;
            int lexeme_len = 0;
            if (fwdptr - bwdptr >= 0)
            {
                lexeme_len = (fwdptr - bwdptr) % 100;
            }
            else
            {
                lexeme_len = (fwdptr - bwdptr + 100) % 100;
            }
            strncpy(lexeme, tokenizer(), 100); // populate the lexeme
            if (lexeme_len > 20)               // Lexeme Length exceeding 20 characters
            {
                mytkn.token = "LEX_ERR";
            }
            else
            {
                char *temp = search_hashtable(mp, lexeme);
                if (!strcmp(temp, "not found"))
                {
                    mytkn.token = "ID"; // if not a keyword
                }
                else
                {
                    mytkn.token = temp; // assign the name of the keyword
                }
            }
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 3:
            ch = get_char(fp);
            if (digit(ch))
                state = 3;
            else if (ch == '.')
                state = 4;
            else
                state = 6;
            break;

        case 4:
            ch = get_char(fp);
            if (ch == '.')
                state = 5;
            else if (digit(ch))
                state = 7;
            else
            {
                discard();
                state = 48;
            }
            break;

        case 5:
            discard();
            discard();
            mytkn.line_num = line_no;
            strncpy(lexeme, tokenizer(), 100);
            mytkn.token = "NUM";
            mytkn.value_num = atoi(lexeme); // Convert to integer and assign to token
            state = 0;
            return mytkn;

        case 6:
            discard();
            mytkn.line_num = line_no;
            strncpy(lexeme, tokenizer(), 100);
            mytkn.token = "NUM";
            mytkn.value_num = atoi(lexeme); // Convert to integer and assign to token
            state = 0;
            return mytkn;

        case 7:
            ch = get_char(fp);
            if (digit(ch))
                state = 7;
            else if (ch == 'E' || ch == 'e')
                state = 8;
            else
                state = 9;
            break;

        case 8:
            ch = get_char(fp);
            if (ch == '+' || ch == '-')
                state = 10;
            else if (digit(ch))
                state = 11;
            else
            {
                discard();
                state = 48;
            }
            break;

        case 9:
            discard();
            mytkn.line_num = line_no;
            strncpy(lexeme, tokenizer(), 100);
            mytkn.token = "RNUM";
            mytkn.value_rnum = strtod(lexeme, &ptr_strtod); // Convert to double and assign to token
            state = 0;
            return mytkn;

        case 10:
            ch = get_char(fp);
            if (digit(ch))
                state = 11;
            else
            {
                discard();
                state = 48;
            }
            break;

        case 11:
            ch = get_char(fp);
            if (digit(ch))
                state = 11;
            else
                state = 12;
            break;

        case 12:
            discard();
            mytkn.line_num = line_no;
            strncpy(lexeme, tokenizer(), 100);
            mytkn.token = "RNUM";
            mytkn.value_rnum = strtod(lexeme, &ptr_strtod); // Convert to double and assign to token
            state = 0;
            return mytkn;

        case 13:
            mytkn.token = "PLUS";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 14:
            mytkn.token = "MINUS";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 15:
            ch = get_char(fp);
            if (ch == '=')
                state = 16;
            else
            {
                discard();
                state = 48;
            }
            break;

        case 16:
            mytkn.token = "NE";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 17:
            mytkn.token = "DIV";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 18:
            ch = get_char(fp);
            if (ch == '=')
                state = 19;
            else if (ch == '>')
                state = 21;
            else
            {
                state = 20;
            }
            break;

        case 19:
            mytkn.token = "GE";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 20:
            discard();
            mytkn.token = "GT";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 21:
            ch = get_char(fp);
            if (ch == '>')
                state = 22;
            else
                state = 23;
            break;

        case 22:
            mytkn.token = "DRIVERENDDEF";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 23:
            discard();
            mytkn.token = "ENDDEF";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 24:
            ch = get_char(fp);
            if (ch == '=')
                state = 25;
            else
            {
                discard();
                state = 48;
            }
            break;

        case 25:
            mytkn.token = "EQ";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 26:
            ch = get_char(fp);
            if (ch == '*')
                state = 27;
            else
                state = 30;
            break;

        case 27:
            bwdptr++;
            ch = get_char(fp);
            if (ch != '*')
            {
                state = 27;
                if (ch == '\n')
                    line_no++;
            }
            else
                state = 28;
            break;

        case 28:
            bwdptr++;
            ch = get_char(fp);
            if (ch == '*')
                state = 29;
            else
            {
                state = 27;
                if (ch == '\n')
                    line_no++;
            }
            break;

        case 29:
            bwdptr = fwdptr;
            state = 0;
            break;

        case 30:
            discard();
            mytkn.token = "MUL";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 31:
            ch = get_char(fp);
            if (ch == '=')
                state = 32;
            else if (ch == '<')
                state = 34;
            else
                state = 33;
            break;

        case 32:
            mytkn.token = "LE";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 33:
            discard();
            mytkn.token = "LT";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 34:
            ch = get_char(fp);
            if (ch == '<')
                state = 35;
            else
                state = 36;
            break;

        case 35:
            mytkn.token = "DRIVERDEF";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 36:
            discard();
            mytkn.token = "DEF";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 37:
            ch = get_char(fp);
            if (ch == '=')
                state = 38;
            else
                state = 39;
            break;

        case 38:
            mytkn.token = "ASSIGNOP";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 39:
            discard();
            mytkn.token = "COLON";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 40:
            mytkn.token = "SEMICOL";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 41:
            mytkn.token = "COMMA";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 42:
            mytkn.token = "SQBO";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 43:
            mytkn.token = "SQBC";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 44:
            mytkn.token = "BO";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 45:
            mytkn.token = "BC";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 46:
            ch = get_char(fp);
            if (ch == ' ' || ch == '\n' || ch == '\t')
            {
                state = 46;
                if (ch == '\n')
                    line_no++;
            }
            else
                state = 47;
            break;

        case 47:
            discard();
            mytkn.token = "DELIM";
            bwdptr = fwdptr;
            state = 0;
            break;

        case 48:
            mytkn.token = "LEX_ERR";
            mytkn.line_num = line_no;
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        case 49:
            ch = get_char(fp);
            if (ch == '.')
                state = 50;
            else
            {
                discard();
                state = 48;
            }
            break;

        case 50:
            mytkn.token = "RANGEOP";
            strncpy(lexeme, tokenizer(), 100);
            strncpy(mytkn.value_id, lexeme, 100);
            state = 0;
            return mytkn;

        default:
            break;
        }
    }
}