int q_pow(int x,int p){//快速幂
    int ans = 1;
    while(p){
        if(p&1)
            ans = (1ll * ans * x) % Mod;
        x = (1ll * x * x) % Mod;
        p>>=1;
    }
    return ans;
}

void pre_porcss(){//预处理n!的阶乘和inv(n!)
    int maxm =2* max(n, m);
    fac[0] = 1;
    for (int i = 1; i <= maxm;i++){//处理阶乘
        fac[i] = (1ll * fac[i - 1] * i) % Mod;//可用1ll相乘强制longlong
    }
    inv[maxm] = q_pow(fac[maxm], Mod - 2);
    for (int i = maxm - 1; i >= 0;i--){
        inv[i] = 1ll * inv[i + 1] * (i + 1) % Mod; //inv((n-1)!)=inv(n!)*n%mod;
    }
}

int Combination(int nn,int mm){//组合数逆元求法
    if(nn<mm)
        return 0;
    int cc = (1ll * fac[nn] * inv[nn - mm] % Mod * inv[mm] % Mod); //C(n,m)=n!*inv((n-m)!)%mod*inv(m!)%mod;
    return cc;
}