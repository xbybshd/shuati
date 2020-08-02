class Solution
{
public:
    stack<char> sp;
    bool isValid(string s)
    {
        int l = s.length();
        for (int i = 0; i < l; i++)
        {
            if (s[i] == ')')
            {
                if (!sp.empty() && sp.top() == '(')
                {
                    sp.pop();
                }
                else
                {
                    sp.push(')');
                }
            }
            else if (!sp.empty() && s[i] == ']')
            {
                if (sp.top() == '[')
                {
                    sp.pop();
                }
                else
                {
                    sp.push(']');
                }
            }
            else if (!sp.empty() && s[i] == '}')
            {
                if (sp.top() == '{')
                {
                    sp.pop();
                }
                else
                {
                    sp.push('}');
                }
            }
            else
            {
                sp.push(s[i]);
            }
        }
        return sp.empty();
    }
};