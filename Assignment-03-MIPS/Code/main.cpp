#include<bits/stdc++.h>
using namespace std;

#ifdef APURBA
#include "DEBUG_TEMPLATE.h"
#else
#define HERE
#define debug(args...)
#endif

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

string convertBinToHex(string bin)
{
    int l = bin.size();
    int t = bin.find_first_of('.');
    int len_left = t != -1 ? t : l;
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
    if (t != -1)
    {
        int len_right = l - len_left - 1;
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }
    unordered_map<string, char> bin_hex_map;
    createMap(&bin_hex_map);
    int i = 0;
    string hex = "";

    while (1)
    {
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;
        if (bin.at(i) == '.')
        {
            hex += '.';
            i++;
        }
    }
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
    else if(s=="$t5")
    {
        return "0111";
    }
    else if(s=="$sp")
    {
        return "0110";
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
vector<string> parse2(string &tmp)
{
    vector<string>ret;
    string now;
    for(int i=0; i<tmp.size(); i++)
    {
        if(tmp[i]=='(' || tmp[i]==')')
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
string get_bits2(int x)
{
    string ret = "00000000";
    for(int i=0; i<8; i++)
    {
        if(x&(1<<i))
            ret[i]='1';
    }
    reverse(ret.begin(),ret.end());
    return ret;
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

string get_bits2(string &s)
{
    int x = stoi(s);
    string ret = "00000000";
    for(int i=0; i<8; i++)
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
        else if(op=="push")
        {
            string tmp;
            getline(cin,tmp);
            vector<string>all = parse2(tmp);
            if(all.size()==1)
            {
                //sw $t0, 0($sp)
                //addi $sp,$sp,1
                vector<string>now = {"sw", all[0], "0($sp)"};
                vector<string>now2 = {"addi", "$t5", "$zero", "255"};
                vector<string>now3 = {"sub", "$t5", "$t5", "$sp"};
                vector<string>now4 = {"addi", "$sp", "$t5", "1"};
                code.push_back(now);
                code.push_back(now2);
                code.push_back(now3);
                code.push_back(now4);
            }
            else
            {
//                lw $t5, 3($t0)
//                sw $t5, 0($sp)
//                addi $sp,$sp,1
                string val = all[0];
                string reg = all[1];
                string koto = val + "(" + reg + ")";
                vector<string>now = {"lw", "$t5", koto};
                code.push_back(now);
                vector<string>now2 = {"sw", "$t5","0($sp)" };
                code.push_back(now2);
                vector<string>now4 = {"addi", "$t5", "$zero", "255"};
                code.push_back(now4);
                vector<string>now5 = {"sub", "$t5", "$t5", "$sp"};
                code.push_back(now5);
                vector<string>now3 = {"addi", "$sp", "$t5", "1"};
                code.push_back(now3);
            }
        }
        else if(op=="pop")
        {
            string tmp;
            getline(cin,tmp);
            vector<string>all = parse2(tmp);
            vector<string>now = {"lw", all[0], "1($sp)"};
            code.push_back(now);
            vector<string>now4 = {"addi", "$t5", "$zero", "255"};
            code.push_back(now4);
            vector<string>now5 = {"sub", "$t5", "$t5", "$sp"};
            code.push_back(now5);
            vector<string>now2 = {"subi", "$sp", "$t5", "1"};
            code.push_back(now2);
        }
        else
        {
            //this is a label
            string name = op;
            bool flag= 0;
            if(name.back()==':')
            {
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


//class Register{
//public:
//    string name;
//    int val;
//    Register(string s)
//    {
//        name = s;
//        val = 0;
//    }
//    void add(Register r1, Register r2)
//    {
//        val = r1.val + r2.val;
//    }
//    void addi(Register r1 , int x)
//    {
//        val = r1.val + x;
//    }
//    void sub(Register r1 , Register r2)
//    {
//        val = r1.val - r2.val;
//    }
//    void subi(Register r1, int x)
//    {
//        val = r1.val - x;
//    }
//    void And(Register r1, Register r2)
//    {
//        val = r1.val&r2.val;
//    }
//    void andi(Register r1 , int x)
//    {
//        val = r1.val & x;
//    }
//    void Or(Register r1, Register r2)
//    {
//        val = r1.val|r2.val;
//    }
//    void ori(Register r1 , int x)
//    {
//        val = r1.val | x;
//    }
//    void sll(Register r1 , int x)
//    {
//        val = r1.val << x;
//    }
//    void srl(Register r1 , int x)
//    {
//        val = r1.val >> x;
//    }
//    void Nor(Register r1 , Register r2)
//    {
//        val = ~(r1.val | r2.val);
//    }
//
//
//};


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    read_code();
    //debug(code);
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
            if(op == "lw" || op=="sw")
            {
                //genjam
                string opcode = get_op_code(op), src, dest = get_register_code(all[0]);
                string val;
                for(int i=0; i<all[1].size(); i++)
                {
                    if(all[1][i]=='(')
                    {
                        for(int j=i+1; j<all[1].size(); j++)
                        {
                            if(all[1][j]==')')
                                break;
                            src += all[1][j];
                        }
                        break;
                    }
                    else
                    {
                        val += all[1][i];
                    }
                }
                while(val.back()==' ')
                    val.pop_back();
                while(val[0]==' ')
                    val.erase(val.begin());
                while(src.back()==' ')
                    src.pop_back();
                while(src[0]==' ')
                    src.erase(src.begin());
                src = get_register_code(src);
                val = get_bits2(val);
                //cout<<opcode<<" "<<src<<" "<<dest<<" "<<val<<"\n";
                //cout<<"Here\n";
                cout<<convertBinToHex(opcode)<<convertBinToHex(src)<<convertBinToHex(dest)<<convertBinToHex(val)<<"\n";
            }
            else if(op=="beq" || op=="bneq")
            {
                string opcode = get_op_code(op), src = get_register_code(all[0]), dest = get_register_code(all[1]);
                string value ;
                int jabe = labels[all[2]];
                if(jabe >= line)
                {
                    int koto =   jabe - line;
                    value = get_bits2(koto);
                }
                else
                {
                    int koto = line - jabe;
                    //2s compliment
                    int x = 0;
                    for(int i=0; i<8; i++)
                    {
                        if(koto&(1<<i))
                        {

                        }
                        else
                        {
                            x |= (1<<i);
                        }
                    }
                    x += 1;
                    value = get_bits2(x);
                }
                //cout<<opcode<<" "<<src<<" "<<dest<<" "<<value<<"\n";
                cout<<convertBinToHex(opcode)<<convertBinToHex(src)<<convertBinToHex(dest)<<convertBinToHex(value)<<"\n";

            }
            else
            {
                string opcode = get_op_code(op), src = get_register_code(all[1]), dest = get_register_code(all[0]), value= get_bits2(all[2]);
                //cout<<opcode<<" "<<src<<" "<<dest<<" "<<value<<"\n";
                cout<<convertBinToHex(opcode)<<convertBinToHex(src)<<convertBinToHex(dest)<<convertBinToHex(value)<<"\n";
            }

        }
        else if(find(jtype.begin(),jtype.end(), op) != jtype.end())
        {
            vector<string>all = code[line];
            all.erase(all.begin());
            string opcode = get_op_code(op);
            int tmp = labels[all[0]];
            string jmp = "00000000";
            for(int i=0; i<8; i++)
            {
                if(tmp&(1<<i))
                {
                    jmp[i] = '1';
                }
            }
            reverse(jmp.begin(),jmp.end());
            //cout<<opcode<<" "<<jmp<<" "<< "00000000"<<"\n";
            cout<<convertBinToHex(opcode)<<""<<convertBinToHex(jmp)<<"00\n";
            line++;
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}
