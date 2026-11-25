import decimal as d
d.getcontext().prec = 50
D = d.Decimal
n,e,X=int(input()),D('0'),input().split(" ")
for i in range(n) :
 for j in range(i+1,n) :
  x,y=D(X[i]),D(X[j])
  m=D.min(x,y)
  e+=m*(x-(m+1)/2)/(x*y)
print(round(e,6))
