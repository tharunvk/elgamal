#include<iostream>
#include<cstring>
#include<vector>
#include <chrono>
#include<algorithm>
using namespace std;
using namespace std::chrono;

typedef struct node{
	//char s[MAX_SIZE];
	string s;
	int sign;
	//int lastdigit;
}largeInt;

// Returns true if str1 is smaller than str2.
bool isSmaller(string str1, string str2)
{
    // Calculate lengths of both string
    int n1 = str1.length(), n2 = str2.length();
 
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
 
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
 
    return false;
}
 
// Function for find difference of larger numbers
largeInt findDiff(largeInt p, largeInt q)
{
    // Before proceeding further, make sure str1
    // is not smaller
    string str1 = p.s;
    string str2 = q.s;
    if (isSmaller(str1, str2))
        swap(str1, str2);
 
    // Take an empty string for storing result
    string str = "";
 
    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();
 
    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
 
    int carry = 0;
 
    // Run loop till small string length
    // and subtract digit of str1 to str2
    for (int i = 0; i < n2; i++) {
        // Do school mathematics, compute difference of
        // current digits
 
        int sub
            = ((str1[i] - '0') - (str2[i] - '0') - carry);
 
        // If subtraction is less then zero
        // we add then we add 10 into sub and
        // take carry as 1 for calculating next step
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }
 
    // subtract remaining digits of larger number
    for (int i = n2; i < n1; i++) {
        int sub = ((str1[i] - '0') - carry);
 
        // if the sub value is -ve, then make it positive
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }
 
    // reverse resultant string
    reverse(str.begin(), str.end());

    while(str[0]=='0')
    	str.erase(0,1);
    
    largeInt finalres = {str,0};
	return finalres;
 
}

largeInt findSum(largeInt p, largeInt q)
{
    // Before proceeding further, make sure length
    // of str2 is larger.
    string str1 = p.s;
    string str2 = q.s;
    if (str1.length() > str2.length())
        swap(str1, str2);
 
    // Take an empty string for storing result
    string str = "";
 
    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();
 
    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
 
    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
 
        // Calculate carry for next step
        carry = sum/10;
    }
 
    // Add remaining digits of larger number
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
 
    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');
 
    // reverse resultant string
    reverse(str.begin(), str.end());

    largeInt finalres = {str,0};
	return finalres;
}

largeInt mul(largeInt p, largeInt q){
	string num1 = p.s;
	string num2 = q.s;
	int len1 = num1.size();
    int len2 = num2.size();
    
 
    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);
 
    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;
     
    // Go from right to left in num1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 
        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;
         
        // Go from right to left in num2            
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';
 
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            // Carry for next iteration
            carry = sum/10;
 
            // Store result
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }
 
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
 
    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
 
    
 
    // generate the result string
    string s = "";
     
    while (i >= 0)
        s+= result[i--] + '0';

    largeInt finalres = {s,0};
    if(p.sign==1 || q.sign==1)
    	finalres.sign=1;
    if(p.sign==1 && q.sign==1)
    	finalres.sign=0;
    if(p.sign==0 && q.sign==0)
    	finalres.sign=0;
	return finalres;
}

largeInt div(largeInt p, largeInt q){
	if(p.s.size()<q.s.size()){
		largeInt blah ={"0",0};
		return blah;
	}
	if(p.s.size()==q.s.size() && isSmaller(p.s,q.s)){
		largeInt blah ={"0",0};
		return blah;
	}

	if(p.s.size()==q.s.size() && p.s==q.s){
		largeInt blah ={"1",0};
		return blah;
	}
	else{
		int len1 = p.s.size()-q.s.size()-1;
		string temp="1";
		for(int i=0;i<len1;i++)
			temp.push_back('0');

		largeInt dividend = {temp,0};
		largeInt mult = mul(q,dividend);
		mult =  findDiff(p,mult);
		largeInt res = findSum(dividend,div(mult,q));
		return res;
	}

}
largeInt mod(largeInt p, largeInt q){
	largeInt quo = div(p,q);
	largeInt mult = mul(quo,q);
	return findDiff(p,mult);
}
largeInt modInverse(largeInt a, largeInt m){
	largeInt m0 =m;
	largeInt x={"1",0};
	largeInt y={"0",0};

	int fx=0,fy=0;

	while(a.s>"1"){
		largeInt q = div(a,m);
		largeInt t = m;

		m=mod(a,m);
		a=t;
		t=y;

		int ft;
		ft=fy;

		largeInt temp = mul(q,y);

		if(fx==0 && fy==0){
			if(!isSmaller(x.s,temp.s)){
				y=findDiff(x,temp);
				fy=0;
			}
			else{
				y=findDiff(temp,x);
				fy=1;
			}
		}
		else if (fx==0 && fy==1){
			y=findSum(x,temp);
			fy=0;
		}

		else if(fx==1 && fy==1){
			if(!isSmaller(temp.s,x.s)){
				y=findDiff(temp,x);
				fy=0;
			}
			else{
				y=findDiff(x,temp);
				fy=1;
			}
		}
		else if(fx==1 && fy==0){
			y=findSum(x,temp);
			fy=1;
		}

		x=t;
		fx=ft;


	}
	if(fx==1){
		x=findDiff(m0,x);
	}
	return x;
}

string to_binary(largeInt b){
	string bin = "";
	int i=0;
	while(b.s>"0"){
		largeInt two={"2",0};
		largeInt zero={"0",0};
		largeInt temp = mod(b,two);
		if(temp.s==zero.s){
			bin[i++]='0';
		}
		else{
			bin[i++]='1';
		}
		b= div(b,two);
	}
	return bin;
}

largeInt modPower(largeInt a,largeInt b, largeInt n){
	string bin = to_binary(b);

	int length = bin.size();
	largeInt r =a;

	for(int i=length-1;i>=0;i++){
		r = mod(mul(r,r),n);
		if(bin[i]=='1')
			r = mod(mul(r,a),n); 
	}
	return r;
}

largeInt decryption(largeInt C,largeInt d,largeInt n){

	largeInt res = modPower(C,d,n);
	return res;
}

largeInt fermat_decryption(largeInt C,largeInt p,largeInt q,largeInt dp,largeInt dq,largeInt Xp,largeInt Xq,largeInt n){

	largeInt Cp = mod(C,p);
	largeInt Cq = mod(C,q);

	largeInt Vp = modPower(Cp,dp,p);
	largeInt Vq = modPower(Cq,dq,q);

	largeInt lhs = mul(Vp,Xp);
	largeInt rhs = mul(Vq,Xq);

	largeInt val = findSum(lhs,rhs);

	return mod(val,n);
}

int main(){
	largeInt n,phi,d;
	largeInt m = {"194165348595303025516433018897",0};
	largeInt p = {"700224993530999530952629002371",0};

    largeInt x = {"313228989825133753116708407647",0};
    largeInt r = {"619353849048912497",0};
	

    //largeInt g = {"50549",0};
    largeInt g = {"22847317707751357042282130269",0};
    largeInt y = modPower(g,x,p);

    largeInt c1 = modPower(g,r,p);
    largeInt temp = modPower(y,r,p);

    largeInt c2 = mod(mul(m,temp),p);

    cout<<"Initial message : "<<m.s<<endl;

    cout<<"Encryption :\n";
    cout<<"------------\n";

    cout<<"Cipher text :"<<endl;
    cout<<c1.s<<" , "<<c2.s<<endl;

    cout<<"Decryption :\n";
    cout<<"------------\n";

    largeInt cx = modPower(c1,x,p);
    largeInt inv = modInverse(cx,p);

    largeInt message = mod(mul(c2,inv),p);
    cout<<"Final Message :\n";
    cout<<message.s<<endl;

}