#include<bits/stdc++.h>

using namespace std;


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
            cout<<opcode<<" "<<src1<<" "<<src2<<" "<<dest<<" "<<shft<<"\n";
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
            cout<<opcode<<" "<<jmp<<"\n";
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
