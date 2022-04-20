#include <iostream>

const std::string NonStrict_rules = "!#$%&'*+-/=?^_`{|}~";

int  find_substr    (std::string, std::string, int);
bool check_interval (char, int, int);
bool check_logic    (std::string, bool);
bool Valid          (std::string);


int main() {
    // std::string email = ".s#D(f@dfg.ne#$t"; // - gives false because first .
    // std::string email = "s..#D(f@dfg.ne#$t"; // - gives false because double ..
    // std::string email = "s#D(f@dfg.ne#$t"; // - gives false because ( in left
    //std::string email = "s#Df@df#g.net"; // gives false # in Right side
    std::string email = "s#Df@dfg.net"; // gives true

    std::cout << "Enter EMAIL to check:\n";
    //   std::cin >> email;
    //   std::cout << email << "\n";

    if(Valid(email)){
        std::cout << email << "\n YES \n";
    }else{
        std::cout << email << "\n NO \n";
    }
    return 0;
}

// ========================================== Valid
bool Valid (std::string email)
{
    // 1. find @
    int pos_ampersend = 0;
    pos_ampersend = find_substr(email, "@",0);
//  std::cout << "pos_ampersend =  " << pos_ampersend << "\n";

    if (pos_ampersend <= 1){
        std::cout << " @  not found or the first symbol (not allowed)\n";
        return false;
    }

// 2) separate left and right parts
    std::string LeftSide   = email.substr(0,pos_ampersend);
    std::string RightSide  = email.substr(pos_ampersend+1, email.length());

// 3) checking length left & right parts on sizes
    if ( LeftSide.length() > 64 || LeftSide.length() <=1){
        std::cout << " Left size of email > 64 or less than 1 \n";
        return false;
    }
    if (( RightSide.length() > 63) || (RightSide.length()<=1)){
        std::cout << " Right size > 63 or empty \n";
        return false;
    }

    // checking LeftPart on the first "."
    if (LeftSide[0] == '.'){
        std::cout << " First symbol can not be . \n";
        return false;
    }

    // checking RightPart on the last "."
    if (RightSide[RightSide.length()-1] == '.' ){
        std::cout << " Last symbol can not be . \n";
        return false;
    }

    // checking on .. (double .)
    if (find_substr(email,"..",0) > 0){
        std::cout << " .. are not allowed \n";
        return false;
    }

    bool Strict = true;
    bool NonStrict = false;

    if (!check_logic(LeftSide,NonStrict)){
        std::cout << " \n Some rules in Email Left Side are broken \n";
        return false;
    }


    if (!check_logic(RightSide,Strict)){
        std::cout << " \n Some rules in Email Right Side are broken \n";
        return false;
    }


    return true; // if we are here
}
// ================================================================ check_logic
bool check_logic(std::string Side, bool Strict){
    char Ch;
    bool Return_value = false;

    // Checking side on the rules
    for (int j = 0; j <= Side.length() - 1; j++) {
        Ch = Side[j]; // just to type less :)
        // try small symbols
        std::cout << "\n1 " << Ch; // debugging print
        Return_value = false; // before checking
        if (check_interval(Ch, 97, 122)) {
            //a-z found!
            std::cout << "\n" << Ch << " OK";
            std::cout << "\n1 ==============================================\n";
            Return_value = true;
        } else {
            // try Capital symbols
            std::cout << "\n2 " << Ch; // debugging print
            if (check_interval(Ch, 65, 90)) {
                // A-Z  found!
                std::cout << "\n" << Ch << " OK";
                std::cout << "\n2 ==============================================\n";
                Return_value = true;
            } else {
                // try . -
                std::cout << "\n3 " << Ch; // debugging print
                if (check_interval(Ch, 45, 46)) {
                    // . -  found!
                    std::cout << "\n" << Ch << " OK";
                    std::cout << "\n3 ==============================================\n";
                    Return_value = true;
                } else {
                    if (!Strict) {
                        // try NonStrict exceptions
                        std::cout << "\n" << Ch;
                        for (int i = 0; i <= NonStrict_rules.length(); i++) {
                            int tmp = NonStrict_rules[i];
                            if (check_interval(Ch, tmp, tmp)) {
                                // found and exit
                                std::cout << "\n" << Ch << " OK";
                                std::cout << "\n4 ==============================================\n";
                                Return_value = true;
                                break;
                            } // fits checking
                        } // exemption loop
                    }
                }
            }
        }
        if (!Return_value) // if meet at least the first no valid then exit false
            return false;
    }
    return true; // if we are here then some of conditions above are valid
}
// ================================================================ find_substr
int find_substr(std::string str, std::string substr, int pos){
    size_t found = str.find(substr, 0);

    if (found != std::string::npos) {
//        std::cout << "found = " << found;
        return found;
    } else
        return -1;
}

// ========================================================== check_interval
bool check_interval(char ch, int left, int right){
    int tmp = ch;
    std::cout <<  "\nSYMBOL = " <<  ch << "  ASC = " << tmp << " LBound= " << left << " RBound=" << right;

    if (tmp < left || tmp > right) {
        std::cout << "\nSymbol " << ch << " is not allowed";
        return false;
    }
    return true;
}




