#include<bits/stdc++.h>
#define E_SIZE 4
#define F_SIZE 11
#define BIAS (1<<(E_SIZE-1))-1
using namespace std;

string intToBinary(int n)
{
    string s;
    while(true)
    {
        s+=(char)(n%2+'0');
        n/=2;
        if(n==0)
            break;
    }
    reverse(s.begin(),s.end());
    return s;
}
string fractionToBinary(double n)
{
    string s;
    while(s.size()<100)
    {
        double t=n*2;
        s+=(char)(floor(t)+'0');
        n=t-floor(t);
        if(n==0)
            break;
    }
    return s;
}

int binaryToInt(string s)
{
    reverse(s.begin(),s.end());
    int ans=0;
    for(int i=0;i<s.size();i++)
    {
        ans+=(s[i]-'0')*(1<<i);
    }
    return ans;
}
double binaryToFrac(string s)
{
    double now=1;
    double ans=0;
    for(int i=0;i<s.size();i++)
    {
        now/=2;
        ans+=(s[i]-'0')*now;
    }
    return ans;
}


struct NormalForm
{
    string sign,exponent,fraction;
    int exp;
    NormalForm()
    {

    }

    NormalForm(string sign,string exponent,string fraction)
    {
        this->sign=sign;
        this->exponent=exponent;
        this->fraction='1'+fraction;
        exp=binaryToInt(exponent);
    }

//    void setNumber(double n)
//    {
//        if(n>=0)
//            sign="0";
//        else
//            sign="1";
//
//        string a=intToBinary(floor(n));
//        string b=fractionToBinary(n-floor(n));
//
//        bool f=0;
//
//        for(int i=0; i<a.size(); i++)
//        {
//            if(a[i]=='1')
//            {
//                exp=a.size()-i-1;
//                f=1;
//
//                fraction=string(a.begin()+i+1,a.end())+b;
//                exp=exp+BIAS;
//                exponent=intToBinary(exp);
//                while(exponent.size()<E_SIZE)
//                    exponent='0'+exponent;
//                while(fraction.size()<F_SIZE)
//                    fraction+='0';
//                while(fraction.size()>F_SIZE)
//                    fraction.pop_back();
//
//                if(exponent.size()>E_SIZE||fraction.size()>F_SIZE)
//                {
//                    cout<<"Limit crossed"<<'\n';
//                    exit(0);
//                }
//
//                break;
//            }
//        }
//        for(int i=0; i<b.size()&&!f; i++)
//        {
//            if(b[i]=='1')
//            {
//                exp=-(i+1);
//                f=1;
//                fraction=string(b.begin()+i+1,b.end());
//                exp+=BIAS;
//
//                exponent=intToBinary(exp);
//                while(exponent.size()<E_SIZE)
//                    exponent='0'+exponent;
//                while(fraction.size()<F_SIZE)
//                    fraction+='0';
//                while(fraction.size()>F_SIZE)
//                    fraction.pop_back();
//
//                if(exponent.size()>E_SIZE||fraction.size()>F_SIZE)
//                {
//                    cout<<"Limit crossed"<<'\n';
//                    exit(0);
//                }
//
//                break;
//            }
//        }
//    }

    void show()
    {
        cout<<"Normal form: "<<sign<<' '<<exponent<<' '<<string(fraction.begin(),fraction.end())<<' '<<endl;
    }

    void value()
    {
        double ans=1;
        if(sign=="1") ans=-1;
        double f=binaryToInt(string(fraction.begin(),fraction.end()));

        f/=pow(2,fraction.size()-1);

        int a=binaryToInt(exponent);
        int b=BIAS;
        int e=a-(int)b;
        ans=ans*f*pow(2,e);
        cout<<setprecision(20)<<"Value: "<<ans<<endl;
    }

    void alignWithNewExponent(int x)
    {
        if(x<exp)
        {
            cout<<"Wrong alignment\n";
            return;
        }

        int diff=x-exp;
        exp=x;

        exponent=intToBinary(exp);
        while(exponent.size()<E_SIZE)
            exponent='0'+exponent;

        for(int i=1; i<=diff; i++)
        {
            fraction.pop_back();
            fraction='0'+fraction;
        }
    }
};

main()
{
    while(true)
    {
//        NormalForm form;
//        double n;
//        cin>>n;
//        form.setNumber(n);
//        form.show();
        string sign1,exponent1,fraction1;
        string sign2,exponent2,fraction2;
        cin>>sign1>>exponent1>>fraction1;
        cin>>sign2>>exponent2>>fraction2;

        NormalForm form1(sign1,exponent1,fraction1);
        NormalForm form2(sign2,exponent2,fraction2);
        form1.value();
        form2.value();
        int mx=max(form1.exp,form2.exp);
        form1.alignWithNewExponent(mx);
        form2.alignWithNewExponent(mx);

        form1.show();
        form2.show();
        form1.value();
        form2.value();

        int f1=binaryToInt(form1.fraction);
        int f2=binaryToInt(form2.fraction);
        if(form1.sign=="1") f1=-f1;
        if(form2.sign=="1") f2=-f2;

        cout<<"After sign set: "<<endl;
        for(int i=F_SIZE+1;i>=0;i--)
        {
            if(f1&(1<<i)) cout<<1;
            else cout<<0;
        }
        cout<<endl;
        for(int i=F_SIZE+1;i>=0;i--)
        {
            if(f2&(1<<i)) cout<<1;
            else cout<<0;
        }
        cout<<endl;
        int ans=f1+f2;
        int b=BIAS;
        cout<<mx<<endl;
        cout<<ans<<' '<<ans*pow(2,mx-b-F_SIZE)<<endl;
        for(int i=29;i>=0;i--)
        {
            if(ans&(1<<i)) cout<<1;
            else           cout<<0;
        }
        cout<<endl;
        for(int i=F_SIZE+1;i>=0;i--)
        {
            if(ans&(1<<i)) cout<<1;
            else           cout<<0;
        }
        cout<<endl;
    }

}
/*
1 01111111 01000110011001100110011
0 10000001 01111000000000000000000

0 01111110 10110011001100110011010
0 10000000 00100000000000000000000

0 0111 10011001100
0 1000 11000000000

0 1001 01000110011

0 1000 01010001111

0 0111 01101011100
0 1001 00000011110


1 1000 11100000000
0 1000 00111001100

0 1001 11110000000
0 1001 11101111111
0 0001 11101011100
0 0001 11101001100



*/
