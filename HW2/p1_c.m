a1=[319,598,1,0,0,0,0,0,0,0,0,0;
    542,429,1,0,0,0,0,0,0,-349,0,0;
    654,431,1,0,0,0,0,0,0,0,-349,0;
    528,613,1,0,0,0,0,0,0,0,0,0;
    0,0,0,319,598,1,0,0,0,0,0,0;
    0,0,0,542,429,1,0,0,0,0,0,0;
    0,0,0,654,431,1,0,0,0,0,-145,0;
    0,0,0,528,613,1,0,0,0,0,0,-145;
    0,0,0,0,0,0,319,598,-1,0,0,0;
    0,0,0,0,0,0,542,429,0,-1,0,0;
    0,0,0,0,0,0,654,431,0,0,-1,0;
    0,0,0,0,0,0,528,613,0,0,0,-1];
b1=[0;0;0;0;0;0;0;0;-1;-1;-1;-1];
[L,U]=lu(a1);
x1=U\(L\b1)

a2=[319,598,1,0,0,0,0,0,0,0,0,0;
    542,429,1,0,0,0,0,0,0,-349,0,0;
    654,431,1,0,0,0,0,0,0,0,-349,0;
    528,613,1,0,0,0,0,0,0,0,0,0;
    0,0,0,319,598,1,0,0,0,0,0,0;
    0,0,0,542,429,1,0,0,0,0,0,0;
    0,0,0,654,431,1,0,0,0,0,-196,0;
    0,0,0,528,613,1,0,0,0,0,0,-196;
    0,0,0,0,0,0,319,598,-1,0,0,0;
    0,0,0,0,0,0,542,429,0,-1,0,0;
    0,0,0,0,0,0,654,431,0,0,-1,0;
    0,0,0,0,0,0,528,613,0,0,0,-1];
b2=[0;0;0;0;0;0;0;0;-1;-1;-1;-1];
[L,U]=lu(a2);
x2=U\(L\b2)
