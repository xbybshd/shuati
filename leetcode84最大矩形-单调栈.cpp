class Solution {
public:
struct node{
    int h;//当前矩形的高度
    int w;//当前矩形到前一个比它矮的矩形的总宽度
    node(int _h,int _w):h(_h),w(_w){};
    node(){};
};

stack<node> s;
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);//把最后一个加上高度0，可以让所有数值都出栈
        int len=heights.size();
        int ans=0;
        s.push(node(heights[0], 1));//先压入第一个
        for(int i=1;i<len;i++){//从第二个开始
            if(heights[i]>s.top().h){//当前高度大于栈顶，直接压栈
                s.push(node(heights[i],1));
            }
            else{
                node a(heights[i],1);
                int width=0;//当前矩形到前一个与其相等矩形的宽度
                while((!s.empty())&&heights[i]<s.top().h){
                    width+=s.top().w;//弹出一个高的就加宽度
                    ans=max(ans,width*s.top().h);//弹出一个高的，将其高度乘上它延伸的总宽度就是面积
                    cout<<ans<<endl;
                    s.pop();//弹出
                }
                a.w+=width;//要压入的矩形的宽度
                s.push(a);
            }
        }
        return ans;
    }