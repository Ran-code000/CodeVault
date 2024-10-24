void Polynomial::from_String_to_Terms(const std::string& str){
    size_t len = str.length();
    for(size_t i = 0; i < len;){
        double coff = 0.0; int exp = 0, sign = 1;
        if(std::isspace(str[i])) continue;
        if(str[i] == '+') sign = 1, i++;
        else if(str[i] == '-') sign = -1, i++; 
        if(std::isdigit(str[i])){
            double Integer_val = 0, Decimal_val = 0;
            while(i < len && std::isdigit(str[i])) Integer_val = Integer_val * 10 + str[i] - '0', i++;
            if(i < len && str[i] == '.'){
                i++;
                double d = 0.1;
                while(i < len && std::isdigit(str[i])){
                    Decimal_val += d * (str[i] - '0');
                    d /= 10; i++;
                }
            }
            coff = sign * (Integer_val + Decimal_val);

            if(i < len){
                if(str[i] != 'x') exp = 0;
                else if(i + 1 < len && str[i + 1] != '^') exp = 1;
                else if(i + 1 < len && str[i + 1] == '^'){
                    i += 2;
                    int val = 0;
                    while(i < len && std::isdigit(str[i])) val = val * 10 + str[i] - '0', i++;
                    exp = val;
                }
            }
            terms.push_back({coff, exp});
        }
    }
}
