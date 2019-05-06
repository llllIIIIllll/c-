#include <stdint.h>
#include <stdbool.h>

#include <iostream>

#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>

using std::string;
using std::vector;
using std::pair;

#define UNION_DATA_SIZE 8u

typedef union {
    uint8_t  raw[8];
    char     c_str[8];
    uint8_t  u_8;
    uint16_t u_16;
    uint32_t u_32;
    uint64_t u_64;
    int8_t   i_8;
    int16_t  i_16;
    int32_t  i_32;
    int64_t  i_64;
    double   d;
    float    f;
    bool     b;
} any_t;

vector<string> name;
vector<any_t> data;

void uint8_t_to_bool(uint8_t *in, bool &out)
{
    if (in[0]) out = true;
    else       out = false;
}

void bool_to_uint8_t(bool &in, uint8_t *out)
{
    if (in) out[0] = 1;
    else    out[0] = 0;
    for (size_t i = 1; i < UNION_DATA_SIZE; i++)
    {
        out[i] = '\0';
    }
}

void uint8_t_to_string(uint8_t *in, string &out)
{
    char txt[UNION_DATA_SIZE];
    for (size_t i = 0; i < UNION_DATA_SIZE; i++)
    {
        txt[i] = in[i];
    }
    string s(txt);
    out = s;
}

void string_to_uint8_t(string &in, uint8_t* out)
{
    vector<uint8_t> vec(in.begin(), in.end()); 
    for (size_t i = 0; i < UNION_DATA_SIZE; i++)
    {
        *(out + i) = (i < vec.size()) ? vec[i] : '\0';
    }
}



void test_for_bool()
{
    bool a = true;
    uint8_t b[UNION_DATA_SIZE];
    bool_to_uint8_t(a, b);
    std::cout << a << std::endl;
    for (size_t i = 0; i < UNION_DATA_SIZE; i++)
        std::cout << b[i] << " ";
    std::cout << std::endl;
    
    uint8_t_to_bool(b, a);
    std::cout << a << std::endl;
    for (size_t i = 0; i < UNION_DATA_SIZE; i++)
        std::cout << b[i] << " ";
    std::cout << std::endl;
}


void test_any()
{
    char param_name_list[2];
    any_t param_value_list[2];
    param_name_list[0] = 'd';
    param_name_list[1] = '1';
    param_value_list[0].d = 123.231;
    string raw = "hello";
    char txt[64];
    
      if (param_name_list[0] == 'b')
        sprintf(txt,"%d",  param_value_list[0].b);
      else if (param_name_list[0] == 'f')
        sprintf(txt,"%f",  param_value_list[0].f);
      else if (param_name_list[0] == 'd')
        sprintf(txt,"%lf",  param_value_list[0].d);
      else if (param_name_list[0] == 'u' && param_name_list[1] == '8')
        sprintf(txt,"%hhu",  param_value_list[0].u_8);
      else if (param_name_list[0] == 'u' && param_name_list[1] == '1')
        sprintf(txt,"%hu",  param_value_list[0].u_16);
      else if (param_name_list[0] == 'u' && param_name_list[1] == '3')
        sprintf(txt,"%u",  param_value_list[0].u_32);
      else if (param_name_list[0] == 'u' && param_name_list[1] == '6')
        sprintf(txt,"%lu",  param_value_list[0].u_64);
      else if (param_name_list[0] == 'i' && param_name_list[1] == '8')
        sprintf(txt,"%hhd",  param_value_list[0].u_8);
      else if (param_name_list[0] == 'i' && param_name_list[1] == '1')
        sprintf(txt,"%hd",  param_value_list[0].u_16);
      else if (param_name_list[0] == 'i' && param_name_list[1] == '3')
        sprintf(txt,"%d",  param_value_list[0].u_32);
      else if (param_name_list[0] == 'i' && param_name_list[1] == '6')
        sprintf(txt,"%ld",  param_value_list[0].u_64);
      else if (param_name_list[0] == 'c')
        sprintf(txt,"%s",  param_value_list[0].c_str);
        
    string tmp(txt);
    std::cout << tmp << std::endl;
}

any_t Param_Get_By_Name(std::vector<string> &param_name_list, std::vector<any_t> &param_value_list, string str)
{
    string param_name = str;
    size_t i;
    return param_value_list[0];
}

void test_for_get()
{
  name.resize(2);
  data.resize(2);
  name[0] = "u8_a";
  name[1] = "i16_b";
  data[0].d = 123123123.43;
  data[1].i_16 = -123;
  any_t test = Param_Get_By_Name(name, data, "i16_b");
  printf("%e\n", test.d);
}

int main()
{
    test_for_get();
}