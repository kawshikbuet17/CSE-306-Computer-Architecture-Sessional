#include<bits/stdc++.h>

using namespace std;

void createMap(unordered_map<string, char> *um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
}

// function to find hexadecimal
// equivalent of binary
string convertBinToHex(string bin)
{
    int l = bin.size();
    int t = bin.find_first_of('.');

    // length of string before '.'
    int len_left = t != -1 ? t : l;

    // add min 0's in the beginning to make
    // left substring length divisible by 4
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;

    // if decimal point exists
    if (t != -1)
    {
        // length of string after '.'
        int len_right = l - len_left - 1;

        // add min 0's in the end to make right
        // substring length divisible by 4
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }

    // create map between binary and its
    // equivalent hex code
    unordered_map<string, char> bin_hex_map;
    createMap(&bin_hex_map);

    int i = 0;
    string hex = "";

    while (1)
    {
        // one by one extract from left, substring
        // of size 4 and add its hex code
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;

        // if '.' is encountered add it
        // to result
        if (bin.at(i) == '.')
        {
            hex += '.';
            i++;
        }
    }

    // required hexadecimal number
//    while(hex.size()<5)
//    {
//        hex.insert(hex.begin(),'0');
//    }
    return hex;
}

string get_op_code(string &op)
{
    if(op=="nor")
    {
        return "0000";
    }
    else if(op=="sll")
    {
        return "0001";
    }
    else if(op=="sw")
    {
        return "0010";
    }
    else if(op=="ori")
    {
        return "0011";
    }
    else if(op=="andi")
    {
        return "0100";
    }
    else if(op=="subi")
    {
        return "0101";
    }
    else if(op=="j")
    {
        return "0110";
    }
    else if(op=="beq")
    {
        return "0111";
    }
    else if(op=="addi")
    {
        return "1000";
    }
    else if(op=="lw")
    {
        return "1001";
    }
    else if(op=="srl")
    {
        return "1010";
    }
    else if(op=="or")
    {
        return "1011";
    }
    else if(op=="and")
    {
        return "1100";
    }
    else if(op=="add")
    {
        return "1101";
    }
    else if(op=="sub")
    {
        return "1110";
    }
    else if(op=="bneq")
    {
        return "1111";
    }
    //invalid instruction
    assert(false);
}

string get_register_code(string &s)
{
    if(s=="$zero")
    {
        return "0000";
    }
    else if(s=="$t0")
    {
        return "0001";
    }
    else if(s=="$t1")
    {
        return "0010";
    }
    else if(s=="$t2")
    {
        return "0011";
    }
    else if(s=="$t3")
    {
        return "0100";
    }
    else if(s=="$t4")
    {
        return "0101";
    }
    else if(s=="$one")
    {
        return "0111";
    }
    //invalid register
    assert(false);
}

vector<string> rtype = {"add","sub","and","or","sll","srl","nor"};
vector<string> itype = {"addi","subi","andi","ori","sw","lw","beq","bneq"};
vector<string> jtype = {"j"};

vector<string> parse(string &tmp)
{
    vector<string>ret;
    string now;
    for(int i=0; i<tmp.size(); i++)
    {
        if(tmp[i]==',')
        {
            if(now.size())
            {
                ret.push_back(now);
            }
            now = "";
        }
        else if(tmp[i]==' ')
        {
            if(now.size())
            {
                ret.push_back(now);
            }
            now = "";
        }
        else
        {
            now += tmp[i];
        }
    }
    if(now.size())
    {
        ret.push_back(now);
    }
    return ret;
}

bool check_num(string &s)
{
    for(int i=0; i<s.size(); i++)
    {
        if(!(s[i]>='0' && s[i]<='9'))
        {
            return 0;
        }
    }
    return 1;
}

string get_bits(string &s)
{
    int x = stoi(s);
    string ret = "0000";
    for(int i=0; i<4; i++)
    {
        if(x&(1<<i))
            ret[i]='1';
    }
    reverse(ret.begin(),ret.end());
    return ret;
}


vector<vector<string> >code;

map<string, int> labels;

void read_code()
{
    string op;
    while(cin>>op)
    {
        vector<string>now;
        if(find(rtype.begin(),rtype.end(), op) != rtype.end())
        {
            string tmp;
            getline(cin,tmp);
            vector<string>all = parse(tmp);
            now.push_back(op);
            for(auto it:all)
            {
                now.push_back(it);
            }
            code.push_back(now);
        }
        else if(find(itype.begin(),itype.end(), op) != itype.end())
        {
            string tmp;
            getline(cin,tmp);
            vector<string>all = parse(tmp);
            now.push_back(op);
            for(auto it:all)
            {
                now.push_back(it);
            }
            code.push_back(now);
        }
        else if(find(jtype.begin(),jtype.end(), op) != jtype.end())
        {
            string tmp;
            getline(cin,tmp);
            vector<string>all = parse(tmp);
            now.push_back(op);
            for(auto it:all)
            {
                now.push_back(it);
            }
            code.push_back(now);
        }
        else
        {
            //this is a label
            string name = op;
            bool flag= 0;
            if(name.back()==':'){
                name.pop_back();
                flag = 1;
            }
            int line = code.size();
            labels[name]= line;
            //expecting a :
            if(flag==0)
            {
                char ch;
                while(1)
                {
                    cin>>ch;
                    if(ch==':')
                        break;
                }
            }
        }
    }
}
int main()
{
    freopen("input.txt","r",stdin);
    read_code();
    int line =0;
    while(line<code.size())
    {
        string op = code[line][0];
        if(find(rtype.begin(),rtype.end(), op) != rtype.end())
        {
            //rtype
            vector<string>all = code[line];
            all.erase(all.begin());
            string opcode, src1, src2, dest, shft;
            opcode = get_op_code(op);
            dest = get_register_code(all[0]);
            src1 = get_register_code(all[1]);
            if(check_num(all[2]))
            {
                src2 = "0000";
                shft = get_bits(all[2]);
            }
            else
            {
                src2 = get_register_code(all[2]);
                shft = "0000";
            }
            //cout<<opcode<<" "<<src1<<" "<<src2<<" "<<dest<<" "<<shft<<"\n";
            cout<<convertBinToHex(opcode)<<""<<convertBinToHex(src1)<<""<<convertBinToHex(src2)<<""<<convertBinToHex(dest)<<""<<convertBinToHex(shft)<<"\n";
            line++;
        }
        else if(find(itype.begin(),itype.end(), op) != itype.end())
        {
            vector<string>all = code[line];
            all.erase(all.begin());

            line++;
        }
        else if(find(jtype.begin(),jtype.end(), op) != jtype.end())
        {
            vector<string>all = code[line];
            all.erase(all.begin());
            string opcode = get_op_code(op);
            line = labels[all[0]];
            string jmp = "00000000";
            for(int i=0;i<8;i++)
            {
                if(line&(1<<i))
                {
                    jmp[i] = '1';
                }
            }
            reverse(jmp.begin(),jmp.end());
            //cout<<opcode<<" "<<jmp<<"\n";
            cout<<convertBinToHex(opcode)<<""<<convertBinToHex(jmp)<<"\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}
/*
*/
