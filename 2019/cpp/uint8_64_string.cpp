#include <stdint.h>
#include <stdbool.h>

#include <iostream>

#include <vector>
#include <string>
#include <string.h>

#define PARAM_START     0x0000
#define PARAM_NAME_SIZE 8u
#define PARAM_VALUE_SIZE 8u
#define NAME_BYTES 8u
#define DATA_BYTES 8u

using std::string;
using std::vector;
using std::pair;

void string_to_uint8_t(string &in, uint8_t* out)
{
    vector<uint8_t> vec(in.begin(), in.end()); 
    for (size_t i =0; i < NAME_BYTES; i++)
    {
        *(out + i) = (i < vec.size()) ? vec[i] : 0;
    }
}


void uint8_t_to_string(uint8_t *in, string &out)
{
    char txt[NAME_BYTES];
    for (size_t i = 0; i < NAME_BYTES; i++)
    {
        txt[i] = in[i];
    }
    string s(txt);
    out = s;
}

void uint64_t_to_uint8_t(uint64_t &in, uint8_t* out)
{
    for (size_t i = 0; i < DATA_BYTES; i++)
    {
        *(out + i) = ((in >> (8 * i)) & 0xffu);
    }
}

void uint8_t_to_uint64_t(uint8_t* in, uint64_t &out)
{
    uint64_t tmp = 0x0;
    
    for (size_t i = 0; i < DATA_BYTES; i++)
    {
        tmp = tmp | (in[i] << (8 * i));
    }
    
    out = tmp;
}

union {
    float f;
    uint8_t ut[4];
} value_f;

void float_to_uint8_t(float in, uint8_t *out)
{
    value_f.f = in;
    for (size_t i = 0; i < 4; i++)
        out[i] = value_f.ut[i];
}

void uint8_t_to_float(uint8_t *in, float &out)
{

    for (size_t i = 0; i < 4; i++)
        value_f.ut[i] = in[i];
    
    out = value_f.f;
}

union {
    double d;
    uint8_t ut[8];
} value_d;

void double_to_uint8_t(double in, uint8_t *out)
{
    value_d.d = in;
    for (size_t i = 0; i < 8; i++)
        out[i] = value_d.ut[i];
}

void uint8_t_to_double(uint8_t *in, double &out)
{
    for (size_t i = 0; i < 8; i++)
        value_d.ut[i] = in[i];
    out = value_d.d;
}

void Param_Write_ALL_TO_FM(std::vector<pair<string, uint64_t>> param_list)
{
    uint16_t address = PARAM_START;
    uint8_t name[PARAM_NAME_SIZE];
    uint8_t value[PARAM_VALUE_SIZE];
    uint64_t out;
    string out_0;
    
    for (size_t i =0; i < param_list.size(); i++)
    {
        string_to_uint8_t(param_list[i].first, name);
        uint8_t_to_string(name, out_0);
        uint64_t_to_uint8_t(param_list[i].second, value);
        uint8_t_to_uint64_t(value, out);
        param_list[i].first = "demo";
        param_list[i].second = 234;
        std::cout << param_list[i].first << " " << param_list[i].second << std::endl;
    }
    
    {
        float a = 123123123.342;
        float b;
        uint8_t out_1[4];
        float_to_uint8_t(a, out_1);
        std::cout << a << std::endl; 
        uint8_t_to_float(out_1 , b);
        std::cout << b << std::endl; 
    }
    {
        double c = 1.1;
        double d;
        uint8_t out_2[8];
        double_to_uint8_t(c, out_2);
        std::cout << c << std::endl; 
        uint8_t_to_double(out_2 , d);
        std::cout << d << std::endl; 
    }
}

int main()
{
    static std::vector<pair<string, uint64_t>> param_list;
    std::pair<string, uint64_t> p = std::make_pair("test", 123456u);
    param_list.push_back(p);

    Param_Write_ALL_TO_FM(param_list);


}