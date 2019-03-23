//
// Created by timpo on 3/23/19.
//

#ifndef FINDER_PF_H
#define FINDER_PF_H
#pragma once


#include <vector>
#include <iostream>

class pf {


private:
    std::vector<size_t> pref_func;
    std::string str;
    size_t common_size = 0;


    size_t calc_next_pf(char new_char) {
        size_t ret = common_size;
        while (ret > 0 && new_char != str[ret]) {
            ret = pref_func[ret - 1];
        }
        if (new_char == str[ret]) {
            ret++;
        }
        return ret;
    }

    void build_pf() {
        common_size = 0;
        size_t n = str.size();
        pref_func.resize(n);
        pref_func[0] = 0;
        for (size_t i = 1; i < n; i++) {
            pref_func[i] = calc_next_pf(str[i]);
        }
    }

public:
    explicit pf() = default;


    explicit pf(std::string const &st) {
        str = st;
        build_pf();
    }


    bool check(char new_char) {
        common_size = calc_next_pf(new_char);
        return common_size == str.size();
    }


    void update(char new_char) {
        common_size = calc_next_pf(new_char);
    }


    void rebuild(std::string const &new_string) {
        str = new_string;
        build_pf();
    }
};

#endif //FINDER_PF_H
